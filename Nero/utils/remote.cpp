#include "remote.hpp"
#include "memutils.hpp"
#include <ntstatus.h>
#include <Windows.h>
#include <winternl.h>
#include <Shlwapi.h>
#include <cassert>
#include <malloc.h>
#include <vector>
#include <algorithm>

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSYSAPI
NTSTATUS NTAPI NtReadVirtualMemory(
	_In_		HANDLE	ProcessHandle,
	_In_		PVOID	BaseAddress,
	_Out_		PVOID	Buffer,
	_In_		SIZE_T	NumberOfBytesToRead,
	_Out_opt_	PSIZE_T	NumberOfBytesRead
);

EXTERN_C NTSYSAPI
NTSTATUS NTAPI NtWriteVirtualMemory(
	_In_		HANDLE	ProcessHandle,
	_In_		PVOID	BaseAddress,
	_In_		PVOID	Buffer,
	_In_		SIZE_T	NumberOfBytesToWrite,
	_Out_opt_	PSIZE_T	NumberOfBytesWritten
);

EXTERN_C NTSYSAPI
NTSTATUS NTAPI NtOpenProcess(
	_Out_		PHANDLE				ProcessHandle,
	_In_		ACCESS_MASK			DesiredAccess,
	_In_		POBJECT_ATTRIBUTES	ObjectAttributes,
	_In_opt_	CLIENT_ID*			ClientId
);

typedef struct x_LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	_ACTIVATION_CONTEXT * EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} xLDR_DATA_TABLE_ENTRY, *xPLDR_DATA_TABLE_ENTRY;

typedef struct x_PEB_LDR_DATA
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
} xPEB_LDR_DATA, *xPPEB_LDR_DATA;

namespace remote
{
	static auto s_attached_process = INVALID_HANDLE_VALUE;

	__declspec(noinline)	// inlining kinda breaks alloca
		static auto get_process_id_by_image_name(const fnv::hash name) -> HANDLE
	{
		auto len = ULONG(0);
		NtQuerySystemInformation(SystemProcessInformation, nullptr, 0, &len);
		const auto buf = alloca(len);
		auto ret = NtQuerySystemInformation(SystemProcessInformation, buf, len, nullptr);
		assert(NT_SUCCESS(ret));
		if (!NT_SUCCESS(ret))
			return INVALID_HANDLE_VALUE;

		auto it = PSYSTEM_PROCESS_INFORMATION(buf);
		do
		{
			char image_name[MAX_PATH + 1];
			ANSI_STRING image_name_astr
			{
				0,
				sizeof(image_name),
				image_name
			};
			ret = RtlUnicodeStringToAnsiString(&image_name_astr, &it->ImageName, FALSE);
			assert(NT_SUCCESS(ret));
			image_name[image_name_astr.Length] = 0;
			for (auto& c : image_name)
				c = tolower(c);
			if (fnv::hash_runtime(image_name) == name)
				return it->UniqueProcessId;
		} while (it->NextEntryOffset && ((it = offset_ptr(it, it->NextEntryOffset))));
		return INVALID_HANDLE_VALUE;
	}

	auto attach_process(const fnv::hash name) -> void
	{
		const auto pid = get_process_id_by_image_name(name);

		constexpr auto access = PROCESS_ALL_ACCESS;

		CLIENT_ID client_id;

		client_id.UniqueProcess = pid;
		client_id.UniqueThread = nullptr;

		OBJECT_ATTRIBUTES attr;
		InitializeObjectAttributes(&attr,
			nullptr,
			FALSE,
			nullptr,
			nullptr);

		auto ret = NtOpenProcess(
			&s_attached_process,
			access,
			&attr,
			&client_id);

		assert(NT_SUCCESS(ret));
	}

	auto detach_process() -> void
	{
		NtClose(s_attached_process);
	}

	auto read_data(void* dest, const std::size_t size, void* src) -> void
	{
		NtReadVirtualMemory(s_attached_process,
			src,
			dest,
			size,
			nullptr
		);
	}

	auto write_data(void* dest, const std::size_t size, void* src) -> void
	{
		NtWriteVirtualMemory(s_attached_process,
			dest,
			src,
			size,
			nullptr
		);
	}

