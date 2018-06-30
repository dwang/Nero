#include "../include.hpp"

SDK* g_pSDK = new SDK();

uintptr_t SDK::GetLocalPlayer()
{
	return remote::read<uintptr_t>(g_pStatic->dwClientBase + g_pStatic->dwLocalPlayer);
}

uintptr_t SDK::GetClientState()
{
	return remote::read<uintptr_t>(g_pStatic->dwEngineBase + g_pStatic->dwClientState);
}

bool SDK::IsInGame()
{
	return remote::read<int>(GetClientState() + g_pStatic->dwClientState_State) == 6;
}

int SDK::GetLocalTeam()
{
	return remote::read<int>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CBaseEntity->m_iTeamNum")>());
}

int SDK::GetLocalHealth()
{
	return remote::read<int>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_iHealth")>());
}

int SDK::GetLocalFlags()
{
	return remote::read<int>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_fFlags")>());
}

void SDK::ForceJump()
{
	remote::write<int>(g_pStatic->dwClientBase + g_pStatic->dwForceJump, 6);
}

void SDK::ForceAttack()
{
	remote::write<int>(g_pStatic->dwClientBase + g_pStatic->dwForceAttack, 6);
}