#include "../include.hpp"

Static* g_pStatic = new Static();

void Static::setup()
{

	if (remote::find_module_by_name(FNV("client.dll")).first == NULL) {
		Static::using_panorama = (GetModuleHandle("client_panorama.dll") != NULL);
	}

	client_dll = Static::using_panorama ? FNV("client_panorama.dll") : FNV("client.dll");

	clientmodule = remote::find_module_by_name(client_dll);
	enginemodule = remote::find_module_by_name(FNV("engine.dll"));

	dwLocalPlayer = remote::read<uintptr_t>(remote::find_pattern(client_dll, "\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A\x00", "x????xx????????x????xxx?") + 1) + 16 - clientmodule.first;
	dwClientState = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0", "x????xxx?x?xxxx") + 1) - enginemodule.first;
	dwClientState_State = remote::read<uintptr_t>(remote::find_pattern(FNV("engine.dll"), "\x83\xB8\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3", "xx?????xxxx") + 2);
	dwEntityList = remote::read<uintptr_t>(remote::find_pattern(client_dll, "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx") + 1) - clientmodule.first;
	dwGlowObjectManager = remote::read<uintptr_t>(remote::find_pattern(client_dll, "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B", "x????xxxx") + 1) + 4 - clientmodule.first;
	dwForceJump = remote::read<uintptr_t>(remote::find_pattern(client_dll, "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 2) - clientmodule.first;
	dwForceAttack = remote::read<uintptr_t>(remote::find_pattern(client_dll, "\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE", "xx????xx????xxxxxx") + 2) - clientmodule.first;

	netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_lifeState")>();


#ifdef _DEBUG
	std::cout << "dwLocalPlayer: 0x" << std::hex << std::uppercase << dwLocalPlayer << std::endl;
	std::cout << "dwClientState: 0x" << std::hex << std::uppercase << dwClientState << std::endl;
	std::cout << "dwClientState_State: 0x" << std::hex << std::uppercase << dwClientState_State << std::endl;
	std::cout << "dwEntityList: 0x" << std::hex << std::uppercase << dwEntityList << std::endl;
	std::cout << "dwGlowObjectManager: 0x" << std::hex << std::uppercase << dwGlowObjectManager << std::endl;
	std::cout << "dwForceJump: 0x" << std::hex << std::uppercase << dwForceJump << std::endl;
	std::cout << "dwForceAttack: 0x" << std::hex << std::uppercase << dwForceAttack << std::endl;
#endif // _DEBUG
}