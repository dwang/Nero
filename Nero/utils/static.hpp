#pragma once

class Static
{
public:
	void setup();

	std::pair<std::uintptr_t, std::size_t> clientmodule;
	std::pair<std::uintptr_t, std::size_t> enginemodule;

	uintptr_t dwLocalPlayer;
	uintptr_t dwClientState;
	uintptr_t dwClientState_State;
	uintptr_t dwEntityList;
	uintptr_t dwGlowObjectManager;
	uintptr_t dwForceJump;
	uintptr_t dwForceAttack;
//	uintptr_t dwCLobbyScreen;
	//uintptr_t dwAcceptMatch;
//	uintptr_t dwMatchAccepted;
//	uintptr_t dwMatchFound;
};

extern Static* g_pStatic;
