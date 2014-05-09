#ifndef __WTCLEVIATHANPROJECTILETURRETSETTINGS_H__
#define __WTCLEVIATHANPROJECTILETURRETSETTINGS_H__

class cLeviathanProjectileTurretSettings : public cLeviathanTurretSettings
{
 public:
 float mfProjSpeed;
 cDamage mcBulletDamage;


cLeviathanProjectileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfProjSpeed,cDamage lcBulletDamage);
cLeviathanProjectileTurretSettings(const cLeviathanTurretSettings &lpSettings,float lfProjSpeed,cDamage lcBulletDamage);
cLeviathanProjectileTurretSettings(cLeviathanProjectileTurretSettings *lpSettings);
cLeviathanProjectileTurretSettings(const cLeviathanProjectileTurretSettings &lpSettings);

    uint8 Type();
    cLeviathanProjectileTurretSettings *ProjectileTurret();

    float DisplayDamage();
    float DisplayProjSpeed();
    float Range();
};

#endif
