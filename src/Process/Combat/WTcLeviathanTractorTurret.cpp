#include "stdafx.h"
#include "../../main.h"

cLeviathanTractorBeam::cLeviathanTractorBeam(cLeviathanTractorTurretSettings *lpSettings) : cLeviathanBeamTurret(lpSettings)
{
    //mfDamageFactor=lpSettings->mfDamageFactor;

    mpTargeted=_CREATE(cAudioObject);
    mpTargeted->Buffer("TractorBeamVoice");
};

cLeviathanTractorBeam::cLeviathanTractorBeam(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor,float lfDampeningFactor) : cLeviathanBeamTurret(lpSettings,lfRange,lfBeamRadius,lfFireDelay,lfRechargeRate,lfDischargeRate,lfFullRecharge,lcBeamColor)
{
 mfDamageFactor=lfDampeningFactor;
 mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("TractorBeamVoice");
}

void cLeviathanTractorBeam::Run()
{

    TrackPoint(gpLeviathan->Target()->Position());

    mpBeam->Equals(mpHull->GetListItem(1)->mmCache);
 	//If the fighters guns are reloaded - fire.
    if(mfCharge>=mfFullRecharge)
    {
        if(InRange(mpBeam->Length()))
        {
            _WAKE(mpBeam);
            mfChargeChange=-mfDischargeRate;
            mfDelayTimer=mfFireDelay;
            cRGBA lcTemp(1.0f,1.0f,1.0f,0.2f);
            mpBeam->SetVariable("ModelColor",lcTemp.Color());

        }
    }
    else
    {
        if(mfCharge<0.0f)
        {
          _SLEEP(mpBeam);
          mfChargeChange=+mfRechargeRate;
        }

    }


if(mpReactor && mfChargeChange>0.0f)
    {
        if(mpReactor->GenerateEnergy(mfEnergyCost)) mfCharge+=mfChargeChange;
    }
    else{ mfCharge+=mfChargeChange;}


cLeviathanComponent::Run();

if(mpBeam->Awake())
{

    if(mfDelayTimer<=0.0f)
    {
        mpBeam->SetVariable("ModelColor",mcBeamColor.Color());
        //This will check for collisions
        //lpProc will point at each Collisions owning process.
        //lpList will store the list of detected collisions.
        //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
        cProcess *lpProc;
        cCollisionList *lpList=_COLLISION_HANDLER->GenerateCollisionList(mpBeamColl,PLAYER_SHIP_FILTER);

        //This will step through all the collisions making lpProc point at the next process.
        for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
        {
            cPlayer::lpMomentum->DampenLinear(mfDamageFactor);
        }
        //delete the cCollisionList created earlier.
        delete lpList;
    }
    else {mfDelayTimer-=0.04f;};

}

}


void cLeviathanTractorBeam::Display(cCombatStatusBox *lpPoint)
{
        _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Charge:");
};

void cLeviathanTractorBeam::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(1.0f-(mfCharge/mfFullRecharge),(mfCharge/mfFullRecharge),0.0f,1.0f).Color());
    return ;
};
