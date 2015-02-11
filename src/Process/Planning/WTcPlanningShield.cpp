
#include "../../main.h"

cPlanningShield::cPlanningShield(cLeviathanShieldSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpShieldGen=_CREATE(cModel(mpComponentNode));
    mpShieldGen->Mesh(lpSettings->mpHull);
    SetProgram(mpShieldGen);

    mpFollowing=mpShieldGen;

    mpColl=_CREATE(cCollisionObject(mpShieldGen,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpColl);

    mcStrength.String("Shield: ");
    mcStrength.Data(lpSettings->mfShieldMax);
    mcRecharge.String("Rechrg: ");
    mcRecharge.Data(lpSettings->mfShieldRecharge);
    mcDelay.String("Delay: ");
    mcDelay.Data(lpSettings->mfShieldDelay);

    miDataItems+=3;
    mcBox.DataItems(miDataItems);


    mpShieldMesh=_CREATE(cModel(mpComponentNode));
    mpShieldMesh->Shader("SetUniformColorProgram");
    mpShieldMesh->SetVariablePointer("ModelColor",mcShieldColor.Color());
    mpShieldMesh->Mesh(lpSettings->mpShield);
    mpShieldMesh->Transparency(4);

    cMatrix4 InvMatrix;
    InvMatrix.Equals(lpSettings->mpFoundations->Matrix(0)->InversionMatrix());
    float lfX,lfY,lfZ;
    lfX=InvMatrix[0]*InvMatrix[12]+InvMatrix[4]*InvMatrix[13]+InvMatrix[8]*InvMatrix[14];
    lfY=InvMatrix[1]*InvMatrix[12]+InvMatrix[5]*InvMatrix[13]+InvMatrix[9]*InvMatrix[14];
    lfZ=InvMatrix[2]*InvMatrix[12]+InvMatrix[6]*InvMatrix[13]+InvMatrix[10]*InvMatrix[14];
    InvMatrix.PositionX(lfX);
    InvMatrix.PositionY(lfY);
    InvMatrix.PositionZ(lfZ);
    mpShieldMesh->Equals(InvMatrix);
}

void cPlanningShield::Run()
{
    cPlanningComponent::Run();

}

void cPlanningShield::Stop()
{
	cPlanningComponent::Stop();
  _KILL(mpShieldGen);
  mpShieldGen=0;
}

void cPlanningShield::DisplayOthers(c3DVf &lfPos)
{

    mcStrength.Display();
    mcRecharge.Display();
    mcDelay.Display();
};

void cPlanningShield::CreateOthers()
{
    mcStrength.Create();
    mcRecharge.Create();
    mcDelay.Create();
};
void cPlanningShield::DestroyOthers()
{
  mcStrength.Destroy();
    mcRecharge.Destroy();
    mcDelay.Destroy();
};

void cPlanningShield::OtherSelected(bool lbState)
{
    if(cPlanningLeviathan::mcKeyToggles[2].On())
    {
        if(lbState) mcShieldColor=PLANNING_SHIELD_SELECTED_COLOR;
        else mcShieldColor=PLANNING_SHIELD_COLOR;
        _WAKE(mpShieldMesh);
    }
    else
    {
        mcShieldColor=PLANNING_SHIELD_COLOR;
        if(lbState) _WAKE(mpShieldMesh);
        else _SLEEP(mpShieldMesh);
    }


};

cTexture *cPlanningShield::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("ShieldPVE");
    else return _GET_TEXTURE_FILE("ShieldNVE");
};
