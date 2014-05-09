#ifndef __WTCFIGHTER_H__
#define __WTCFIGHTER_H__




class cFighter : public cProcess
{
public:
 float lfThrust;
 float mfHealth;
 cModel *mpHull;
 cCollisionObject *mpHullColl,*mpBeamColl;
 bool lbCollSearch;
 cDamage mcBulletDamage;
 cParticleGroup *mpFire;

 float mfParticleRate;

 cPredictiveTracking *mpTrack;
 float *lpVertex;
 uint32 miState;

 float mfReload;
 float mfFleeingTime;

 cBeamMesh *mpBeam;
 cAttributeArray4 *mpStore;
 cUniformMatrix4 *mpPerspective,*mpGlobal;

public:

cFighter(cDamage lcDamage);
void Run();
void Stop();
bool UserSignal(SIGNAL lsSignal,void *lpData);

};

#endif
