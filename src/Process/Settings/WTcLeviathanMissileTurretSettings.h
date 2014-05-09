#ifndef __WTCLEVIATHANMISSILETURRETSETTINGS_H__
#define __WTCLEVIATHANMISSILETURRETSETTINGS_H__


class cLeviathanMissileTurretSettings : public cLeviathanTurretSettings
{
public:
    cLeviathanMissileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings);
    cLeviathanMissileTurretSettings(const cLeviathanTurretSettings &lpSettings,float lfRange,cMissileSettings *lpMissileSettings);

    cLeviathanMissileTurretSettings(cLeviathanMissileTurretSettings *lpSettings);
    cLeviathanMissileTurretSettings(const cLeviathanMissileTurretSettings &lpSettings);
    cMissileSettings *mpMissileSettings;

    float mfReloadState;
    float mfRange;

    uint8 Type();
    cLeviathanMissileTurretSettings *MissileTurret();

    float DisplayDamage();
    float Range();

};

#endif
