#include "include.hpp"

void glow() { g_pVisuals->Glow(); }
void triggerbot() { g_pAim->TriggerBot(); }
void bunnyhop() { g_pMisc->BunnyHop(); }

int main()
{
	g_pMenu->Setup();

	std::cout << "> Waiting for \"csgo.exe\"" << std::endl << std::endl;;

	while (FindWindow(0, "Counter-Strike: Global Offensive") == NULL)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	remote::attach_process(FNV("csgo.exe"));

	std::cout << "> Waiting for \"client.dll\" and \"engine.dll\"" << std::endl << std::endl;;

	while (remote::find_module_by_name(FNV("serverbrowser.dll")).first == 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	std::cout << "> Successfully loaded Nero" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	g_pStatic->Setup();
	g_pMenu->Update();

	std::thread tGlow(glow);
	std::thread tTriggerbot(triggerbot);
	std::thread tBunnyhop(bunnyhop);

	tGlow.detach();
	tTriggerbot.detach();
	tBunnyhop.detach();

	while (true)
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			g_pVisuals->glowenabled = !g_pVisuals->glowenabled;
			g_pVisuals->chamsenabled = false;
			g_pSDK->ForceFullUpdate();
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			g_pVisuals->chamsenabled = !g_pVisuals->chamsenabled;
			g_pVisuals->glowenabled = false;
			g_pSDK->ForceFullUpdate();
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(VK_F3) & 0x8000)
		{
			g_pAim->enabled = !g_pAim->enabled;
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(VK_F4) & 0x8000)
		{
			g_pMisc->enabled = !g_pMisc->enabled;
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (FindWindowA(NULL, "Counter-Strike: Global Offensive") != GetForegroundWindow())
			g_pSDK->IsGameFocused = false;
		else
			g_pSDK->IsGameFocused = true;

		if (GetAsyncKeyState(VK_END) & 0x8000)
		{
			tGlow.~thread();
			tTriggerbot.~thread();
			tBunnyhop.~thread();
			g_pSDK->ForceFullUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			remote::detach_process();
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}