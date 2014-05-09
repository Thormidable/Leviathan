#ifndef __WTCPLANNINGREACTOR_H__
#define __WTCPLANNINGREACTOR_H__

class cPlanningReactor : public cPlanningComponent
{
    cModel *mpReactor;
    cCollisionObject *mpColl;

    cLeviathanReactorSettings *mpSettings;

    cComponentTextField<float> mcBaseHeat;
    cComponentTextField<float> mcBaseVentCooling;
    cComponentTextField<float> mcMaxCooling;
    cComponentTextField<float> mcPowerRequired;
    cComponentTextField<float> mcMaxGeneration;
    cComponentTextField<float> mcMaxHeatFactor;
    cComponentTextField<float> mcPoweredArmourHeat;
    bool mbPowerArmour;

public:
    cPlanningReactor(cLeviathanReactorSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();
};

#endif
