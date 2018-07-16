#pragma once

#include "console_color.hpp"

class Menu
{
public:
	void setup();
	void update();
private:
	void showconsolecursor(bool showFlag);
};

extern Menu* g_pMenu;