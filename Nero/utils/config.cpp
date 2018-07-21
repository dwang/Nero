#include "../include.hpp"

#define caseStringify(x) case x: return std::string(#x)

Config* g_pConfig = new Config();

BOOL Config::WritePrivateProfileIntA(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nInteger, LPCTSTR lpFileName)
{
	TCHAR lpString[1024];
	wsprintf(lpString, "%d", nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

float Config::GetPrivateProfileFloatA(const char* element, const char* item)
{
	char result[255];
	GetPrivateProfileStringA(element, item, NULL, result, 255, (PrintApplicationPath() + "\\Nero.ini").c_str());
	return (float) atof(result);
}

void Config::WritePrivateProfileFloatA(const char* element, const char* item, float value)
{
	char temp[255];
	sprintf_s(temp, "%f", value);
	WritePrivateProfileStringA(element, item, temp, (PrintApplicationPath() + "\\Nero.ini").c_str());
}

bool Config::GetPrivateProfileBoolA(const char* element, const char* item)
{
	char result[255];
	GetPrivateProfileStringA(element, item, NULL, result, 255, (PrintApplicationPath() + "\\Nero.ini").c_str());
	return (strcmp(result, "True") == 0 || strcmp(result, "true") == 0) ? true : false;
}

void Config::WritePrivateProfileBoolA(const char* element, const char* item, bool value)
{
	char temp[255];
	sprintf_s(temp, "%s", value ? "true" : "false");
	WritePrivateProfileStringA(element, item, temp, (PrintApplicationPath() + "\\Nero.ini").c_str());
}

std::string Config::PrintApplicationPath() {
	char chbuffer[MAX_PATH];
	GetModuleFileName(NULL, chbuffer, MAX_PATH);
	std::string::size_type pos = std::string(chbuffer).find_last_of("\\/");
	return std::string(chbuffer).substr(0, pos);
}

void Config::Setup()
{
	if (std::experimental::filesystem::exists((PrintApplicationPath() + "\\Nero.ini").c_str()))
		return;

	std::ofstream configfile;
	configfile.open((PrintApplicationPath() + "\\Nero.ini").c_str());
	configfile << "; Nero External by Meow404" << std::endl;
	configfile << "; Find keycodes at http://cherrytree.at/misc/vk.htm and use the decimal values" << std::endl << std::endl;
	configfile.close();

	WritePrivateProfileIntA("hotkeys", "glowesp", hotkeys.glowesp, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "chams", hotkeys.chams, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "triggerbot", hotkeys.triggerbot, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "bunnyhop", hotkeys.bunnyhop, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "radar", hotkeys.radar, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "panic", hotkeys.panic, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("hotkeys", "reloadconfig", hotkeys.reloadconfig, (PrintApplicationPath() + "\\Nero.ini").c_str());

	WritePrivateProfileIntA("visuals", "changecolor", visuals.changecolor, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileBoolA("visuals", "teamcheck", visuals.teamcheck);
	WritePrivateProfileIntA("visuals", "custom_red", visuals.custom_red, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("visuals", "custom_green", visuals.custom_green, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("visuals", "custom_blue", visuals.custom_blue, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileIntA("visuals", "custom_alpha", visuals.custom_alpha, (PrintApplicationPath() + "\\Nero.ini").c_str());

	WritePrivateProfileIntA("triggerbot", "key", triggerbot.key, (PrintApplicationPath() + "\\Nero.ini").c_str());
	WritePrivateProfileFloatA("triggerbot", "delay", triggerbot.delay);
}

void Config::Load()
{
	hotkeys.glowesp = GetPrivateProfileIntA("hotkeys", "glowesp", hotkeys.glowesp, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.chams = GetPrivateProfileIntA("hotkeys", "chams", hotkeys.chams, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.triggerbot = GetPrivateProfileIntA("hotkeys", "triggerbot", hotkeys.triggerbot, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.bunnyhop = GetPrivateProfileIntA("hotkeys", "bunnyhop", hotkeys.bunnyhop, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.radar = GetPrivateProfileIntA("hotkeys", "radar", hotkeys.radar, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.panic = GetPrivateProfileIntA("hotkeys", "panic", hotkeys.panic, (PrintApplicationPath() + "\\Nero.ini").c_str());
	hotkeys.reloadconfig = GetPrivateProfileIntA("hotkeys", "reloadconfig", hotkeys.reloadconfig, (PrintApplicationPath() + "\\Nero.ini").c_str());

	visuals.changecolor = GetPrivateProfileIntA("visuals", "changecolor", visuals.changecolor, (PrintApplicationPath() + "\\Nero.ini").c_str());
	visuals.teamcheck = GetPrivateProfileBoolA("visuals", "teamcheck");
	visuals.custom_red = GetPrivateProfileIntA("visuals", "custom_red", visuals.custom_red, (PrintApplicationPath() + "\\Nero.ini").c_str());
	visuals.custom_green = GetPrivateProfileIntA("visuals", "custom_green", visuals.custom_green, (PrintApplicationPath() + "\\Nero.ini").c_str());
	visuals.custom_blue = GetPrivateProfileIntA("visuals", "custom_blue", visuals.custom_blue, (PrintApplicationPath() + "\\Nero.ini").c_str());
	visuals.custom_alpha = GetPrivateProfileIntA("visuals", "custom_alpha", visuals.custom_alpha, (PrintApplicationPath() + "\\Nero.ini").c_str());

	triggerbot.key = GetPrivateProfileIntA("triggerbot", "key", triggerbot.key, (PrintApplicationPath() + "\\Nero.ini").c_str());
	triggerbot.delay = GetPrivateProfileFloatA("triggerbot", "delay");
}

std::string Config::vkToString(int vk) {
	if (vk == 0) return std::string("NONE");
	char c[2] = { 0 };
	if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z')) {
		c[0] = (char)vk;
		return std::string(c);
	}
	switch (vk) {
		caseStringify(VK_LBUTTON);
		caseStringify(VK_RBUTTON);
		caseStringify(VK_CANCEL);
		caseStringify(VK_MBUTTON);
		caseStringify(VK_XBUTTON1);
		caseStringify(VK_XBUTTON2);
		caseStringify(VK_BACK);
		caseStringify(VK_TAB);
		caseStringify(VK_CLEAR);
		caseStringify(VK_RETURN);
		caseStringify(VK_SHIFT);
		caseStringify(VK_CONTROL);
		caseStringify(VK_MENU);
		caseStringify(VK_PAUSE);
		caseStringify(VK_CAPITAL);
		caseStringify(VK_KANA);
		caseStringify(VK_JUNJA);
		caseStringify(VK_FINAL);
		caseStringify(VK_KANJI);
		caseStringify(VK_ESCAPE);
		caseStringify(VK_CONVERT);
		caseStringify(VK_NONCONVERT);
		caseStringify(VK_ACCEPT);
		caseStringify(VK_MODECHANGE);
		caseStringify(VK_SPACE);
		caseStringify(VK_PRIOR);
		caseStringify(VK_NEXT);
		caseStringify(VK_END);
		caseStringify(VK_HOME);
		caseStringify(VK_LEFT);
		caseStringify(VK_UP);
		caseStringify(VK_RIGHT);
		caseStringify(VK_DOWN);
		caseStringify(VK_SELECT);
		caseStringify(VK_PRINT);
		caseStringify(VK_EXECUTE);
		caseStringify(VK_SNAPSHOT);
		caseStringify(VK_INSERT);
		caseStringify(VK_DELETE);
		caseStringify(VK_HELP);
		caseStringify(VK_LWIN);
		caseStringify(VK_RWIN);
		caseStringify(VK_APPS);
		caseStringify(VK_SLEEP);
		caseStringify(VK_NUMPAD0);
		caseStringify(VK_NUMPAD1);
		caseStringify(VK_NUMPAD2);
		caseStringify(VK_NUMPAD3);
		caseStringify(VK_NUMPAD4);
		caseStringify(VK_NUMPAD5);
		caseStringify(VK_NUMPAD6);
		caseStringify(VK_NUMPAD7);
		caseStringify(VK_NUMPAD8);
		caseStringify(VK_NUMPAD9);
		caseStringify(VK_MULTIPLY);
		caseStringify(VK_ADD);
		caseStringify(VK_SEPARATOR);
		caseStringify(VK_SUBTRACT);
		caseStringify(VK_DECIMAL);
		caseStringify(VK_DIVIDE);
		caseStringify(VK_F1);
		caseStringify(VK_F2);
		caseStringify(VK_F3);
		caseStringify(VK_F4);
		caseStringify(VK_F5);
		caseStringify(VK_F6);
		caseStringify(VK_F7);
		caseStringify(VK_F8);
		caseStringify(VK_F9);
		caseStringify(VK_F10);
		caseStringify(VK_F11);
		caseStringify(VK_F12);
		caseStringify(VK_F13);
		caseStringify(VK_F14);
		caseStringify(VK_F15);
		caseStringify(VK_F16);
		caseStringify(VK_F17);
		caseStringify(VK_F18);
		caseStringify(VK_F19);
		caseStringify(VK_F20);
		caseStringify(VK_F21);
		caseStringify(VK_F22);
		caseStringify(VK_F23);
		caseStringify(VK_F24);
		caseStringify(VK_NUMLOCK);
		caseStringify(VK_SCROLL);
		caseStringify(VK_OEM_NEC_EQUAL);
		caseStringify(VK_OEM_FJ_MASSHOU);
		caseStringify(VK_OEM_FJ_TOUROKU);
		caseStringify(VK_OEM_FJ_LOYA);
		caseStringify(VK_OEM_FJ_ROYA);
		caseStringify(VK_LSHIFT);
		caseStringify(VK_RSHIFT);
		caseStringify(VK_LCONTROL);
		caseStringify(VK_RCONTROL);
		caseStringify(VK_LMENU);
		caseStringify(VK_RMENU);
		caseStringify(VK_BROWSER_BACK);
		caseStringify(VK_BROWSER_FORWARD);
		caseStringify(VK_BROWSER_REFRESH);
		caseStringify(VK_BROWSER_STOP);
		caseStringify(VK_BROWSER_SEARCH);
		caseStringify(VK_BROWSER_FAVORITES);
		caseStringify(VK_BROWSER_HOME);
		caseStringify(VK_VOLUME_MUTE);
		caseStringify(VK_VOLUME_DOWN);
		caseStringify(VK_VOLUME_UP);
		caseStringify(VK_MEDIA_NEXT_TRACK);
		caseStringify(VK_MEDIA_PREV_TRACK);
		caseStringify(VK_MEDIA_STOP);
		caseStringify(VK_MEDIA_PLAY_PAUSE);
		caseStringify(VK_LAUNCH_MAIL);
		caseStringify(VK_LAUNCH_MEDIA_SELECT);
		caseStringify(VK_LAUNCH_APP1);
		caseStringify(VK_LAUNCH_APP2);
		caseStringify(VK_OEM_1);
		caseStringify(VK_OEM_PLUS);
		caseStringify(VK_OEM_COMMA);
		caseStringify(VK_OEM_MINUS);
		caseStringify(VK_OEM_PERIOD);
		caseStringify(VK_OEM_2);
		caseStringify(VK_OEM_3);
		caseStringify(VK_OEM_4);
		caseStringify(VK_OEM_5);
		caseStringify(VK_OEM_6);
		caseStringify(VK_OEM_7);
		caseStringify(VK_OEM_8);
		caseStringify(VK_OEM_AX);
		caseStringify(VK_OEM_102);
		caseStringify(VK_ICO_HELP);
		caseStringify(VK_ICO_00);
		caseStringify(VK_PROCESSKEY);
		caseStringify(VK_ICO_CLEAR);
		caseStringify(VK_PACKET);
	}
	c[0] = (char)vk;
	return std::string(c);
}