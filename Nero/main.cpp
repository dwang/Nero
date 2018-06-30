#include "include.hpp"

void glow() { g_pVisuals->Glow(); }
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

	Beep(330, 100);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	g_pStatic->Setup();

	g_pMenu->Update();

	std::thread tGlow(glow);
	std::thread tBunnyhop(bunnyhop);

	tGlow.detach();
	tBunnyhop.detach();

	while (true)
	{
		if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			g_pVisuals->enabled = !g_pVisuals->enabled;
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			g_pMisc->enabled = !g_pMisc->enabled;
			g_pMenu->Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
			

		if (GetAsyncKeyState(VK_END) & 0x8000)
		{
			tGlow.~thread();
			tBunnyhop.~thread();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			remote::detach_process();
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}