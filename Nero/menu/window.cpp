#include "../include.hpp"

using namespace render;

Window* g_pWindow = new Window();

std::unique_ptr<Overlay> Window::create_overlay(const EDeviceType type, const std::string& window_title)
{
	auto overlay = Overlay::New(type);
	if (!overlay) {
		return nullptr;
	}
	if (!overlay->create(window_title)) {
		return nullptr;
	}

	auto surface = overlay->get_surface();
	if (!surface) {
		return nullptr;
	}
	overlay->scale_overlay();
	if (GetWindowRect(FindWindow(0, "Counter-Strike: Global Offensive"), &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	if (!surface->add_font(
		"default",
		"Segoe UI",
		width / 50,
		FW_NORMAL,
		/// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
		DEFAULT_QUALITY
	)) {
		return nullptr;
	}

	return std::move(overlay);
}

void Window::setup()
{
	overlay = create_overlay(EDeviceType::Direct3D9, "Counter-Strike: Global Offensive");

	auto* callback = overlay->add_callback(
		"menu", [](Surface* surface) {
		surface->text(80, 50, "default", 0xFFFFFFFF, "Nero by Meow404");
		surface->text(80, 80, "default", 0xFFFFFFFF, "Glow ESP [" + g_pConfig->vkToString(g_pConfig->hotkeys.glowesp) + "]");
		surface->text(250, 80, "default", g_pVisuals->glowenabled ? 0xFF00FF00 : 0xFFFF0000, g_pVisuals->glowenabled ? "ON" : "OFF");
		surface->text(80, 110, "default", 0xFFFFFFFF, "Chams [" + g_pConfig->vkToString(g_pConfig->hotkeys.chams) + "]");
		surface->text(250, 110, "default", g_pVisuals->chamsenabled ? 0xFF00FF00 : 0xFFFF0000, g_pVisuals->chamsenabled ? "ON" : "OFF");
		surface->text(80, 140, "default", 0xFFFFFFFF, "Triggerbot [" + g_pConfig->vkToString(g_pConfig->hotkeys.triggerbot) + "]");
		surface->text(250, 140, "default", g_pAim->triggerbotenabled ? 0xFF00FF00 : 0xFFFF0000, g_pAim->triggerbotenabled ? "ON" : "OFF");
		surface->text(80, 170, "default", 0xFFFFFFFF, "Bunnyhop [" + g_pConfig->vkToString(g_pConfig->hotkeys.bunnyhop) + "]");
		surface->text(250, 170, "default", g_pMisc->bunnyhopenabled ? 0xFF00FF00 : 0xFFFF0000, g_pMisc->bunnyhopenabled ? "ON" : "OFF");
		surface->text(80, 200, "default", 0xFFFFFFFF, "Radar [" + g_pConfig->vkToString(g_pConfig->hotkeys.radar) + "]");
		surface->text(250, 200, "default", g_pVisuals->radarenabled ? 0xFF00FF00 : 0xFFFF0000, g_pVisuals->radarenabled ? "ON" : "OFF");
		surface->text(80, 230, "default", 0xFFFFFFFF, "Change Color [" + g_pConfig->vkToString(g_pConfig->visuals.changecolor) + "]");
		surface->text(250, 230, "default", 0xFFFFFFFF, g_pVisuals->colorname);
		surface->text(80, 260, "default", 0xFFFFFFFF, "Reload Config [" + g_pConfig->vkToString(g_pConfig->hotkeys.reloadconfig) + "]");
		surface->text(80, 290, "default", 0xFFFFFFFF, "Panic Key [" + g_pConfig->vkToString(g_pConfig->hotkeys.panic) + "]");
	}
	);
}

void Window::draw()
{
	while (overlay->render())
	{
		overlay->scale_overlay();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}