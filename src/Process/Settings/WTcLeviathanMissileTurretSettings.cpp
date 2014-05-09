#include "stdafx.h"
#include "../../main.h"

    cLeviathanMissileTurretSettings::cLeviathanMissileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings) : cLeviathanTurretSettings(lpSettings)
    {
        mfRange=lfRange;
        mpMissileSettings=lpMissileSettings;
    };

    cLeviathanMissileTurretSettings::cLeviathanMissileTurretSettings(const cLeviathanTurretSettings &lpSettings,float lfRange,cMissileSettings *lpMissileSettings) : cLeviathanTurretSettings(lpSettings)
    {
        mfRange=lfRange;
        mpMissileSettings=lpMissileSettings;
    };

    cLeviathanMissileTurretSettings::cLeviathanMissileTurretSettings(cLeviathanMissileTurretSettings *lpSettings) : cLeviathanTurretSettings(lpSettings)
    {
        mfRange=lpSettings->mfRange;
        mpMissileSettings=lpSettings->mpMissileSettings;
    };

    cLeviathanMissileTurretSettings::cLeviathanMissileTurretSettings(const cLeviathanMissileTurretSettings &lpSettings) : cLeviathanTurretSettings(lpSettings)
    {
        mfRange=lpSettings.mfRange;
        mpMissileSettings=lpSettings.mpMissileSettings;
    };


uint8 cLeviathanMissileTurretSettings::Type(){return LV_TURRET_MISSILE;};
cLeviathanMissileTurretSettings *cLeviathanMissileTurretSettings::MissileTurret(){return this;};

float cLeviathanMissileTurretSettings::DisplayDamage()
{
    return mpMissileSettings->DetonationDamage();
};

float cLeviathanMissileTurretSettings::Range()
{
    return mfRange;
}
