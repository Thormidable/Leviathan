#include "stdafx.h"
#include "../../main.h"

cParticleHandler *cLeviathan::mpLeviathanParticleHandler=0;

cLeviathan *gpLeviathan=0;
vRenderNode *cLeviathan::spLast=0;
//Constructor for the enemy fighter.
cLeviathan::cLeviathan(cLeviathanSettings *mpSettings)
{

if(!mpLeviathanParticleHandler)
{
  mpLeviathanParticleHandler=_CREATE(cParticleHandler(_CAMERA));
  mpLeviathanParticleHandler->Shader("NewPointSizingProgram");
  mpLeviathanParticleHandler->Transparency(3);
}

 gpLeviathan=this;

mcReactorDamage=cDamage(REACTOR_DEATH_DAMAGE_RATE,DAMAGE_TYPE_THROUGH);

 vRenderNode *mpCoreBeam=0;
 cLeviathanComponent *mpBaseComponent=0;
 cLeviathanComponent *lpTemp;
spLast=_CAMERA->RenderList();


miComponents=mpSettings->miComponents;
mpComponents=new cLeviathanComponent*[miComponents];

for(uint32 liCount=0;liCount<mpSettings->miComponents;++liCount)
{
    switch(mpSettings->mpComponents[liCount]->Type())
    {
        case LV_REACTOR : {lpTemp=_CREATE(cLeviathanReactor(mpSettings->mpComponents[liCount]->Reactor()));}break;
        case LV_HULL : {lpTemp=_CREATE(cLeviathanHull(mpSettings->mpComponents[liCount]->Hull()));}break;
        case LV_SENSORS : {lpTemp=_CREATE(cLeviathanSensor(mpSettings->mpComponents[liCount]->Sensor()));}break;
        case LV_SHIELD : {lpTemp=_CREATE(cLeviathanShield(mpSettings->mpComponents[liCount]->Shield()));}break;
        case LV_THRUSTERS : {lpTemp=_CREATE(cLeviathanThruster(mpSettings->mpComponents[liCount]->Thruster()));}break;
        case LV_VENT : {lpTemp=_CREATE(cLeviathanVent(mpSettings->mpComponents[liCount]->Vent()));}break;
        case LV_TURRET_BEAM : {lpTemp=_CREATE(cLeviathanBeamTurret(mpSettings->mpComponents[liCount]->BeamTurret()));}break;
        case LV_TURRET_MISSILE : {lpTemp=_CREATE(cLeviathanMissileTurret(mpSettings->mpComponents[liCount]->MissileTurret()));}break;
        case LV_TURRET_PROJECTILE : {lpTemp=_CREATE(cLeviathanProjectileTurret(mpSettings->mpComponents[liCount]->ProjectileTurret()));}break;
        case LV_TURRET_TRACTOR : {lpTemp=_CREATE(cLeviathanTractorBeam(mpSettings->mpComponents[liCount]->TractorTurret()));}break;
        case LV_MULTIHULL : {lpTemp=_CREATE(cLeviathanMultiHull(mpSettings->mpComponents[liCount]->MultiHull()));}break;
		case LV_REPAIR : {lpTemp=_CREATE(cLeviathanRepair(mpSettings->mpComponents[liCount]->Repair()));}break;
        default : {lpTemp=0;}break;
    };

	mpComponents[liCount]=lpTemp;
    if(lpTemp)
    {

      spLast=lpTemp->ComponentNode();
      mpSettings->mpComponents[liCount]->mpNode=spLast;
      for(uint32 liLoop=0;liLoop<12;++liLoop)
      {
          if(gcPlannedSettings.mfTargets[liLoop].ID()==liCount+1) gcGameSettings.mcTargets[liLoop].SetTarget(lpTemp,gcPlannedSettings.mfTargets[liLoop].Position());
      }
    }
    if(!liCount)
    {
        mpCoreBeam=lpTemp->ComponentNode();
        mpBaseComponent=lpTemp;
    }
}


  mpCoreBeam->Equals(gcPlannedSettings.mmOrientation);
 //gcPlannedSettings.mmOrientation.Display();
 mpCoreBeam->Position(0.0f,0.0f,1.0f);
 mpBaseComponent->UserSignal(LEVIATHAN_COMPONENT_FREE,0);

 //Rotate the Ship to face in a random direction.



mpBaseComponent->Momentum()->DampenMomentum(0.0f);

 //Rotate the Ship to face in a random direction.



}


