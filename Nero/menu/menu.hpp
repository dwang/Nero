#pragma once

#include "console_color.hpp"

class Menu
{
public:
	void Setup();
	void Update();
private:
	void ShowConsoleCursor(bool showFlag);
};

extern Menu* g_pMenu;