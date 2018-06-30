#include "../include.hpp"

Aim* g_pAim = new Aim();

void Aim::TriggerBot()
{
	while (true)
	{
		if (g_pSDK->IsGameFocused && g_pSDK->IsInGame() && enabled)
		{
			if (GetAsyncKeyState(VK_MENU) & 0x8000 && g_pSDK->GetCrosshairID() > 0 && g_pSDK->GetCrosshairID() <= 64 && g_pSDK->GetLocalTeam() != g_pSDK->GetEntityTeam(g_pSDK->GetEntityBase(g_pSDK->GetCrosshairID() - 1)))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				g_pSDK->ForceAttack();
			}

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}