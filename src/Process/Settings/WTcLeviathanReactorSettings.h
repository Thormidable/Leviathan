#ifndef __WTCLEVIATHANREACTORSETTINGS_H__
#define __WTCLEVIATHANREACTORSETTINGS_H__

class cLeviathanReactor;

class cLeviathanReactorSettings : public cLeviathanComponentSettings
{
  public:
    cLeviathanReactorSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseHeat,float lfMaxPower,float lfDamageHeatFactor,double lfOverload);
    cLeviathanReactorSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfBaseHeat,float lfMaxPower,float lfDamageHeatFactor,double lfOverload);

    float mfInvMaxHealth;
    cMesh *mpReactor;
    cMeshFileCollision *mpColl;

    cLeviathanReactor *mpReactorComp;

    float mfBaseHeat;
    float mfMaxPower;
    float mfDamageHeatFactor;
    double mfOverload;

    float mfMaxPowerRequired;
    float mfBaseVent;
    float mfMaxVent;

    float mfPowerArmour;

    uint8 Type();
    cLeviathanReactorSettings *Reactor();

    void AddPowerUse(float lfHeat);
    void AddBaseCooling(float lfCool);
    void AddMaxCooling(float lfCool);
    void AddPowerArmour(float lfEnergy);
};

#endif
