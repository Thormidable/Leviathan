#ifndef __WTCLEVIATHANREACTOR_H__
#define __WTCLEVIATHANREACTOR_H__

class cLeviathanReactor : public cLeviathanComponent
{
 cModel *mpReactor;

 float mfHeatFactor;
 float mfBaseHeat;
 float mfDamageHeatFactor;
 float mfTemp;
 double mfInvOverload;
 float mfMaxPowerGeneration;
 float mfGenerated;
 float mfMaxHealthInv;
 cDamage mcOverloadDamage;
public:
	cLeviathanReactor(cLeviathanReactorSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();



void ForceGenerateEnergy(float lfEnergy);
bool GenerateEnergy(float lfEnergy);
void Cool(float lfCooling);
float ReactorTemp();

    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);
};



#endif
