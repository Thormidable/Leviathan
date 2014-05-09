#include "stdafx.h"
#include "../../main.h"

cDamageSettings::cDamageSettings(float lfDamage,uint8 liType)
{
    mfDamage=lfDamage;
    miType=liType;
};

cReductiveArmourSettings::cReductiveArmourSettings()
{
    memset(mpArmour,0,sizeof(float)*DAMAGE_TYPES);
};
cReductiveArmourSettings::cReductiveArmourSettings(float lfInstant,float lfContinuous,float lfArea)
{
    mpArmour[DAMAGE_TYPE_INSTANTANEOUS]=lfInstant;
    mpArmour[DAMAGE_TYPE_CONTINUOUS]=lfContinuous;
    mpArmour[DAMAGE_TYPE_AREA]=lfArea;
};

cReductiveArmourSettings::cReductiveArmourSettings(cReductiveArmourSettings *lpArmour)
{
    memcpy(mpArmour,lpArmour->mpArmour,sizeof(float)*3);
};

cReductiveArmourSettings::cReductiveArmourSettings(float lfArmour)
{
    mpArmour[DAMAGE_TYPE_INSTANTANEOUS]=lfArmour;
    mpArmour[DAMAGE_TYPE_CONTINUOUS]=lfArmour*CONTINUOUS_ARMOUR_FACTOR;
    mpArmour[DAMAGE_TYPE_AREA]=lfArmour;
};

vArmourSettings *vArmourSettings::MakeArmour(vArmourSettings *lpArmour)
{
    if(lpArmour)
    {
        if(dynamic_cast<cReductiveArmourSettings*>(lpArmour)) return new cReductiveArmourSettings(dynamic_cast<cReductiveArmourSettings*>(lpArmour));
        if(dynamic_cast<cPoweredArmourSettings*>(lpArmour)) return new cPoweredArmourSettings(dynamic_cast<cPoweredArmourSettings*>(lpArmour));
        if(dynamic_cast<cBrittleArmourSettings*>(lpArmour)) return new cBrittleArmourSettings(dynamic_cast<cBrittleArmourSettings*>(lpArmour));
        if(dynamic_cast<cTriangularArmourSettings*>(lpArmour)) return new cTriangularArmourSettings(dynamic_cast<cTriangularArmourSettings*>(lpArmour));
    }
    return 0;
};


cPoweredArmourSettings::cPoweredArmourSettings(float lfDamageEnergyConversion,float lfMaxDamage)
{
    mfDamageEnergyConversion=lfDamageEnergyConversion;
    mfMaxDamageConversion=lfMaxDamage;
};
cPoweredArmourSettings::cPoweredArmourSettings(cPoweredArmourSettings *lpArmour)
{
    mfDamageEnergyConversion=lpArmour->mfDamageEnergyConversion;
    mfMaxDamageConversion=lpArmour->mfMaxDamageConversion;
};

void cPoweredArmourSettings::ReactorPower(cLeviathanReactorSettings *lpReactor)
{
    lpReactor->AddPowerArmour(mfMaxDamageConversion*mfDamageEnergyConversion);
};


cBrittleArmourSettings::cBrittleArmourSettings(float lfArmourPoints,float lfBreakingPoint)
{
 mfArmourPoints=lfArmourPoints;
 mfBreakingPoint=lfBreakingPoint;
};

cBrittleArmourSettings::cBrittleArmourSettings(cBrittleArmourSettings *lpSettings)
{
 mfArmourPoints=lpSettings->mfArmourPoints;
 mfBreakingPoint=lpSettings->mfBreakingPoint;
};

cTriangularArmourSettings::cTriangularArmourSettings(float lfArmourPoints,float lfMinWear,float lfArmourScaling)
{
    mfArmourPoints=lfArmourPoints;
    mfMinWear=lfMinWear;
    mfArmourScaling=lfArmourScaling;
}
cTriangularArmourSettings::cTriangularArmourSettings(cTriangularArmourSettings *lpSettings)
{
    mfArmourPoints=lpSettings->mfArmourPoints;
    mfMinWear=lpSettings->mfMinWear;
    mfArmourScaling=lpSettings->mfArmourScaling;
};

