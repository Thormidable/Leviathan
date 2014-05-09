#ifndef __WTCLEVIATHAN_H__
#define __WTCLEVIATHAN_H__

class cLeviathan : public cProcess
{

public:

    static vRenderNode *spLast;
     float	mfSensorDegredation;
     cMatrix4 mpTarget;

     cModel *mpLightBase;
     cLight *mpLight;
      vRenderNode *mpLightCentre;
      static cParticleHandler *mpLeviathanParticleHandler;

	  cLeviathanComponent **mpComponents;
	  uint32 miComponents;

      cDamage mcReactorDamage;

public:
    cLeviathan(cLeviathanSettings *mpSettings);

void Run();
void Stop();
bool UserSignal(SIGNAL lsSignal,void *lpData);
void SetProgram(cRenderObject *lpObject);
cMatrix4 *Target(){return &mpTarget;};
void CoolReactor(float lfCooling);
void ReactorHeat(float lfHeating);
float ChargeEnergy(float mfEnergy);
bool UseEnergy(float lfEnergy);
void SensorInput(float lfDegredation);

cLeviathanComponent *LowestHealth();

void CheckFoundations(cLeviathanComponent* lpComp,vRenderNode *lpNode);

};

extern cLeviathan *gpLeviathan;

#endif
