#include "../include.hpp"

Aim* g_pAim = new Aim();

void Aim::triggerbot()
{
	while (true)
	{
		if (g_pSDK->IsGameFocused && g_pSDK->IsInGame() && triggerbotenabled)
		{
			if (GetAsyncKeyState(g_pConfig->triggerbot.key))
			{
				if (g_pSDK->GetLocalPlayer() == NULL || !(g_pSDK->GetLocalHealth() > 0))
					continue;

				if (g_pSDK->GetCrosshairID() > 0 && g_pSDK->GetCrosshairID() <= 64)
				{
					if (g_pSDK->GetLocalTeam() != g_pSDK->GetEntityTeam(g_pSDK->GetEntityBase(g_pSDK->GetCrosshairID() - 1)) && !g_pSDK->GetDormant(g_pSDK->GetEntityBase(g_pSDK->GetCrosshairID() - 1)))
					{
						std::this_thread::sleep_for(std::chrono::milliseconds((int)g_pConfig->triggerbot.delay));
						g_pSDK->ForceAttack();
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}