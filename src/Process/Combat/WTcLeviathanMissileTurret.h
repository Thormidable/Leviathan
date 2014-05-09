#ifndef __WTCLEVIATHANMISSILETURRET_H__
#define __WTCLEVIATHANMISSILETURRET_H__


class cLeviathanMissileTurret : public cLeviathanTurret

{
 cMissileSettings *mpMissileSettings;

 float mfReloadRate;
 float mfReloadState;
 float mfRange;

 cAudioObject *mpLaunch;
public:

	cLeviathanMissileTurret(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings);
	cLeviathanMissileTurret(cLeviathanMissileTurretSettings *lpSettings);
	void Run();
	//void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);
};



#endif
