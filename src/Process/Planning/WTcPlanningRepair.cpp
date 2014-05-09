#include "stdafx.h"
#include "../../main.h"

cPlanningRepair::cPlanningRepair(cLeviathanRepairSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpModel=_CREATE(cModel(mpComponentNode));
    mpModel->Mesh(lpSettings->mpMesh);
    SetProgram(mpModel);

    mpFollowing=mpModel;

    mpColl=_CREATE(cCollisionObject(mpModel,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpCollision);


	mcRepairRate.String("Repair Rate:");
	mcRepairRate.Data(lpSettings->mfRepairRate);

	mcRepairLimit.String("Repair Limit:");
	mcRepairLimit.Data(lpSettings->mfRepairLimit);

	miDataItems+=2;
	mcBox.DataItems(miDataItems);

}


void cPlanningRepair::Run()
{
    cPlanningComponent::Run();
}

void cPlanningRepair::Stop()
{
 cPlanningComponent::Stop();
 _KILL(mpModel);
}

void cPlanningRepair::DisplayOthers(c3DVf &lfPos)
{
	mcRepairRate.Display();
	mcRepairLimit.Display();

};
void cPlanningRepair::CreateOthers()
{
	mcRepairRate.Create();
	mcRepairLimit.Create();
};
void cPlanningRepair::DestroyOthers()
{
	mcRepairRate.Destroy();
	mcRepairLimit.Destroy();
};


cTexture *cPlanningRepair::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("RepairPVE");
    else return _GET_TEXTURE_FILE("RepairNVE");
};

