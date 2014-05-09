#ifndef __WTCLEVIATHANBEAMTURRET_H__
#define __WTCLEVIATHANBEAMTURRET_H__


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
 float mfDamageFactor;

 cRGBA mcBeamColor;


public:
	cLeviathanBeamTurret(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor);
	cLeviathanBeamTurret(cLeviathanBeamTurretSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);
};

#endif
