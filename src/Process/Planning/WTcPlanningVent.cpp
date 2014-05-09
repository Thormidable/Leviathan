#include "stdafx.h"
#include "../../main.h"

cPlanningVent::cPlanningVent(cLeviathanVentSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpVent=_CREATE(cModel(mpComponentNode));
    mpVent->Mesh(lpSettings->mpVent);
    SetProgram(mpVent);

    mpFollowing=mpVent;

    mpColl=_CREATE(cCollisionObject(mpVent,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpVentColl);

    mcCooling.String("Min Cool: ");
    mcCooling.Data(lpSettings->mfBaseCool);

    mcOpen.String("Max Cool: ");
    mcOpen.Data(lpSettings->mfMaxCool);

    miDataItems+=2;
    mcBox.DataItems(miDataItems);
}

void cPlanningVent::Run()
{
    cPlanningComponent::Run();

}

void cPlanningVent::Stop()
{
	cPlanningComponent::Stop();
  _KILL(mpVent);
  mpVent=0;
}

void cPlanningVent::DisplayOthers(c3DVf &lfPos)
{
  mcCooling.Display();
  mcOpen.Display();
};

void cPlanningVent::CreateOthers()
{
  mcCooling.Create();
  mcOpen.Create();
};
void cPlanningVent::DestroyOthers()
{
  mcCooling.Destroy();
  mcOpen.Destroy();
};

cTexture *cPlanningVent::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("VentPVE");
    else return _GET_TEXTURE_FILE("VentNVE");
};
