#include "../include.hpp"

Misc* g_pMisc = new Misc();

void Misc::BunnyHop()
{
	while (true)
	{
		if (g_pSDK->IsInGame() && enabled)
		{
			if ((g_pSDK->GetLocalFlags() & FL_ONGROUND || g_pSDK->GetLocalFlags() & FL_PARTIALGROUND) && GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				g_pSDK->ForceJump();
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 20 + 70));
				g_pSDK->ForceJump();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}