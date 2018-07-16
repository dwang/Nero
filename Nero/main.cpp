#include "include.hpp"

void glow() { g_pVisuals->glow(); }
void radar() { g_pVisuals->radar(); }
void triggerbot() { g_pAim->triggerbot(); }
void bunnyhop() { g_pMisc->bunnyhop(); }

int main()
{
	g_pMenu->setup();

	std::cout << "> Waiting for \"csgo.exe\"" << std::endl << std::endl;;

	while (FindWindow(0, "Counter-Strike: Global Offensive") == NULL)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	remote::attach_process(FNV("csgo.exe"));

	std::cout << "> Waiting for modules" << std::endl << std::endl;;

	while (remote::find_module_by_name(FNV("serverbrowser.dll")).first == 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	std::cout << "> Scanning for offsets" << std::endl << std::endl;

	g_pStatic->setup();

	std::cout << "> Loading configuration file" << std::endl << std::endl;

	g_pConfig->Setup();
	g_pConfig->Load();

	std::cout << "> Successfully loaded Nero" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	g_pMenu->update();

	std::thread tGlow(glow);
	std::thread tRadar(radar);
	std::thread tTriggerbot(triggerbot);
	std::thread tBunnyhop(bunnyhop);

	tGlow.detach();
	tRadar.detach();
	tTriggerbot.detach();
	tBunnyhop.detach();

	while (true)
	{
		if (GetAsyncKeyState(g_pConfig->hotkeys.glowesp) & 0x8000)
		{
			g_pVisuals->glowenabled = !g_pVisuals->glowenabled;
			g_pVisuals->chamsenabled = false;
			g_pSDK->ForceFullUpdate();
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->hotkeys.chams) & 0x8000)
		{
			g_pVisuals->chamsenabled = !g_pVisuals->chamsenabled;
			g_pVisuals->glowenabled = false;
			g_pSDK->ForceFullUpdate();
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->hotkeys.triggerbot) & 0x8000)
		{
			g_pAim->triggerbotenabled = !g_pAim->triggerbotenabled;
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->hotkeys.bunnyhop) & 0x8000)
		{
			g_pMisc->bunnyhopenabled = !g_pMisc->bunnyhopenabled;
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->hotkeys.radar) & 0x8000)
		{
			g_pVisuals->radarenabled = !g_pVisuals->radarenabled;
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->visuals.changecolor) & 0x8000)
		{
			g_pVisuals->glowmode++;
			
			if (g_pVisuals->glowmode > 5)
				g_pVisuals->glowmode = 0;

			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(g_pConfig->hotkeys.reloadconfig) & 0x8000)
		{
			g_pConfig->Load();
			g_pMenu->update();
			Beep(330, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (FindWindowA(NULL, "Counter-Strike: Global Offensive") != GetForegroundWindow())
			g_pSDK->IsGameFocused = false;
		else
			g_pSDK->IsGameFocused = true;

		if (GetAsyncKeyState(g_pConfig->hotkeys.panic) & 0x8000 || FindWindowA(NULL, "Counter-Strike: Global Offensive") == NULL)
		{
			tGlow.~thread();
			tRadar.~thread();
			tTriggerbot.~thread();
			tBunnyhop.~thread();
			g_pSDK->ForceFullUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			remote::detach_process();
			Beep(330, 100);
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}