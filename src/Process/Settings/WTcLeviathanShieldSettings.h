#ifndef __WTCLEVIATHANSHIELDSETTINGS_H__
#define __WTCLEVIATHANSHIELDSETTINGS_H__

class cLeviathanShieldSettings : public cLeviathanComponentSettings
{
  public:
    cLeviathanShieldSettings(cLeviathanComponentSettings *lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	uint32 liFilter,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor);

	cLeviathanShieldSettings(const cLeviathanComponentSettings &lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	uint32 liFilter,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor);

    float mfShieldMax;
	float mfShieldRecharge;
	float mfShieldDelay;
	cRGBA mcShieldColor;
	 float mfMaxHealthInv;
    cMesh *mpHull;
    cMesh *mpShield;

    cMeshFileCollision *mpColl;
    cMeshFileCollision *mpShieldColl;

    uint32 miFilter;

    uint8 Type();
    cLeviathanShieldSettings *Shield();

};

#endif
