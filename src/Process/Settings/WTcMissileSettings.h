#ifndef __WTCMISSILESETTINGS_H__
#define __WTCMISSILESETTINGS_H__

class vMissileSettings
{
public:
    cGameTarget mpTarget;
    virtual float DetonationDamage()=0;
    virtual uint8 Type(){return MISSILE_TYPE_VOID;};
    virtual string TypeString(){return "Void";};
};

class cChaffSettings : public vMissileSettings
{

public:
    cChaffSettings(cMatrix4 *lpSource,uint16 liCharges,float lfSpread,float lfSize,float lfDelay,cRGBA lcColor,cMomentum *lpCurSpeed);
    cMatrix4 *mpSource;
    uint16 miCharges;
    float mfSpreadRate;
    float mfChargeSize;
    float mfChargeDelay;
    cRGBA mcFlareColor;
    cMomentum *mpCurSpeed;
    float DetonationDamage(){return 0.0f;};

    uint8 Type(){return MISSILE_TYPE_CHAFF;};
    string TypeString(){return "Chaff";};
};

class cMissileSettings : public vMissileSettings
{
    public:
 cMatrix4 *mpMatrix;
 cMesh *mpMesh;
 cMomentum *mpMomentumBase;
 cTexture *mpTexture;
 c3DVf mfOffset;
 uint16 miFilter;
 float mfThrust;
 float mfSideThrust;
 float mfTrack;
 float mfThrustLimit;
 float mfHealth;
 float mfDetonationDistance;
 float mfSize;
 cDamage mcDamage;

  float DetonationSize();
  float DetonationDamage();
  cMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase);
  cMissileSettings(cMissileSettings *lpOther);

};

class cExplosiveMissileSettings : public cMissileSettings
{

public:
    cExplosiveMissileSettings(cMissileSettings *lpSettings,float lfExplosionSize,cDamage lfExplosionDamage);
    cExplosiveMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfExplosionSize,cDamage lfExplosionDamage);

    uint8 Type(){return MISSILE_TYPE_EXPLOSIVE;};
    string TypeString(){return "Explosive";};
};

class cLaserMissileSettings : public cMissileSettings
{
  public:
  cLaserMissileSettings(cMissileSettings *lpSettings,float lfLaserLength,cDamage lfLaserDamage);
  cLaserMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfExplosionSize,cDamage lfExplosionDamage);

  uint8 Type(){return MISSILE_TYPE_LASER;};
  string TypeString(){return "Laser";};
};

class cEMPMissileSettings : public cMissileSettings
{
  public:
   cEMPMissileSettings(cMissileSettings *lpSettings,float lfEMPSize);
   cEMPMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,float lfEMPSize);

   float DetonationDamage();

   uint8 Type(){return MISSILE_TYPE_EMP;};
   string TypeString(){return "EMP";};

};

class cMWMissileSettings : public cMissileSettings
{
  public:
        cMWMissileSettings(cMissileSettings *lpSettings,uint8 liMunitions,float lfSpread,cMissileSettings *lpMunitionSettings);
        cMWMissileSettings(cMatrix4 *lpMatrix,string lsMesh, string lsTexture,c3DVf lfOffset,cGameTarget lpTarget,uint16 liFilter,float lfThrust,float lfSideThrust,float lfTrack,float lfThrustLimit,float lfHealth,float lfDetonationDistance,cMomentum *lpMomentumBase,uint8 liMunitions,float lfSpread,cMissileSettings *lpMunitionSettings);

        uint8 miMunitions;
        float mfSpread;
        cMissileSettings *mpMunitionSettings;

        float DetonationDamage();

        uint8 Type();
        string TypeString();
};

#endif
