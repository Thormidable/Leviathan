#ifndef __WTCPLANNEDSETTINGS_H__
#define __WTCPLANNEDSETTINGS_H__

class cLeviathanComponent;

class cTargetingFlag
{
    uint16 miComponentID;
    c3DVf mfPosition;
public:
    cTargetingFlag();
    void SetID(uint16 liID,c3DVf lfPos=c3DVf(0.0f,0.0f,0.0f));
    uint16 ID();
    c3DVf Position();
};

class cPlayerGunSettings
{
public:
  float mfReloadTime;
  float mfDamage;

};

class cPlannedSettings
{

public:
	cMatrix4 mmOrientation;
	cTargetingFlag mfTargets[12];
	uint32 mpMissileSlots[MISSILE_SLOTS];
	cPlayerGunSettings mcPlayerGun;

};

class cGameTarget
{
public:
    cGameTarget();
    cLeviathanComponent *mpComponent;
    cMatrix4 *mpMatrix;
    c3DVf mfPosition;

    bool Targeted();
    void SetTarget(cLeviathanComponent *lpComponent,c3DVf lfPos=c3DVf(0.0f,0.0f,0.0f));
    void SetTarget(cMatrix4 *lpMatrix,c3DVf lfPos=c3DVf(0.0f,0.0f,0.0f));
    void SetTarget(vRenderObject *lpObj,c3DVf lfPos=c3DVf(0.0f,0.0f,0.0f));
    bool CheckDeath(cLeviathanComponent *lpComp);
    bool CheckDeath(cMatrix4 *lpMat);
    void Clear();
    void operator=(cGameTarget lpOther);
    c3DVf GetPosition();
};

class cGameSettings
{
    public:

    cGameTarget mcTargets[12];
    void CheckDeath(cLeviathanComponent* lpComp);
};

extern cPlannedSettings gcPlannedSettings;

extern cGameSettings gcGameSettings;

#endif
