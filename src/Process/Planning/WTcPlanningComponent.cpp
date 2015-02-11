
#include "../../main.h"

vRenderNode *cPlanningComponent::ComponentNode(){return mpComponentNode;};

cPlanningComponent::cPlanningComponent(cLeviathanComponentSettings *lpSettings)
{

mpReactor=lpSettings->mpReactor;

 mbSelected=false;


 mcBox.Width(DATA_BOX_WIDTH);


 mcType.String("Type: ");
 mcType.Data(TypeString(lpSettings->Type()));

 mcHealth.String("Health: ");
 mcHealth.Data(lpSettings->mfHealth);

 mcEnergyCost.String("Energy: ");
 mcEnergyCost.Data(lpSettings->mfEnergyCost);

 if(lpSettings->mpArmour)
 {
    mcArmourType.String("Armour: ");
    mcArmourType.Data(lpSettings->mpArmour->TypeString());

    mcArmourValue.String("Armour Value: ");
    mcArmourValue.Data(lpSettings->mpArmour->Value());
    mbArmour=true;

    mcBox.DataItems(5);
    miDataItems=5;
 }
 else
 {
     mbArmour=false;
     mcBox.DataItems(3);
     miDataItems=3;
 }
    mpFollowing=0;

 if(lpSettings->mpFoundations->Component(0)) mpComponentNode=_CREATE(cRenderNode(lpSettings->mpFoundations->Component(0)->mpNode));
 else mpComponentNode=_CREATE(cRenderNode(cPlanningLeviathan::spLast));

 mpComponentNode->Process(this);
 mpComponentNode->Equals(lpSettings->mpFoundations->Matrix(0));

 mpIcon=new cImage(gp2DCamera);
 mpIcon->Shader("Image2DUniformColorProgram");
 mpIcon->AddTexture(GetIcon());
 mpIcon->SetVariable("UniformColor",cRGBA(1.0f,1.0f,0.0f,1.0f).Color());
 mpIcon->Width(40.0f);
 mpIcon->Height(40.0f);
 mpIcon->Transparency(2);


}
void cPlanningComponent::SetProgram(cRenderObject *lpObj)
{
    lpObj->Shader("NormalMappingProgram");
    lpObj->AddTexture("BricksNormalMap");
    lpObj->AddTexture("BricksColorMap");

 	lpObj->SetVariable("Material_diffuse",cRGBA(0.8f,0.8f,0.8f,1.0f).Color());
 	lpObj->SetVariable("Material_ambient",cRGBA(0.2f,0.2f,0.2f,1.0f).Color());

	cModel *lpTemp=dynamic_cast<cModel*>(lpObj);
 	cTBNVectors *lpTBN=new cTBNVectors(lpTemp->Mesh());
 	lpTBN->LinkToShader(lpObj);
}

void cPlanningComponent::Run()
{
        DisplayBox();

    if(cPlanningLeviathan::sbSelectionOn && mpIcon->Awake())
    {
        c3DVf lfBox(_MOUSE->X(),gpWindow->RenderAreaHeight()-_MOUSE->Y(),0.0f);
        lfBox-=mpIcon->Position();
        if(cPlanningLeviathan::mfSelectionDistance> lfBox.MagnitudeSq())
        {
            cPlanningLeviathan::mpSelection=this;
            cPlanningLeviathan::mfSelectionDistance=lfBox.MagnitudeSq();
        }
    }
}

void cPlanningComponent::Selected(bool lbState)
{
    mbSelected=lbState;
    if(mbSelected)
    {
        //mpIcon->Priority(2);
        mpIcon->Transparency(4);
        if(mpIcon->X()>DATA_BOX_WIDTH+mpIcon->Width()*0.5)
        {
          _WAKE(mpIcon);
        }
        else _SLEEP(mpIcon);
        CreateBox();
        cRGBA Temp=cPlanningLeviathan::GetNextColor();
        Temp.A(1.0f);
        mpIcon->SetVariable("UniformColor",Temp.Color());
        mcBox.Color(Temp);
    }
    else
    {
        cRGBA Temp=cRGBA(1.0f,1.0f,1.0f,0.5f);
        mpIcon->SetVariable("UniformColor",Temp.Color());
        //mcBox.Color(Temp);
        DestroyBox();
       //mpIcon->Priority(4);
		mpIcon->Transparency(3);
       if(cPlanningLeviathan::mcKeyToggles[1].Off() || (cPlanningLeviathan::mcKeyToggles[0].Off() && Hull()) || !(mpIcon->X()>DATA_BOX_WIDTH+mpIcon->Width()*0.5))
       {
           _SLEEP(mpIcon);
       }
       else
       {
            _WAKE(mpIcon);
       }
    }
    OtherSelected(lbState);
    mpIcon->ClearTextureStack();
    mpIcon->AddTexture(GetIcon());

};
void cPlanningComponent::Stop()
{
	_KILL(mpIcon);
	mpIcon=0;
	_KILL(mpComponentNode);
    DestroyBox();
}

void cPlanningComponent::DisplayBox()
{
    if(mpFollowing)
    {
        c3DVf lfPos=mpFollowing->GetScreenPosition();
        mpIcon->Position(lfPos[0],lfPos[1]);
        mpIcon->Size(PLANNING_ICON_SIZE);
        if(mbSelected && mcBox.Created())
        {
            mcBox.Display();
            mcType.Display();
            mcHealth.Display();
            mcEnergyCost.Display();
            if(mbArmour)
            {
                mcArmourType.Display();
                mcArmourValue.Display();
            }
            DisplayOthers(lfPos);
        }
    }
}

void cPlanningComponent::CreateBox()
{
    if(!mcBox.Created())
    {
        mcBox.Create();
        mcType.Create();
        mcHealth.Create();
        mcEnergyCost.Create();
        if(mbArmour)
            {
                mcArmourType.Create();
                mcArmourValue.Create();
            }
        CreateOthers();
    }
};

void cPlanningComponent::DestroyBox()
{
    if(mcBox.Created())
    {
        mcBox.Destroy();
        mcType.Destroy();
        mcHealth.Destroy();
        mcEnergyCost.Destroy();
        if(mbArmour)
            {
                mcArmourType.Destroy();
                mcArmourValue.Destroy();
            }
        DestroyOthers();
    }
};

string cPlanningComponent::TypeString(uint8 liType)
{
    switch(liType)
    {
        case LV_MULTIHULL : return "MultiHull";
        case LV_VENT : return "Vent";
        case LV_REACTOR : return "Reactor";
        case LV_THRUSTERS : return "Thruster";
        case LV_SENSORS : return "Sensor";
        case LV_TURRET_PROJECTILE : return "Ballistic";
        case LV_TURRET_BEAM : return "Beam";
        case LV_TURRET_MISSILE : return "Missile";
        case LV_TURRET_TRACTOR : return "Tractor";
        case LV_SHIELD : return "Shield";
        case LV_HULL : return "Hull";
		case LV_REPAIR : return "Repair";
        default : return "Void Component";
    };
};

void cPlanningComponent::OtherSelected(bool lbState)
{
(void) lbState;
};

cTexture *cPlanningComponent::GetIcon()
{
    return 0;
};

bool cPlanningComponent::Hull()
{
    return 0;
}
