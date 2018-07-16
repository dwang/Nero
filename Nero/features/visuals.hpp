#pragma once

class Visuals
{
public:
	void glow();
	void radar();
	bool glowenabled = false;
	bool chamsenabled = false;
	bool radarenabled = false;
	int glowmode = 0;
	Color color;
	Color clrRender;
};

extern Visuals* g_pVisuals;