void cLeviathan::Run()
{

	mfSensorDegredation=TRAIN_LEV_SENSORS_WORST+0.1f;
	SensorInput(TRAIN_LEV_SENSORS_WORST);

}

cLeviathanComponent *cLeviathan::LowestHealth()
{
 float lfLowest=mpComponents[0]->Health();
 uint32 liLowest=0;
 for(uint32 liCount=1;liCount<miComponents;++liCount)
 {
	if(mpComponents[liCount] && mpComponents[liCount]->Health()<lfLowest)
	{
 		liLowest=liCount;
		lfLowest=mpComponents[liCount]->Health();
	}
 }
 return mpComponents[liLowest];

};

void cLeviathan::SensorInput(float lfDegredation)
{
 if(lfDegredation<mfSensorDegredation)
 {
	mfSensorDegredation=lfDegredation;
	mpTarget.Equals(cPlayer::HullMatrix);
	mpTarget.Advance(ZEROED_RANDOM_NUMBER*mfSensorDegredation,ZEROED_RANDOM_NUMBER*mfSensorDegredation,ZEROED_RANDOM_NUMBER*mfSensorDegredation);
 }

};


//On Leviathan Death this function will run
void cLeviathan::Stop()
{

}

//This is a function for receiving signals from other processes.
bool cLeviathan::UserSignal(SIGNAL lsSignal,void *lpData)
{
 switch(lsSignal)
 {
	 case LEVIATHAN_COMPONENT_DEATH :
	 {

	     cLeviathanComponent *lpComponent=((cLeviathanComponent*)lpData);
	     vRenderNode *lpNode=lpComponent->ComponentNode();
           bool lbPower=false;
           lpNode->TreeProcessUserSignal(LEVIATHAN_POWER_STATE,&lbPower);
           cProcess *lpProcess;
             for(vRenderObject *lpCur=lpNode->FindStart();lpCur;)
             {
                 if(lpCur->Alive())
                 {
                     lpProcess=lpCur->Process();
                    if(lpProcess)
                    {
                        lpCur=lpNode->FindNext();
                        lpProcess->UserSignal(LEVIATHAN_COMPONENT_FREE,lpNode);
                        continue;
                    }
                 }
                 lpCur=lpNode->FindNext();
             }
             CheckFoundations(lpComponent,lpNode);
            lpNode->MoveAll(_CAMERA->RenderList());
        return 1;
	 }
     case LEVIATHAN_REACTOR_DEATH:
	 {
	     cLeviathanComponent *lpComponent=((cLeviathanComponent*)lpData);
	     vRenderNode *lpNode=lpComponent->ComponentNode();
             bool lbPower=false;
             lpNode->TreeProcessUserSignal(LEVIATHAN_POWER_STATE,&lbPower);
             cProcess *lpProcess;
             for(vRenderObject *lpCur=lpNode->FindStart();lpCur;)
             {
                 if(lpCur->Alive())
                 {
                    lpProcess=lpCur->Process();
                    if(lpProcess)
                    {
                        lpCur=lpNode->FindNext();
                        lpProcess->UserSignal(LEVIATHAN_REACTOR_DEATH,lpNode);
                        continue;
                    }
                 }
                 lpCur=lpNode->FindNext();
             }
                CheckFoundations(lpComponent,lpNode);
                lpNode->MoveAll(_CAMERA->RenderList());
                return 1;
        }

	 default :
	 {
	     return 0;
	 }
 };
 return 0;
}


void cLeviathan::SetProgram(cRenderObject *lpObj)
{
    lpObj->Shader("NormalMappingProgram");
    lpObj->AddTexture("BricksNormalMap");
    lpObj->AddTexture("BricksColorMap");

 	lpObj->SetVariable("Material_diffuse",cRGBA(0.8f,0.8f,0.8f,1.0f).Color());
 	lpObj->SetVariable("Material_ambient",cRGBA(0.2f,0.2f,0.2f,1.0f).Color());

	cModel *lpTemp=dynamic_cast<cModel*>(lpObj);
 	cTBNVectors *lpTBN=new cTBNVectors(lpTemp->Mesh());
 	lpTBN->LinkToShader(lpObj);
};


void cLeviathan::CheckFoundations(cLeviathanComponent* lpComp,vRenderNode *lpNode)
{
    for(uint32 liCount=0;liCount<miComponents;++liCount)
    {
        if(mpComponents[liCount])
        {
           if(mpComponents[liCount]==lpComp)
            mpComponents[liCount]=0;
           else
            mpComponents[liCount]->FoundationDeath(lpNode);
        }
    }
};
