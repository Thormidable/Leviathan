#include "stdafx.h"
#include "../../main.h"

cLeviathanShieldSettings::cLeviathanShieldSettings(cLeviathanComponentSettings *lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	uint32 liFilter,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor) : cLeviathanComponentSettings(lpSettings)
	{

		 mpHull=_GET_MESH_FILE(lsMesh.c_str());
 		 mpShield=_GET_MESH_FILE(lsShieldMesh.c_str());

		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
		 mpShieldColl=_GET_COLLISION_MESH_FILE(lsShieldCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;

        mfShieldMax=lfShieldMax;
        mfShieldRecharge=lfShieldRecharge;
        mfShieldDelay=lfShieldDelay;
        mcShieldColor=lcShieldColor;
        miFilter=liFilter;
	}

	cLeviathanShieldSettings::cLeviathanShieldSettings(const cLeviathanComponentSettings &lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	uint32 liFilter,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor) : cLeviathanComponentSettings(lpSettings)
	{

		 mpHull=_GET_MESH_FILE(lsMesh.c_str());
 		 mpShield=_GET_MESH_FILE(lsShieldMesh.c_str());

		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
		 mpShieldColl=_GET_COLLISION_MESH_FILE(lsShieldCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;

        mfShieldMax=lfShieldMax;
        mfShieldRecharge=lfShieldRecharge;
        mfShieldDelay=lfShieldDelay;
        mcShieldColor=lcShieldColor;
        miFilter=liFilter;
	}


uint8 cLeviathanShieldSettings::Type(){return LV_SHIELD;};
cLeviathanShieldSettings *cLeviathanShieldSettings::Shield(){return this;};

