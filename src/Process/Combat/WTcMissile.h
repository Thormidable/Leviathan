#ifndef __WTCMISSILE_H__
#define __WTCMISSILE_H__

class cChaffCharge;

class cMissile : public cProcess
{
protected:
cMapDisplayObject *mpMapDisp;
 cModel *mpHull;
 float mfHealth;
 cCollisionObject *mpHullColl;
 cGameTarget mpTarget;
 cMissileSettings *mpSettings;
 cMomentum *mpMomentum;
 cImage *mpReticule;

 float mf180Delay;
 bool mbTracking;


public:

    static cChaffCharge *spChaffDeployed;

  cMissile(cMissileSettings *lpSettings);
  void Run();
  void Stop();
  bool UserSignal(SIGNAL lsSignal,void *lpData);
  virtual void Detonate()=0;

  void ChaffCheck();
};



class cExplosiveMissile : public cMissile
{

public:
 cExplosiveMissile(cExplosiveMissileSettings *lpSettings);

 void Detonate();
};


class cLaserMissile : public cMissile
{

public:
 cLaserMissile(cLaserMissileSettings *lpSettings);

 void Detonate();
};

class cEMPMissile : public cMissile
{

public:
    cEMPMissile(cEMPMissileSettings *lpSettings);
    void Detonate();
};

class cMWMissile : public cMissile
{
protected:
    uint8 miMunitions;
    float mfSpread;
    cMissileSettings *mpMunitions;
public:
    cMWMissile(cMWMissileSettings *lpSettings);
    void Detonate();
    virtual void TargetMunition();
};

class cMWMissileScatter : public cMWMissile
{

public:
    cMWMissileScatter(cMWMissileSettings *lpSettings);
    void TargetMunition();
};

class cChaffCharge : public cProcess
{
    friend class cMissile;
 c3DVf mvSpeed;
 float mfDelay;
 float mfSize;
 float mfCurrentSize;
 cBillBoard *mpCharge;
 cCollisionObject *mpColl;
 bool mbChaffBlind;

public:
    cChaffCharge(cChaffSettings *lpSettings);
    void Run();
    void Stop();


 static void ActivateChaff(cChaffSettings *lpSettings);

};

#endif
