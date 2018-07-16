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
	return remote::read<int>(GetLocalPlayer() + /*netvar_manager::get_offset_by_hash_cached<FNV("CBaseEntity->m_iTeamNum")>()*/ 0xF0);
}

int SDK::GetLocalHealth()
{
	return remote::read<int>(GetLocalPlayer() + /*netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_iHealth")>()*/ 0xFC);
}

int SDK::GetLocalFlags()
{
	return remote::read<int>(GetLocalPlayer() + /*netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_fFlags")>()*/ 0x100);
}

int SDK::GetCrosshairID()
{
	return remote::read<int>(GetLocalPlayer() + /*netvar_manager::get_offset_by_hash_cached<FNV("CCSPlayer->m_bHasDefuser")>() + 92*/ 0xB2B8);
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
		return remote::read<int>(playerBase + /*netvar_manager::get_offset_by_hash_cached<FNV("CBaseEntity->m_iTeamNum")>()*/ 0xF0);
}

int SDK::GetEntityHealth(uintptr_t playerBase)
{
	if (playerBase != NULL)
		return remote::read<int>(playerBase + /*netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_iHealth")>()*/ 0xFC);
}

bool SDK::GetDormant(uintptr_t playerBase)
{
	if (playerBase != NULL)
		return remote::read<bool>(playerBase + 0xE9);
}

Vector SDK::GetLocalVelocity()
{
	if (GetLocalPlayer() && GetLocalHealth() > 0)
		return remote::read<Vector>(GetLocalPlayer() + /*netvar_manager::get_offset_by_hash_cached<FNV("CBasePlayer->m_vecVelocity[0]")>()*/ 0x110);
}

void SDK::ForceFullUpdate()
{
	remote::write<int>(g_pSDK->GetClientState() + 0x174, -1);
}