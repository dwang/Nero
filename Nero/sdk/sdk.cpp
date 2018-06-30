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

int SDK::GetCrosshairID()
{
	return remote::read<int>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CCSPlayer->m_bHasDefuser")>() + 92);
}

void SDK::ForceJump()
{
	remote::write<int>(g_pStatic->dwClientBase + g_pStatic->dwForceJump, 6);
}

void SDK::ForceAttack()
{
	remote::write<int>(g_pStatic->dwClientBase + g_pStatic->dwForceAttack, 6);
}

uintptr_t SDK::GetEntityBase(int index)
{
	return remote::read<uintptr_t>(g_pStatic->dwClientBase + g_pStatic->dwEntityList + (index * 0x10));
}

int SDK::GetEntityTeam(uintptr_t playerBase)
{
	return remote::read<int>(playerBase + netvar_manager::get_offset_by_hash_cached<FNV("CBaseEntity->m_iTeamNum")>());
}

Vector SDK::GetLocalVelocity()
{
	return remote::read<Vector>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_vecVelocity[0]")>());
}

void SDK::ForceFullUpdate()
{
	remote::write<int>(g_pSDK->GetClientState() + 0x174, -1);
}