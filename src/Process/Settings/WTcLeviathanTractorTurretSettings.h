#ifndef __WTCLEVIATHANTRACTORTURRETSETTINGS_H__
#define __WTCLEVIATHANTRACTORTURRETSETTINGS_H__

class cLeviathanTractorTurretSettings : public cLeviathanBeamTurretSettings
{
public:
    cLeviathanTractorTurretSettings(cLeviathanBeamTurretSettings *lpSettings);
    cLeviathanTractorTurretSettings(const cLeviathanBeamTurretSettings &lpSettings);
    cLeviathanTractorTurretSettings(cLeviathanTurretSettings *lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor);
    cLeviathanTractorTurretSettings(const cLeviathanTurretSettings &lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor);
    uint8 Type();
    cLeviathanTractorTurretSettings *TractorTurret();
    cLeviathanBeamTurretSettings *BeamTurret();

    float DisplayDamage();
};

#endif
