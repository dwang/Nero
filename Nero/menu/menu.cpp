#include "../include.hpp"

Menu* g_pMenu = new Menu();

void Menu::Setup()
{
	SetConsoleTitleA("Nero");
	g_pMenu->ShowConsoleCursor(false);

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

void Menu::Update()
{
	system("cls");

	std::cout << std::endl;
	std::cout << "  _   _                " << std::endl;
	std::cout << " | \\ | | ___ _ __ ___  " << std::endl;
	std::cout << " |  \\| |/ _ \\ '__/ _ \\ " << std::endl;
	std::cout << " | |\\  |  __/ | | (_) |" << std::endl;
	std::cout << " |_| \\_|\\___|_|  \\___/ " << std::endl;
	std::cout << std::endl;
	std::cout << " by Meow404" << std::endl;
	std::cout << std::endl;

	std::cout << "> Panic Key [VK_END]" << std::endl << std::endl;

	std::cout << "> Glow ESP [F1] = ";
	if (g_pVisuals->enabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;

	std::cout << "> Bunnyhop [F2] = ";
	if (g_pMisc->enabled)
		std::cout << green << "Enabled " << white << std::endl << std::endl;
	else
		std::cout << red << "Disabled" << white << std::endl << std::endl;
}

void Menu::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}