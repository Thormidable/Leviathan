#ifndef __WTCLEVIATHANTURRET_H__
#define __WTCLEVIATHANTURRET_H__

class cLeviathanTurret : public cLeviathanComponent
{
protected:
    cNodeList *mpHull;
    float mfTrackSpeed;
 	float mfLowYaw;
 	float mfHighYaw;
 	float mfLowPitch;
 	float mfHighPitch;
 	float mfReloadRate;
public:
  cLeviathanTurret(cLeviathanTurretSettings *lpSettings);

  bool TrackPoint(float *lpPoint);
  bool TrackVector(float *lpVector);
  void UpdateHitSelf();
  bool HitSelf();
  bool InRange(float lfRange);
  bool WillHitSelf();

 cCollisionObject *lpLOSColl;
 cBeam *lpLOSBeam;

 void Stop();

};

/*

class cLeviathanProjectileTurretSettings : public cLeviathanTurretSettings
{
 public:
 float mfProjSpeed;
 float mfProjDamage;

cLeviathanProjectileTurretSettings(vRenderNode *lpNode,float lfHealth,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate,
 float lfProjSpeed,
 float lfProjDamage,
 cMatrix4 *lpMatrix=0);


cLeviathanProjectileTurretSettings(cLeviathanComponentSettings *lpSettings,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate,
 float lfProjSpeed,
 float lfProjDamage);

cLeviathanProjectileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfProjSpeed,float lfProjDamage);
};


class cLeviathanProjectileTurret : public cLeviathanTurret

{
 cPredictiveTracking *mpTracker;
 float mfReloadState;
 float mfReloadRate;
 cLeviathanProjectileTurretSettings *mpProjSettings;


public:
	cLeviathanProjectileTurret(cLeviathanProjectileTurretSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth(float *lfDamage);
};




class cLeviathanBeamTurretSettings : public cLeviathanTurretSettings
{
public:
    cBeam mpBeam;
    cMeshCollision *mpBeamColl;

    float mfFireDelay;
    float mfRechargeRate;
    float mfFullRecharge;
    float mfDischargeRate;
    float mfDamageFactor;
    cRGBA mcBeamColor;

    cLeviathanBeamTurretSettings(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,float lfDamageFactor,cRGBA lcBeamColor);
}


class cLeviathanBeamTurret : public cLeviathanTurret

{
protected:
 cBeam *mpBeam;
 cCollisionObject *mpBeamColl;

 float mfFireDelay;
 float mfDelayTimer;
 float mfRechargeRate;
 float mfCharge;
 float mfFullRecharge;
 float mfDischargeRate;
 float mfChargeChange;

 cRGBA mcBeamColor;


public:
	cLeviathanBeamTurret(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth(float *lfDamage);
};

class cLeviathanTractorBeam : public cLeviathanBeamTurret
{
 float mfDampeningFactor;
public:
    cLeviathanTractorBeam(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor,float lfDampeningFactor);

    void Run();
};



class cLeviathanMissileTurretSettings : public cLeviathanTurretSettings
{
public:
    cLeviathanMissileTurretSettings(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings);

    cMissileSettings *mpMissileSettings;

    float mfReloadRate;
    float mfReloadState;
    float mfRange;

}

class cLeviathanMissileTurret : public cLeviathanTurret

{
 cMissileSettings *mpMissileSettings;

 float mfReloadRate;
 float mfReloadState;
 float mfRange;

 cAudioObject *mpLaunch;
public:

	cLeviathanMissileTurret(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings);
	void Run();
	//void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth(float *lfDamage);
};
*/


#endif
