#ifndef __WTCLEVIATHANPROJECTILETURRET_H__
#define __WTCLEVIATHANPROJECTILETURRET_H__

class cLeviathanProjectileTurret : public cLeviathanTurret

{
 cPredictiveTracking *mpTracker;
 float mfReloadState;
 float mfProjSpeed;
 cDamage mcBulletDamage;


public:
	cLeviathanProjectileTurret(cLeviathanProjectileTurretSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);
};


#endif
