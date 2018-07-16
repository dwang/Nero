#include "../include.hpp"

Misc* g_pMisc = new Misc();

void Misc::bunnyhop()
{
	while (true)
	{
		if (g_pSDK->IsGameFocused && g_pSDK->IsInGame() && bunnyhopenabled)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (g_pSDK->GetLocalPlayer() == NULL || !(g_pSDK->GetLocalHealth() > 0))
					continue;

				if (g_pSDK->GetLocalFlags() & FL_ONGROUND)
				{
					if (g_pSDK->GetLocalVelocity().Length2D() > 0.1)
						g_pSDK->ForceJump();
				}

			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
/*
bool Misc::MatchFound()
{
	uintptr_t CLobbyScreen = remote::read<uintptr_t>(g_pStatic->dwClientBase + g_pStatic->dwCLobbyScreen);
	if (CLobbyScreen != NULL)
	{
		int iAccept = remote::read<int>(CLobbyScreen + g_pStatic->dwMatchAccepted);
		int iFound = remote::read<int>(CLobbyScreen + g_pStatic->dwMatchFound);

		if (iAccept == 0 && iFound != 0)
			Beep(330, 1000);

		return iAccept == 0 && iFound != 0;
	}
	else
		return false;
}

void Misc::RankReveal()
{

}
*/