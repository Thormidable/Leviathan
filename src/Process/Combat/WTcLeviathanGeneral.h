#ifndef __WTCLEVIATHANGENERAL_H__
#define __WTCLEVIATHANGENERAL_H__

//extern cLeviathanTraining *gpLeviathan;

class cLeviathanDeath : public cProcess
{
 float mfLife;
 vRenderNode *mpComponentNode;
public:
	cLeviathanDeath(vRenderNode *lpNode,float Life);
	void Run();
	void Stop();
};

class cLeviathanDamage : public cProcess
{
 cLeviathanComponent *mpComp;
 float mfRate;
 float mfTimer;
 static cParticleSettings *mpSettings;
public:
	cLeviathanDamage(cLeviathanComponent *lpMesh,float lfRate);
	void Run();
	void Stop();
	void Rate(float lfRate);




};

class cLeviathanComponent : public cProcess, public cFoundationTracking
{
    friend class cLeviathan;
protected:
 static cParticleSettings *mpFlameTrailSettings;
 bool mbReactorDeath;
 float mfHealth;
 float mfMaxHealthInv;
 float mfEnergyCost;
 cLeviathanDamage *mpDamage;
 cAudioObject *mpTargeted;
 vArmour *mpArmour;
public:
 cLeviathanComponent *mpTreeBase;
 cMomentumFRI *mpMoment;
 cLeviathanReactor *mpReactor;

cLeviathanComponent(cLeviathanComponentSettings *lpSettings);
void Run();
void Stop();

bool UserSignal(SIGNAL lsSignal,void *lpData);

    virtual void ReduceHealth()=0;
    void SignalDeath();
    cMomentumFRI *Momentum();
	void PlayTargetedNoise();
	void FlameTrail(cDamage *lfCentre);

    virtual void UpdateFieldColors(cCombatStatusBox *lpPoint);
	virtual void Display(cCombatStatusBox *lpPoint);

	float Health();

};



#endif
