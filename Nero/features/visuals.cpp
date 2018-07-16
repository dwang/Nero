#include "../include.hpp"

Visuals* g_pVisuals = new Visuals();

void Visuals::glow()
{
	while (true)
	{
		if (g_pSDK->IsInGame() && (glowenabled || chamsenabled))
		{
			DWORD glowPointer = remote::read<uintptr_t>(g_pStatic->clientmodule.first + g_pStatic->dwGlowObjectManager);
			int objectCount = remote::read<int>(g_pStatic->clientmodule.first + g_pStatic->dwGlowObjectManager + 0x4);

			if (!glowPointer && objectCount)
				continue;

			for (int i = 0; i < objectCount; i++)
			{
				GlowObjectDefinition_t glowObj = remote::read<GlowObjectDefinition_t>(glowPointer + (i * 0x38));

				if (glowObj.m_pEntity)
				{
					int classID = remote::read<int>(remote::read<int>(remote::read<int>(remote::read<int>(glowObj.m_pEntity + 0x8) + 2 * 0x4) + 0x1) + 20);

					if (!classID)
						continue;

					if (classID == CCSPlayer && !g_pSDK->GetDormant(glowObj.m_pEntity))
					{
						if (g_pSDK->GetLocalTeam() != g_pSDK->GetEntityTeam(glowObj.m_pEntity))
						{
							switch (g_pVisuals->glowmode)
							{
							case 0:
								g_pVisuals->color = Color(1.0f, 0.0f, 1.0f, 0.6f);
								break;
							case 1:
								g_pVisuals->color = Color(1.0f, 0.0f, 0.0f, 0.6f);
								break;
							case 2:
								g_pVisuals->color = Color(0.0f, 1.0f, 0.0f, 0.6f);
								break;
							case 3:
								g_pVisuals->color = Color(0.0f, 0.0f, 1.0f, 0.6f);
								break;
							case 4:
								g_pVisuals->color = Color((255 - 2.55 * g_pSDK->GetEntityHealth(glowObj.m_pEntity)) / 255.0f, (2.55 * g_pSDK->GetEntityHealth(glowObj.m_pEntity)) / 255.0f, 0.0f, 0.6f);
								break;
							case 5:
								g_pVisuals->color = Color(g_pConfig->visuals.custom_red / 255.0f, g_pConfig->visuals.custom_green / 255.0f, g_pConfig->visuals.custom_blue / 255.0f, g_pConfig->visuals.custom_alpha / 255.0f);
								break;
							}

							glowObj.clr = color;
							clrRender = color;
						}
						else
						{
							if (g_pConfig->visuals.teamcheck)
								continue;

							glowObj.clr = Color(0.0f, 0.5f, 1.0f, 0.6f);
							clrRender = Color(0.0f, 0.5f, 1.0f, 1.0f);
						}


						glowObj.m_bRenderWhenOccluded = true;
						glowObj.m_bRenderWhenUnoccluded = false;
						glowObj.m_bFullBloomRender = false;

						if (chamsenabled)
							glowObj.m_nGlowStyle = 1;
						else
							glowObj.m_nGlowStyle = 0;

						if (chamsenabled)
							remote::write<Color>(glowObj.m_pEntity + 0x70, clrRender);

						remote::write<GlowObjectDefinition_t>(glowPointer + (i * 0x38), glowObj);
					}

					if (classID == 1 || classID == 39 || classID >= 204 && classID <= 244 || classID == CBaseCSGrenade || classID == CBaseCSGrenadeProjectile || classID == CC4 || classID == CPlantedC4 || classID == CHEGrenade || classID == CMolotovProjectile || classID == CMolotovGrenade || classID == CIncendiaryGrenade || classID == CSmokeGrenade || classID == CSmokeGrenadeProjectile)
					{
						glowObj.clr = Color(0.2f, 0.6f, 0.86f, 0.7f);

						glowObj.m_bRenderWhenOccluded = true;
						glowObj.m_bRenderWhenUnoccluded = false;
						glowObj.m_bFullBloomRender = false;
						glowObj.m_nGlowStyle = 0;
					
						remote::write<GlowObjectDefinition_t>(glowPointer + (i * 0x38), glowObj);
					}
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Visuals::radar()
{
	while (true)
	{
		if (g_pSDK->IsInGame() && radarenabled)
		{
			DWORD glowPointer = remote::read<uintptr_t>(g_pStatic->clientmodule.first + g_pStatic->dwGlowObjectManager);
			int objectCount = remote::read<int>(g_pStatic->clientmodule.first + g_pStatic->dwGlowObjectManager + 0x4);

			for (int i = 0; i < objectCount; i++)
			{
				GlowObjectDefinition_t glowObj = remote::read<GlowObjectDefinition_t>(glowPointer + (i * 0x38));

				if (glowPointer && glowObj.m_pEntity && !g_pSDK->GetDormant(glowObj.m_pEntity))
					remote::write<bool>(glowObj.m_pEntity + 0x939, true);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}