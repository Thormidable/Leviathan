
#include "../../main.h"

cLeviathanBeamTurretSettings::cLeviathanBeamTurretSettings(cLeviathanBeamTurretSettings *lpSettings) : cLeviathanTurretSettings(lpSettings)
{
    mpBeam=lpSettings->mpBeam;

 mfFireDelay=lpSettings->mfFireDelay;
 mfRechargeRate=lpSettings->mfRechargeRate;
 mfFullRecharge=lpSettings->mfFullRecharge;
 mfDischargeRate=lpSettings->mfDischargeRate;
 mfDamageFactor=lpSettings->mfDamageFactor;
 mcBeamColor=lpSettings->mcBeamColor;
};
cLeviathanBeamTurretSettings::cLeviathanBeamTurretSettings(const cLeviathanBeamTurretSettings &lpSettings) : cLeviathanTurretSettings(lpSettings)
{
     mpBeam=lpSettings.mpBeam;
     mfFireDelay=lpSettings.mfFireDelay;
     mfRechargeRate=lpSettings.mfRechargeRate;
     mfFullRecharge=lpSettings.mfFullRecharge;
     mfDischargeRate=lpSettings.mfDischargeRate;
     mfDamageFactor=lpSettings.mfDamageFactor;
     mcBeamColor=lpSettings.mcBeamColor;
};

cLeviathanBeamTurretSettings::cLeviathanBeamTurretSettings(cLeviathanTurretSettings *lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor) : cLeviathanTurretSettings(lpSettings)
{
    mpBeam=lpBeam;
    mfFullRecharge=lfFullRecharge;
    mfRechargeRate=lfRechargeRate;
    mfDischargeRate=lfDischargeRate;
    mfFireDelay=lfFireDelay;
    mcBeamColor=lcBeamColor;
    mfDamageFactor=lfDamageFactor;
};


cLeviathanBeamTurretSettings::cLeviathanBeamTurretSettings(const cLeviathanTurretSettings &lpSettings,cBeamMesh lpBeam,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor) : cLeviathanTurretSettings(lpSettings)
{
    mpBeam=lpBeam;
    mfFullRecharge=lfFullRecharge;
    mfRechargeRate=lfRechargeRate;
    mfDischargeRate=lfDischargeRate;
    mfFireDelay=lfFireDelay;
    mcBeamColor=lcBeamColor;
    mfDamageFactor=lfDamageFactor;
};

uint8 cLeviathanBeamTurretSettings::Type(){return LV_TURRET_BEAM;};
cLeviathanBeamTurretSettings *cLeviathanBeamTurretSettings::BeamTurret(){return this;};

float cLeviathanBeamTurretSettings::DisplayROF()
{
    return 240.0f*mfRechargeRate/mfFullRecharge;
};

float cLeviathanBeamTurretSettings::DisplayDamage()
{
    return ((mfFullRecharge-(mfFireDelay/0.04f*mfDischargeRate))*mfDamageFactor)*0.5f*(mfFullRecharge-(mfFireDelay/0.04f*mfDischargeRate))*mfDischargeRate/0.04f;
};

float cLeviathanBeamTurretSettings::DisplayDelay()
{
    return mfFireDelay/0.04f*mfDischargeRate;
};

float cLeviathanBeamTurretSettings::Range()
{
    return mpBeam.mfLength;
}
