
#include "../../main.h"

cPlanningTurret::cPlanningTurret(cLeviathanTurretSettings *lpSettings) : cPlanningComponent(lpSettings)
{

    mpTurret=_CREATE(cNodeList(lpSettings->mpMesh,mpComponentNode));
    //SetProgram(mpTurret);

    mpFollowing=mpTurret;

    mpColl=_CREATE(cCollisionObject(mpTurret,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(-10.0f,10.0f,0.0f,40.0f,-10.0f,10.0f);

    mcTrackingSpeed.String("Track: ");
    mcTrackingSpeed.Data(lpSettings->DisplayTrackSpeed());

    mcArc.Yaw(c2DVf(lpSettings->mfLowYaw,lpSettings->mfHighYaw));
    mcArc.Pitch(c2DVf(lpSettings->mfLowPitch,lpSettings->mfHighPitch));
    mcArc.Range(500.0f);
    mcArc.ConstructArcs();

    mcArcRange.Yaw(c2DVf(lpSettings->mfLowYaw,lpSettings->mfHighYaw));
    mcArcRange.Pitch(c2DVf(lpSettings->mfLowPitch,lpSettings->mfHighPitch));
    mcArcRange.Range(lpSettings->Range());
    mcArcRange.ConstructArcs();

    miDataItems+=1;
    mcBox.DataItems(miDataItems);
}


void cPlanningTurret::Run()
{
    cPlanningComponent::Run();
    if(cPlanningLeviathan::mcKeyToggles[15].On() && mcArc.Created())
    {
        mcArc.Destroy();
        mcArcRange.Create(mpComponentNode);
    }
    if(cPlanningLeviathan::mcKeyToggles[15].Off() && mcArcRange.Created())
    {
        mcArc.Create(mpComponentNode);
        mcArcRange.Destroy();
    }

}

void cPlanningTurret::Stop()
{
	cPlanningComponent::Stop();
  _KILL(mpTurret);
  mpTurret=0;
}

void cPlanningTurret::DisplayOthers(c3DVf &lfPos)
{
  mcTrackingSpeed.Display();
};

void cPlanningTurret::CreateOthers()
{

  mcTrackingSpeed.Create();
  if(cPlanningLeviathan::mcKeyToggles[15].On()) mcArcRange.Create(mpComponentNode);
  else mcArc.Create(mpComponentNode);
};
void cPlanningTurret::DestroyOthers()
{
  mcTrackingSpeed.Destroy();
  if(mcArc.Created()) mcArc.Destroy();
  if(mcArcRange.Created()) mcArcRange.Destroy();
};


