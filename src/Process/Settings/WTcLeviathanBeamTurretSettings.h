#ifndef __WTCLEVIATHANBEAMTURRETSETTINGS_H__
#define __WTCLEVIATHANBEAMTURRETSETTINGS_H__

class cLeviathanBeamTurretSettings : public cLeviathanTurretSettings
{
public:
    cBeamMesh mpBeam;

    float mfFireDelay;
    float mfRechargeRate;
    float mfFullRecharge;
    float mfDischargeRate;
    float mfDamageFactor;
    cRGBA mcBeamColor;

    cLeviathanBeamTurretSettings(cLeviathanTurretSettings *lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor);
    cLeviathanBeamTurretSettings(const cLeviathanTurretSettings &lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor);
    cLeviathanBeamTurretSettings(cLeviathanBeamTurretSettings *lpSettings);
    cLeviathanBeamTurretSettings(const cLeviathanBeamTurretSettings &lpSettings);

    uint8 Type();
    cLeviathanBeamTurretSettings *BeamTurret();

    float DisplayROF();
    float DisplayDamage();
    float DisplayDelay();

    float Range();

};

#endif
