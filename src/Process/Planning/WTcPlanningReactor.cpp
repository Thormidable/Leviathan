#include "stdafx.h"
#include "../../main.h"

cPlanningReactor::cPlanningReactor(cLeviathanReactorSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpSettings=lpSettings;

    mpReactor=_CREATE(cModel(mpComponentNode));
    mpReactor->Mesh(lpSettings->mpReactor);
    SetProgram(mpReactor);

    mpFollowing=mpReactor;

    mpColl=_CREATE(cCollisionObject(mpReactor,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpColl);



    mcMaxGeneration.String("Max Heat: ");
    mcMaxGeneration.Data(lpSettings->mfMaxPower);

    mcPowerRequired.String("Ship Use: ");
    mcPowerRequired.Data(lpSettings->mfMaxPowerRequired);

    mcBaseHeat.String("Reactor Gen: ");
    mcBaseHeat.Data(lpSettings->mfBaseHeat);

    mcBaseVentCooling.String("Vent Base:");
    mcBaseVentCooling.Data(lpSettings->mfBaseVent);

    mcMaxCooling.String("Vent Max:");
    mcMaxCooling.Data(lpSettings->mfMaxVent);

    mcMaxHeatFactor.String("Heat Factor: ");
    mcMaxHeatFactor.Data(1.0f+lpSettings->mfDamageHeatFactor);

   if(lpSettings->mfPowerArmour>0.0f)
   {
        mcPoweredArmourHeat.String("Power Armour: ");
        mcPoweredArmourHeat.Data(lpSettings->mfPowerArmour);

        miDataItems+=7;
        mcBox.DataItems(miDataItems);

        mbPowerArmour=true;
   }
   else
   {
        mcBox.DataItems(6);
        mbPowerArmour=false;
   }
}


void cPlanningReactor::Run()
{
    cPlanningComponent::Run();

}

void cPlanningReactor::Stop()
{
cPlanningComponent::Stop();
 _KILL(mpReactor);
 mpReactor=0;

}

void cPlanningReactor::DisplayOthers(c3DVf &lfPos)
{
    mcMaxGeneration.Display();
    mcPowerRequired.Display();
    mcBaseHeat.Display();
    mcBaseVentCooling.Display();
    mcMaxCooling.Display();
    mcMaxHeatFactor.Display();
    if(mbPowerArmour) mcPoweredArmourHeat.Display();

};
void cPlanningReactor::CreateOthers()
{
    mcMaxGeneration.Create();
        mcPowerRequired.Create();
        mcBaseHeat.Create();
        mcBaseVentCooling.Create();
        mcMaxCooling.Create();
        mcMaxHeatFactor.Create();
        if(mbPowerArmour) mcPoweredArmourHeat.Create();
};
void cPlanningReactor::DestroyOthers()
{
    mcMaxGeneration.Destroy();
    mcPowerRequired.Destroy();
    mcBaseHeat.Destroy();
    mcBaseVentCooling.Destroy();
    mcMaxCooling.Destroy();
    mcMaxHeatFactor.Destroy();
    if(mbPowerArmour) mcPoweredArmourHeat.Destroy();
};

cTexture *cPlanningReactor::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("ReactorPVE");
    else return _GET_TEXTURE_FILE("ReactorNVE");
};
