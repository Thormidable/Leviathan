#include "stdafx.h"
#include "../../main.h"

   cLeviathanProjectileTurretSettings::cLeviathanProjectileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfSpeed,cDamage lfDamage) : cLeviathanTurretSettings(lpSettings)
  {
        mfProjSpeed=lfSpeed;
        mcBulletDamage=lfDamage;
  };

   cLeviathanProjectileTurretSettings::cLeviathanProjectileTurretSettings(const cLeviathanTurretSettings &lpSettings,float lfSpeed,cDamage lfDamage) : cLeviathanTurretSettings(lpSettings)
  {
        mfProjSpeed=lfSpeed;
        mcBulletDamage=lfDamage;
  };

cLeviathanProjectileTurretSettings::cLeviathanProjectileTurretSettings(cLeviathanProjectileTurretSettings *lpSettings) : cLeviathanTurretSettings(lpSettings)
{
 mfProjSpeed=lpSettings->mfProjSpeed;
 mcBulletDamage=lpSettings->mcBulletDamage;
};
cLeviathanProjectileTurretSettings::cLeviathanProjectileTurretSettings(const cLeviathanProjectileTurretSettings &lpSettings) : cLeviathanTurretSettings(lpSettings)
{
    mfProjSpeed=lpSettings.mfProjSpeed;
    mcBulletDamage=lpSettings.mcBulletDamage;
};

uint8 cLeviathanProjectileTurretSettings::Type(){return LV_TURRET_PROJECTILE;};
cLeviathanProjectileTurretSettings *cLeviathanProjectileTurretSettings::ProjectileTurret(){return this;};

float cLeviathanProjectileTurretSettings::DisplayDamage()
{
    return mcBulletDamage.mfDamage;
};

float cLeviathanProjectileTurretSettings::DisplayProjSpeed()
{
    return mfProjSpeed;
};

float cLeviathanProjectileTurretSettings::Range()
{
    return BULLET_RANGE;
}
