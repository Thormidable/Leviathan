#include "stdafx.h"
#include "../../main.h"

cPlanningHull::cPlanningHull(cLeviathanHullSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpModel=_CREATE(cModel(mpComponentNode));
    mpModel->Mesh(lpSettings->mpMesh);
    SetProgram(mpModel);

    mpFollowing=mpModel;

    mpColl=_CREATE(cCollisionObject(mpModel,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpCollision);
}


void cPlanningHull::Run()
{
    cPlanningComponent::Run();
}

void cPlanningHull::Stop()
{
 cPlanningComponent::Stop();
 _KILL(mpModel);
}

void cPlanningHull::DisplayOthers(c3DVf &lfPos)
{

};
void cPlanningHull::CreateOthers()
{

};
void cPlanningHull::DestroyOthers()
{

};


cTexture *cPlanningHull::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("HullPVE");
    else return _GET_TEXTURE_FILE("HullNVE");
};

bool cPlanningHull::Hull()
{
    return 1;
};
