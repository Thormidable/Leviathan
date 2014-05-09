#include "stdafx.h"
#include "../../main.h"

cChaffSettings::cChaffSettings(cMatrix4 *lpSource,uint16 liCharges,float lfSpread,float lfSize,float lfDelay,cRGBA lcColor,cMomentum *lpCurSpeed)
{
    mpSource=lpSource;
    miCharges=liCharges;
    mfSpreadRate=lfSpread;
    mfChargeSize=lfSize;
    mfChargeDelay=lfDelay;
    mcFlareColor=lcColor;
    mpCurSpeed=lpCurSpeed;
};

cMissileSettings::cMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase)
{
     mpMatrix=lpMatrix;
     mpMesh=_GET_MESH_FILE(lsMesh.c_str());
     mpTexture=_GET_TEXTURE_FILE(lsTexture.c_str());
     mfOffset=lfOffset;
     mpTarget=lpTarget;
     mfThrust=lfThrust;
     mfThrustLimit=lfThrustLimit;
     mfTrack=lfTrack;
     mfHealth=lfHealth;
     mfSideThrust=lfSideThrust;
     miFilter=liFilter;
     mfDetonationDistance=lfDetonationDistance*lfDetonationDistance;
     mpMomentumBase=lpMomentumBase;
}

cMissileSettings::cMissileSettings(cMissileSettings *lpOther)
{
     mpMatrix=lpOther->mpMatrix;
     mpMesh=lpOther->mpMesh;
     mpTexture=lpOther->mpTexture;
     mfOffset=lpOther->mfOffset;
     mpTarget=lpOther->mpTarget;
     mfThrust=lpOther->mfThrust;
     mfThrustLimit=lpOther->mfThrustLimit;
     mfTrack=lpOther->mfTrack;
     mfHealth=lpOther->mfHealth;
     mfSideThrust=lpOther->mfSideThrust;
     miFilter=lpOther->miFilter;
     mfDetonationDistance=lpOther->mfDetonationDistance;
     mpMomentumBase=lpOther->mpMomentumBase;
}

float cMissileSettings::DetonationSize(){return mfSize;};
float cMissileSettings::DetonationDamage(){return mcDamage.mfDamage;};
float cEMPMissileSettings::DetonationDamage(){return 0.0f;};

cExplosiveMissileSettings::cExplosiveMissileSettings(cMissileSettings *lpSettings,float lfExplosionSize,cDamage lfExplosionDamage) : cMissileSettings(lpSettings)
{
    mfSize=lfExplosionSize;
    mcDamage=lfExplosionDamage;
};
cExplosiveMissileSettings::cExplosiveMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfExplosionSize,cDamage lfExplosionDamage) : cMissileSettings(
    lpMatrix,lsMesh,lsTexture,lfOffset,lpTarget,liFilter,lfThrust,lfSideThrust,lfTrack,lfThrustLimit,lfHealth,lfDetonationDistance,lpMomentumBase)
{
    mfSize=lfExplosionSize;
    mcDamage=lfExplosionDamage;
};

cLaserMissileSettings::cLaserMissileSettings(cMissileSettings *lpSettings,float lfLaserLength,cDamage lfLaserDamage) : cMissileSettings(lpSettings)
{
    mfSize=lfLaserLength;
    mcDamage=lfLaserDamage;
};
cLaserMissileSettings::cLaserMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfLaserLength,cDamage lfLaserDamage) : cMissileSettings(
    lpMatrix,lsMesh,lsTexture,lfOffset,lpTarget,liFilter,lfThrust,lfSideThrust,lfTrack,lfThrustLimit,lfHealth,lfDetonationDistance,lpMomentumBase)
{
    mfSize=lfLaserLength;
    mcDamage=lfLaserDamage;
};

cEMPMissileSettings::cEMPMissileSettings(cMissileSettings *lpSettings,float lfEMPSize) : cMissileSettings(lpSettings)
{
    mfSize=lfEMPSize;
    mcDamage.mfDamage=0.0f;
};
cEMPMissileSettings::cEMPMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfEMPSize) : cMissileSettings(
    lpMatrix,lsMesh,lsTexture,lfOffset,lpTarget,liFilter,lfThrust,lfSideThrust,lfTrack,lfThrustLimit,lfHealth,lfDetonationDistance,lpMomentumBase)
{
    mfSize=lfEMPSize;
    mcDamage.mfDamage=0.0f;
};

cMWMissileSettings::cMWMissileSettings(cMissileSettings *lpSettings,uint8 liMunitions,float lfSpread,cMissileSettings *lpMunitionSettings) : cMissileSettings(lpSettings)
{
    mfSpread=lfSpread;
    miMunitions=liMunitions;
    mpMunitionSettings=lpMunitionSettings;
};
cMWMissileSettings::cMWMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,uint8 liMunitions,float lfSpread,cMissileSettings *lpMunitionSettings) :
cMissileSettings(lpMatrix,lsMesh,lsTexture,lfOffset,lpTarget,liFilter,lfThrust,lfSideThrust,lfTrack,lfThrustLimit,lfHealth,lfDetonationDistance,lpMomentumBase)
{
    mfSpread=lfSpread;
    miMunitions=liMunitions;
    mpMunitionSettings=lpMunitionSettings;
};

float cMWMissileSettings::DetonationDamage(){return 0.0f;};

uint8 cMWMissileSettings::Type(){return MISSILE_TYPE_MW;};
string cMWMissileSettings::TypeString(){return "MW";};
