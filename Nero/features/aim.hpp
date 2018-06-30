#pragma once

class Aim
{
public:
	void TriggerBot();
	bool enabled = false;
};

extern Aim* g_pAim;