	auto raw_read(const uintptr_t address, const size_t size, void* buffer) -> void
	{
		NtReadVirtualMemory(s_attached_process, reinterpret_cast<void*>(address), buffer, size, nullptr);
	}

	auto raw_write(const uintptr_t address, const size_t size, const void* buffer) -> void
	{
		NtWriteVirtualMemory(s_attached_process, reinterpret_cast<void*>(address), const_cast<void*>(buffer), size, nullptr);
	}

	auto find_module_by_name(const fnv::hash name) -> std::pair<std::uintptr_t, std::size_t>
	{
		PROCESS_BASIC_INFORMATION basic_information;
		auto ret = NtQueryInformationProcess(s_attached_process,
			ProcessBasicInformation,
			&basic_information,
			sizeof(basic_information),
			nullptr);

		assert(NT_SUCCESS(ret));
		if (!NT_SUCCESS(ret))
			return { 0, 0 };

		xPPEB_LDR_DATA loader_data;
		ret = NtReadVirtualMemory(s_attached_process,
			&(basic_information.PebBaseAddress->Ldr),
			&loader_data,
			sizeof(loader_data),
			nullptr);

		assert(NT_SUCCESS(ret));
		if (!NT_SUCCESS(ret))
			return { 0, 0 };

		const auto list_head = &loader_data->InLoadOrderModuleList;

		PLIST_ENTRY current;
		ret = NtReadVirtualMemory(s_attached_process,
			&(loader_data->InLoadOrderModuleList.Flink),
			&current,
			sizeof(current),
			nullptr);
		assert(NT_SUCCESS(ret));
		if (!NT_SUCCESS(ret))
			return { 0, 0 };

		while (current != list_head)
		{
			xLDR_DATA_TABLE_ENTRY loader_module;
			ret = NtReadVirtualMemory(s_attached_process,
				CONTAINING_RECORD(current, xLDR_DATA_TABLE_ENTRY, InLoadOrderLinks),
				&loader_module,
				sizeof(loader_module),
				nullptr);

			assert(NT_SUCCESS(ret));
			if (!NT_SUCCESS(ret))
				return { 0, 0 };

			wchar_t image_name_wide[MAX_PATH + 1];
			ret = NtReadVirtualMemory(s_attached_process,
				loader_module.BaseDllName.Buffer,
				image_name_wide,
				max(sizeof(image_name_wide), loader_module.BaseDllName.MaximumLength),
				nullptr);
			loader_module.BaseDllName.Buffer = image_name_wide;

			char image_name[MAX_PATH + 1];
			ANSI_STRING image_name_astr
			{
				0,
				sizeof(image_name),
				image_name
			};
			ret = RtlUnicodeStringToAnsiString(&image_name_astr, &loader_module.BaseDllName, FALSE);
			assert(NT_SUCCESS(ret));
			image_name[image_name_astr.Length] = 0;
			for (auto& c : image_name)
				c = tolower(c);

			if (fnv::hash_runtime(image_name) == name)
				return
			{
				std::uintptr_t(loader_module.DllBase),
				std::size_t(loader_module.SizeOfImage)
			};

			current = loader_module.InLoadOrderLinks.Flink;
		}

		return { 0, 0 };
	}

	auto find_pattern(const fnv::hash module_name, const char* pattern, const char* mask) -> std::uintptr_t
	{
		const auto mod = find_module_by_name(module_name);
		const auto base = mod.first;
		const auto size = mod.second;
		std::vector<std::uint8_t> copy;
		copy.resize(size);
		read_data(copy.data(), size, reinterpret_cast<void*>(base));

		std::vector<std::pair<std::uint8_t, bool>> signature;

		for (auto i = 0u; mask[i]; i++)
			signature.push_back(std::make_pair(pattern[i], mask[i] == 'x'));

		auto ret = std::search(begin(copy), end(copy), begin(signature), end(signature),
			[](std::uint8_t curr, std::pair<std::uint8_t, bool> curr_pattern)
		{
			return (!curr_pattern.second) || curr == curr_pattern.first;
		});

		return ret == end(copy) ? 0 : base + (ret - begin(copy));
	}
}