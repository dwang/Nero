#include "../include.hpp"


Static* g_pStatic = new Static();

void Static::setup()
{
	clientmodule = remote::find_module_by_name(FNV("client.dll"));
	enginemodule = remote::find_module_by_name(FNV("engine.dll"));

	dwLocalPlayer = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A\x00", "x????xx????????x????xxx?") + 1) + 16 - clientmodule.first;
	dwClientState = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0", "x????xxx?x?xxxx") + 1) - enginemodule.first;
	dwClientState_State = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\x83\xB8\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3", "xx?????xxxx") + 2);
	dwEntityList = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx") + 1) - clientmodule.first;
	dwGlowObjectManager = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B", "x????xxxx") + 1) + 4 - clientmodule.first;
	dwForceJump = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 2) - clientmodule.first;
	dwForceAttack = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE", "xx????xx????xxxxxx") + 2) - clientmodule.first;

	if (remote::find_module_by_name(FNV("client_panorama.dll")).first != 0)
	{
		clientmodule = remote::find_module_by_name(FNV("client_panorama.dll"));
		dwLocalPlayer = remote::read<uintptr_t>(remote::find_pattern(FNV("client_panorama.dll"), "\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A\x00", "x????xx????????x????xxx?") + 1) + 16 - clientmodule.first;
		dwClientState = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0", "x????xxx?x?xxxx") + 1) - enginemodule.first;
		dwClientState_State = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\x83\xB8\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3", "xx?????xxxx") + 2);
		dwEntityList = remote::read<uintptr_t>(remote::find_pattern(FNV("client_panorama.dll"), "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx") + 1) - clientmodule.first;
		dwGlowObjectManager = remote::read<uintptr_t>(remote::find_pattern(FNV("client_panorama.dll"), "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B", "x????xxxx") + 1) + 4 - clientmodule.first;
		dwForceJump = remote::read<uintptr_t>(remote::find_pattern(FNV("client_panorama.dll"), "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 2) - clientmodule.first;
		dwForceAttack = remote::read<uintptr_t>(remote::find_pattern(FNV("client_panorama.dll"), "\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE", "xx????xx????xxxxxx") + 2) - clientmodule.first;
	}

//netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_lifeState")>();
//	dwCLobbyScreen = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\xA1\x00\x00\x00\x00\x85\xC0\x74\x0F\x6A\x00", "x????xxxxx?") + 1) - clientmodule.first;
//	dwAcceptMatch = remote::find_pattern(FNV("client.dll"), "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x08\x56\x8B\x35\x00\x00\x00\x00\x57\x83\xBE", "xxxxxxxxxxxx????xxx") - clientmodule.first;
//	dwAcceptMatch += clientmodule.first;
//	dwMatchAccepted = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\x89\xB7\x00\x00\x00\x00\x8B\x4F\x04\x85\xC9", "xx????xxxxx") + 2) - clientmodule.first;
//	dwMatchFound = remote::read<uintptr_t>(remote::find_pattern(FNV("client.dll"), "\x89\x87\x00\x00\x00\x00\x8B\x87\x00\x00\x00\x00\x3B\xF0", "xx????xx????xx") + 2);

#ifdef _DEBUG
	std::cout << "dwClientBase: 0x" << std::hex << std::uppercase << dwClientBase << std::endl;
	std::cout << "dwEngineBase: 0x" << std::hex << std::uppercase << dwEngineBase << std::endl;
	std::cout << "dwLocalPlayer: 0x" << std::hex << std::uppercase << dwLocalPlayer << std::endl;
	std::cout << "dwClientState: 0x" << std::hex << std::uppercase << dwClientState << std::endl;
	std::cout << "dwClientState_State: 0x" << std::hex << std::uppercase << dwClientState_State << std::endl;
	std::cout << "dwEntityList: 0x" << std::hex << std::uppercase << dwEntityList << std::endl;
	std::cout << "dwGlowObjectManager: 0x" << std::hex << std::uppercase << dwGlowObjectManager << std::endl;
	std::cout << "dwForceJump: 0x" << std::hex << std::uppercase << dwForceJump << std::endl;
	std::cout << "dwForceAttack: 0x" << std::hex << std::uppercase << dwForceAttack << std::endl;
#endif // _DEBUG
}