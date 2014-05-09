#include "stdafx.h"
#include "../../main.h"

float cDamage::mfFinalDamage=0.0f;

cDamage::cDamage(float lfDamage,uint8 liType)
{
 mfDamage=lfDamage;
 miType=liType;
};

cDamage::cDamage(cDamageSettings *lpSettings)
{
  mfDamage=lpSettings->mfDamage;
  miType=lpSettings->miType;
};


cReductiveArmour::cReductiveArmour(cReductiveArmourSettings *lpSettings)
{
    memcpy(mpArmour,lpSettings->mpArmour,sizeof(float)*DAMAGE_TYPES);
};

void cReductiveArmour::Damage(cDamage *lpDam)
{
  if(lpDam->miType==DAMAGE_TYPE_THROUGH) {cDamage::mfFinalDamage=lpDam->mfDamage; return;}
    cDamage::mfFinalDamage=lpDam->mfDamage-mpArmour[lpDam->miType];
    if(cDamage::mfFinalDamage<0.0f) cDamage::mfFinalDamage=0.0f;
};

cPoweredArmour::cPoweredArmour(cPoweredArmourSettings *lpSettings,cLeviathanReactor *lpReactor)
{
    mpReactor=lpReactor;
    mfDamageEnergyConversion=lpSettings->mfDamageEnergyConversion;
    mfDamageConverted=0.0f;
    mfMaxDamageConversion=lpSettings->mfMaxDamageConversion;

};

void cPoweredArmour::Damage(cDamage *lpDam)
{
 if(lpDam->miType==DAMAGE_TYPE_THROUGH) cDamage::mfFinalDamage=lpDam->mfDamage;

 float lfTemp;
 if(lpDam->mfDamage+mfDamageConverted>mfMaxDamageConversion) {lfTemp=lpDam->mfDamage+mfDamageConverted-mfMaxDamageConversion; mfDamageConverted=mfMaxDamageConversion;}
 else {lfTemp=mfMaxDamageConversion-mfDamageConverted; mfDamageConverted+=lfTemp;}

  if(!mpReactor->GenerateEnergy(lfTemp*mfDamageEnergyConversion))
  {
    cDamage::mfFinalDamage=lpDam->mfDamage;
  }
  else
  {
    cDamage::mfFinalDamage=lpDam->mfDamage-lfTemp;
  }
};

void cPoweredArmour::Reset()
{
    mfDamageConverted=0.0f;
};

void vArmour::Damage(cDamage *lpDam)
{
    cDamage::mfFinalDamage=lpDam->mfDamage;
};

vArmour *vArmour::MakeArmour(vArmourSettings *lpArmour,cLeviathanReactor *lpReactor)
{
 if(lpArmour)
 {
    if(dynamic_cast<cReductiveArmourSettings*>(lpArmour)) return new cReductiveArmour(dynamic_cast<cReductiveArmourSettings*>(lpArmour));
    if(dynamic_cast<cPoweredArmourSettings*>(lpArmour)) return new cPoweredArmour(dynamic_cast<cPoweredArmourSettings*>(lpArmour),lpReactor);
    if(dynamic_cast<cBrittleArmourSettings*>(lpArmour)) return new cBrittleArmour(dynamic_cast<cBrittleArmourSettings*>(lpArmour));
    if(dynamic_cast<cTriangularArmourSettings*>(lpArmour)) return new cTriangularArmour(dynamic_cast<cTriangularArmourSettings*>(lpArmour));
 }
 return new vArmour();
};

cDamage cDamage::operator=(cDamage lpOther)
{
    mfDamage=lpOther.mfDamage;
    miType=lpOther.miType;
    mfPos=lpOther.mfPos;
    return *this;
};

cBrittleArmour::cBrittleArmour(cBrittleArmourSettings *lpSettings)
{
    mfBreakingPoint=lpSettings->mfBreakingPoint;
    mfArmourPoints=lpSettings->mfArmourPoints;
    mfInvArmour=1.0f/mfArmourPoints;
};

void cBrittleArmour::Damage(cDamage *lpDam)
{
    if(lpDam->mfDamage>mfBreakingPoint)
    {
      cDamage::mfFinalDamage=lpDam->mfDamage;
      mfArmourPoints=0.0f;
      mfBreakingPoint=0.0f;
    }
    else
    {
        if(mfArmourPoints>lpDam->mfDamage)
        {
            mfArmourPoints-=lpDam->mfDamage;
            cDamage::mfFinalDamage=0.0f;
        }
        else
        {
            cDamage::mfFinalDamage=lpDam->mfDamage-mfArmourPoints;
            mfArmourPoints=0.0f;
        }
    }
}


cTriangularArmour::cTriangularArmour(cTriangularArmourSettings *lpSettings)
{
    mfArmourPoints=lpSettings->mfArmourPoints;
    mfArmourScaling=lpSettings->mfArmourScaling;
    mfMinWear=lpSettings->mfMinWear;
    mfInvArmour=1.0f/mfArmourPoints;
};

void cTriangularArmour::Damage(cDamage *lpDam)
{
    float lfWear=0.0f;
    if(lpDam->mfDamage>mfArmourPoints)
    {
        cDamage::mfFinalDamage=(lpDam->mfDamage-mfArmourPoints);
        lfWear=cDamage::mfFinalDamage*mfArmourScaling;
    }
    else
    {
        cDamage::mfFinalDamage=0.0f;
    }

    if(lfWear<mfMinWear) mfArmourPoints-=mfMinWear;
    else mfArmourPoints-=lfWear;
};

float cReductiveArmour::ArmourStatus(){return 1.0f;};
float cPoweredArmour::ArmourStatus(){return 1.0f;};
float cBrittleArmour::ArmourStatus(){return mfInvArmour*mfArmourPoints;};
float cTriangularArmour::ArmourStatus(){return mfInvArmour*mfArmourPoints;};
