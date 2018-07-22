#pragma once

#include "../include.hpp"

using namespace render;

class Window
{
public:
	std::unique_ptr<Overlay> overlay = nullptr;
	void setup();
	void draw();
private:
	std::unique_ptr<Overlay> create_overlay(const EDeviceType type, const std::string& window_title);
};

extern Window* g_pWindow;