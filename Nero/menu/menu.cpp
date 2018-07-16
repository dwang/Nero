#include "../include.hpp"

Menu* g_pMenu = new Menu();

void Menu::setup()
{
	SetConsoleTitleA("Nero 1.4");
	g_pMenu->showconsolecursor(false);

	std::cout << std::endl;
	std::cout << "  _   _                " << std::endl;
	std::cout << " | \\ | | ___ _ __ ___  " << std::endl;
	std::cout << " |  \\| |/ _ \\ '__/ _ \\ " << std::endl;
	std::cout << " | |\\  |  __/ | | (_) |" << std::endl;
	std::cout << " |_| \\_|\\___|_|  \\___/ " << std::endl;
	std::cout << std::endl;
	std::cout << " by Meow404" << std::endl;
	std::cout << std::endl;
}

void Menu::update()
{
	system("cls");

	std::cout << std::endl;
	std::cout << white << "  _   _                " << std::endl;
	std::cout << " | \\ | | ___ _ __ ___  " << std::endl;
	std::cout << " |  \\| |/ _ \\ '__/ _ \\ " << std::endl;
	std::cout << " | |\\  |  __/ | | (_) |" << std::endl;
	std::cout << " |_| \\_|\\___|_|  \\___/ " << std::endl;
	std::cout << std::endl;
	std::cout << " by Meow404" << std::endl << std::endl;

	std::cout << "> Glow ESP [" << g_pConfig->vkToString(g_pConfig->hotkeys.glowesp) << "] = ";
	if (g_pVisuals->glowenabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;
	
	std::cout << "> Chams [" << g_pConfig->vkToString(g_pConfig->hotkeys.chams) << "] = ";
	if (g_pVisuals->chamsenabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;


	std::cout << "> Triggerbot [" << g_pConfig->vkToString(g_pConfig->hotkeys.triggerbot) << "] = ";
	if (g_pAim->triggerbotenabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;


	std::cout << "> Bunnyhop [" << g_pConfig->vkToString(g_pConfig->hotkeys.bunnyhop) << "] = ";
	if (g_pMisc->bunnyhopenabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;

	std::cout << "> Radar [" << g_pConfig->vkToString(g_pConfig->hotkeys.radar) << "] = ";
	if (g_pVisuals->radarenabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;

	std::cout << "> Change Color [" << g_pConfig->vkToString(g_pConfig->visuals.changecolor) << "] = ";
	switch (g_pVisuals->glowmode)
	{
	case 0:
		std::cout << pink << "Pink" << white << std::endl << std::endl;
		break;
	case 1:
		std::cout << red << "Red" << white << std::endl << std::endl;
		break;
	case 2:
		std::cout << green << "Green" << white << std::endl << std::endl;
		break;
	case 3:
		std::cout << blue << "Blue" << white << std::endl << std::endl;
		break;
	case 4:
		std::cout << "HP" << std::endl << std::endl;
		break;
	case 5:
		std::cout << "Custom" << std::endl << std::endl;
		break;
	default:
		std::cout << pink << "Pink" << white << std::endl << std::endl;
		break;
	}

	std::cout << "> Reload Config [" << g_pConfig->vkToString(g_pConfig->hotkeys.reloadconfig) << "]" << std::endl << std::endl;

	std::cout << "> Config File Location = " << g_pConfig->PrintApplicationPath() + "\\Nero.ini" << std::endl << std::endl;

	std::cout << "> Panic Key [" << g_pConfig->vkToString(g_pConfig->hotkeys.panic) << "]" << std::endl << std::endl;
}

void Menu::showconsolecursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}