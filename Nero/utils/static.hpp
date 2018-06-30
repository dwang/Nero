#pragma once

class Static
{
public:
	void Setup();

	std::pair<std::uintptr_t, std::size_t> clientmodule;
	std::pair<std::uintptr_t, std::size_t> enginemodule;

	uintptr_t dwClientBase;
	uintptr_t dwEngineBase;
	uintptr_t dwLocalPlayer;
	uintptr_t dwClientState;
	uintptr_t dwClientState_State;
	uintptr_t dwEntityList;
	uintptr_t dwGlowObjectManager;
	uintptr_t dwForceJump;
	uintptr_t dwForceAttack;
};

extern Static* g_pStatic;
