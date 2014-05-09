#include "stdafx.h"
#include "../../main.h"

cLeviathanTractorTurretSettings::cLeviathanTractorTurretSettings(cLeviathanBeamTurretSettings *lpSettings) : cLeviathanBeamTurretSettings(lpSettings)
{

};

cLeviathanTractorTurretSettings::cLeviathanTractorTurretSettings(const cLeviathanBeamTurretSettings &lpSettings) : cLeviathanBeamTurretSettings(lpSettings)
{

};

cLeviathanTractorTurretSettings::cLeviathanTractorTurretSettings(cLeviathanTurretSettings *lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor) : cLeviathanBeamTurretSettings(lpSettings,lpBeam,lfFireDelay,lfRechargeRate,lfDischargeRate,lfFullRecharge,lfDamageFactor,lcBeamColor)
{

};
cLeviathanTractorTurretSettings::cLeviathanTractorTurretSettings(const cLeviathanTurretSettings &lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor) : cLeviathanBeamTurretSettings(lpSettings,lpBeam,lfFireDelay,lfRechargeRate,lfDischargeRate,lfFullRecharge,lfDamageFactor,lcBeamColor)
{

};


uint8 cLeviathanTractorTurretSettings::Type(){return LV_TURRET_TRACTOR;};
cLeviathanTractorTurretSettings *cLeviathanTractorTurretSettings::TractorTurret(){return this;};
cLeviathanBeamTurretSettings *cLeviathanTractorTurretSettings::BeamTurret(){return 0;};

float cLeviathanTractorTurretSettings::DisplayDamage()
{
    return (1.0f-mfDamageFactor)*100.0f;
};

