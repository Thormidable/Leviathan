#ifndef __WTCLEVIATHANSHIELD_H__
#define __WTCLEVIATHANSHIELD_H__

class cLeviathanShield : public cLeviathanComponent
{
 cModel *mpHull;
 cShield *mpShield;
public:
	cLeviathanShield(cLeviathanComponentSettings *lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor);

    cLeviathanShield(cLeviathanShieldSettings *lpSettings);

	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);

};



#endif
