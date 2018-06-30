#pragma once
#include "fnv.hpp"
#include <utility>

namespace remote
{
	auto attach_process(const fnv::hash name) -> void;
	auto detach_process() -> void;
	auto read_data(void* dest, const std::size_t size, void* src) -> void;
	auto write_data(void* dest, const std::size_t size, void* src) -> void;
	auto raw_read(const uintptr_t address, const size_t size, void* buffer) -> void;
	auto raw_write(const uintptr_t address, const size_t size, const void* buffer) -> void;
	auto find_module_by_name(const fnv::hash name)->std::pair<std::uintptr_t, std::size_t>;
	auto find_pattern(const fnv::hash module_name, const char* pattern, const char* mask)->std::uintptr_t;

	template <typename T>
	auto read(void* src) -> T
	{
		T v;
		read_data(&v, sizeof(v), src);
		return v;
	}

	template <typename T>
	auto write(void* dst, const T& v) -> void
	{
		write_data(dst, sizeof(T), &v);
	}

	template <typename T>
	T read(const uintptr_t address)
	{
		T buffer{};
		raw_read(address, sizeof(T), &buffer);
		return buffer;
	}

	template <typename T>
	void write(const uintptr_t address, const T& buffer)
	{
		raw_write(address, sizeof(T), &buffer);
	}

	template <typename T>
	class variable
	{
	private:
		using my_type = variable<T>;

		variable() = delete;
		variable(const my_type&) = delete;

	public:
		auto get() -> T { return read<T>(&remote_value); }
		auto get_raw() -> T* { return &remote_value; }
		auto set(const T& v) -> void { write(&remote_value, v); }

		operator T() { return get(); }
		auto operator =(const T& v) -> my_type& { set(v); return *this; }

	private:
		T remote_value;
	};
}
