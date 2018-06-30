#include "../include.hpp"

Visuals* g_pVisuals = new Visuals();

void Visuals::Glow()
{
	while (true)
	{
		if (g_pSDK->IsInGame() && (glowenabled || chamsenabled))
		{
			DWORD glowPointer = remote::read<uintptr_t>(g_pStatic->dwClientBase + g_pStatic->dwGlowObjectManager);
			int objectCount = remote::read<int>(g_pStatic->dwClientBase + g_pStatic->dwGlowObjectManager + 0x4);

			for (int i = 0; i < objectCount; i++)
			{
				GlowObjectDefinition_t glowObj = remote::read<GlowObjectDefinition_t>(glowPointer + (i * 0x38));

				if (glowObj.m_pEntity)
				{
					int classID = remote::read<int>(remote::read<int>(remote::read<int>(remote::read<int>(glowObj.m_pEntity + 0x8) + 2 * 0x4) + 0x1) + 20);

					Color clrRender = {};

					if (classID == CCSPlayer && !remote::read<bool>(glowObj.m_pEntity + 0xE9))
					{

						if (g_pSDK->GetLocalTeam() != remote::read<int>(glowObj.m_pEntity + 0xF0))
						{
							glowObj.r = 1.0f;
							glowObj.g = 0.0f;
							glowObj.b = 1.0f;
							glowObj.a = 0.6f;

							clrRender.SetColor(255, 0, 255, 255);
						}
						else
						{
							glowObj.r = 0.0f;
							glowObj.g = 0.5f;
							glowObj.b = 1.0f;
							glowObj.a = 0.6f;

							clrRender.SetColor(0, 128, 255, 255);
						}
					
						glowObj.m_bRenderWhenOccluded = true;
						glowObj.m_bRenderWhenUnoccluded = false;
						glowObj.m_bFullBloomRender = false;

						if (chamsenabled)
							glowObj.m_nGlowStyle = 1;
						else
							glowObj.m_nGlowStyle = 0;
					}

					if (classID == 1 || classID == 39 || classID >= 204 && classID <= 244 || classID == CBaseCSGrenade || classID == CBaseCSGrenadeProjectile || classID == CC4 || classID == CPlantedC4 || classID == CHEGrenade || classID == CMolotovProjectile || classID == CMolotovGrenade || classID == CIncendiaryGrenade || classID == CSmokeGrenade || classID == CSmokeGrenadeProjectile)
					{
						glowObj.r = 0.2f;
						glowObj.g = 0.6f;
						glowObj.b = 0.86f;
						glowObj.a = 0.7f;

						glowObj.m_bRenderWhenOccluded = true;
						glowObj.m_bRenderWhenUnoccluded = false;
						glowObj.m_bFullBloomRender = false;
						glowObj.m_nGlowStyle = 0;
					}

					remote::write<GlowObjectDefinition_t>(glowPointer + (i * 0x38), glowObj);
					if (chamsenabled)
						remote::write<Color>(glowObj.m_pEntity + 0x70, clrRender);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}