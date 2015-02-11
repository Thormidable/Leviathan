
#include "../../main.h"

cPlanningThruster::cPlanningThruster(cLeviathanThrusterSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpThruster=_CREATE(cModel(mpComponentNode));
    mpThruster->Mesh(lpSettings->mpThruster);
    SetProgram(mpThruster);

    mpFollowing=mpThruster;

    mpColl=_CREATE(cCollisionObject(mpThruster,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpThrusterColl);

    mcThrust.String("Thrust: ");
    mcThrust.Data(lpSettings->mfStartMaxThrust*100);

    miDataItems+=1;
    mcBox.DataItems(miDataItems);
}

void cPlanningThruster::Run()
{
    cPlanningComponent::Run();

}

void cPlanningThruster::Stop()
{
	cPlanningComponent::Stop();
  _KILL(mpThruster);
  mpThruster=0;
}

void cPlanningThruster::DisplayOthers(c3DVf &lfPos)
{
  mcThrust.Display();
};

void cPlanningThruster::CreateOthers()
{
    mcThrust.Create();
};
void cPlanningThruster::DestroyOthers()
{
  mcThrust.Destroy();
};

cTexture *cPlanningThruster::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("ThrusterPVE");
    else return _GET_TEXTURE_FILE("ThrusterNVE");
};
