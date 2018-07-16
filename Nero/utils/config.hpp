#pragma once

#include <Windows.h>
#include <string>

class Config {
public:
	void Setup();
	void Load();
	std::string vkToString(int vk);
	std::string PrintApplicationPath();

	struct hotkeys {
		int glowesp = VK_F1;
		int chams = VK_F2;
		int triggerbot = VK_F3;
		int bunnyhop = VK_F4;
		int radar = VK_F5;
		int reloadconfig = VK_F7;
		int panic = VK_END;
	} hotkeys;

	struct visuals {
		int changecolor = VK_F6;
		bool teamcheck = false;
		int custom_red = 255;
		int custom_green = 255;
		int custom_blue = 0;
		int custom_alpha = 255;
	} visuals;

	struct triggerbot {
		int key = VK_MENU;
		float delay = 50.0;
	} triggerbot;

private:
	BOOL WritePrivateProfileIntA(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nInteger, LPCTSTR lpFileName);
	float GetPrivateProfileFloatA(const char * element, const char * item);
	void WritePrivateProfileFloatA(const char * element, const char * item, float value);
	bool GetPrivateProfileBoolA(const char * element, const char * item);
	void WritePrivateProfileBoolA(const char * element, const char * item, bool value);
};

extern Config* g_pConfig;