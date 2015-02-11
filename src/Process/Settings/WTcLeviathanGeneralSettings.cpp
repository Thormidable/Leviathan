
#include "../../main.h"

#define FREE_THRUST 100.0f
#define FREE_ANGLE_THRUST 50.0f

uint8 cLeviathanComponentSettings::Type(){return LV_COMPONENT_VOID;};

vRenderNode *cLeviathanComponentSettings::Node(){return mpNode;};

cLeviathanComponentSettings::cLeviathanComponentSettings(float lfHealth,cFoundationSettingsList *lpFoundationList,vArmourSettings *lpArmour,cLeviathanReactorSettings *lpReactor,float lfEnergyCost)
{
    mfHealth=lfHealth;
    mpFoundations=new cFoundationSettingsList(lpFoundationList);
    mpNode=0;
    mfEnergyCost=lfEnergyCost;
    mpReactor=lpReactor;
    mpArmour=lpArmour;
    if(mpReactor) mpReactor->AddPowerUse(mfEnergyCost);
};

cLeviathanComponentSettings::cLeviathanComponentSettings(cLeviathanComponentSettings *lpSettings)
{
    mfHealth=lpSettings->mfHealth;
    mpFoundations=new cFoundationSettingsList(lpSettings->mpFoundations);
    mpNode=0;
    mfEnergyCost=lpSettings->mfEnergyCost;
    mpReactor=lpSettings->mpReactor;
    if(lpSettings->mpArmour) mpArmour=vArmourSettings::MakeArmour(lpSettings->mpArmour);
    else mpArmour=0;
    if(mpReactor) mpReactor->AddPowerUse(mfEnergyCost);
};

cLeviathanComponentSettings::cLeviathanComponentSettings(const cLeviathanComponentSettings &lpSettings)
{
    mfHealth=lpSettings.mfHealth;
    mpFoundations=new cFoundationSettingsList(lpSettings.mpFoundations);
    mpNode=0;
    mfEnergyCost=lpSettings.mfEnergyCost;
    mpReactor=lpSettings.mpReactor;
    if(lpSettings.mpArmour) mpArmour=vArmourSettings::MakeArmour(lpSettings.mpArmour);
    else mpArmour=0;

    if(mpReactor)
    {
        mpReactor->AddPowerUse(mfEnergyCost);
        if(mpArmour) mpArmour->ReactorPower(mpReactor);
    }
};


cLeviathanComponentSettings::~cLeviathanComponentSettings()
{
    if(mpReactor) mpReactor->AddPowerUse(-mfEnergyCost);
    delete mpArmour;
    mpArmour=0;
};
