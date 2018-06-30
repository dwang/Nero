#pragma once

class Visuals
{
public:
	void Glow();
	bool glowenabled = false;
	bool chamsenabled = false;
};

extern Visuals* g_pVisuals;
