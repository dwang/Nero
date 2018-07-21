#include "../include.hpp"

SDK* g_pSDK = new SDK();

uintptr_t SDK::GetLocalPlayer()
{
	return remote::read<uintptr_t>(g_pStatic->clientmodule.first + g_pStatic->dwLocalPlayer);
}

uintptr_t SDK::GetClientState()
{
	return remote::read<uintptr_t>(g_pStatic->enginemodule.first + g_pStatic->dwClientState);
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
	if (GetLocalPlayer() && GetLocalHealth() > 0)
		remote::write<int>(g_pStatic->clientmodule.first + g_pStatic->dwForceJump, 6);
}

void SDK::ForceAttack()
{
	if (GetLocalPlayer() && GetLocalHealth() > 0)
		remote::write<int>(g_pStatic->clientmodule.first + g_pStatic->dwForceAttack, 6);
}

uintptr_t SDK::GetEntityBase(int index)
{
	return remote::read<uintptr_t>(g_pStatic->clientmodule.first + g_pStatic->dwEntityList + (index * 0x10));
}

int SDK::GetEntityTeam(uintptr_t playerBase)
{
	if (playerBase != NULL)
		return remote::read<int>(playerBase + netvar_manager::get_offset_by_hash_cached<FNV("CBaseEntity->m_iTeamNum")>());
}

int SDK::GetEntityHealth(uintptr_t playerBase)
{
	if (playerBase != NULL)
		return remote::read<int>(playerBase + netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_iHealth")>());
}

bool SDK::GetDormant(uintptr_t playerBase)
{
	if (playerBase != NULL)
		return remote::read<bool>(playerBase + 0xE9);
}

Vector SDK::GetLocalVelocity()
{
	if (GetLocalPlayer() && GetLocalHealth() > 0)
		return remote::read<Vector>(GetLocalPlayer() + netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_vecVelocity[0]")>());
}

void SDK::ForceFullUpdate()
{
	remote::write<int>(g_pSDK->GetClientState() + 0x174, -1);
}