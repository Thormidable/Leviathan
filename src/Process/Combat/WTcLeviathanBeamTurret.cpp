
#include "../../main.h"

cLeviathanBeamTurret::cLeviathanBeamTurret(cLeviathanBeamTurretSettings *lpSettings) : cLeviathanTurret(lpSettings)
{
    mpBeam=_CREATE(cBeam(lpSettings->mpBeam));
    mpBeam->Equals(mpHull->GetListItem(1));
	mpBeam->Shader("SetUniformColorProgram");
	mpBeam->SetVariable("ModelColor",lpSettings->mcBeamColor.Color());
	mpBeam->Transparency(1);

    mpBeamColl=_CREATE(cCollisionObject(mpBeam,this));
    mpBeamColl->SetType(mpBeam);
    mpBeamColl->CollisionFilter(ENEMY_BULLET_FILTER);

    mfCharge=mfFullRecharge=lpSettings->mfFullRecharge;
    mfChargeChange=mfRechargeRate=lpSettings->mfRechargeRate;
    mfDischargeRate=lpSettings->mfDischargeRate;
    mfFireDelay=lpSettings->mfFireDelay;
    mfDelayTimer=0.0f;
    mcBeamColor=lpSettings->mcBeamColor;

    mfDamageFactor=lpSettings->mfDamageFactor;

    mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("BeamTurretVoice");
};

cLeviathanBeamTurret::cLeviathanBeamTurret(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor) : cLeviathanTurret(lpSettings)
{
    mpBeam=_CREATE(cBeam(lfBeamRadius,lfRange,12));
    mpBeam->Equals(mpHull->GetListItem(1));
	mpBeam->Shader("SetUniformColorProgram");
	mpBeam->SetVariable("ModelColor",lcBeamColor.Color());
	mpBeam->Transparency(1);

    mpBeamColl=_CREATE(cCollisionObject(mpBeam,this));
    mpBeamColl->SetType(mpBeam);
    mpBeamColl->CollisionFilter(ENEMY_BULLET_FILTER);

    mfCharge=mfFullRecharge=lfFullRecharge;
    mfChargeChange=mfRechargeRate=lfRechargeRate;
    mfDischargeRate=lfDischargeRate;
    mfFireDelay=lfFireDelay;
    mfDelayTimer=0.0f;
    mcBeamColor=lcBeamColor;

    mfDamageFactor=LEVIATHAN_BEAM_DAMAGE_FACTOR;

    mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("BeamTurretVoice");
};

void cLeviathanBeamTurret::Run()
{
    TrackPoint(gpLeviathan->Target()->Position());

    UpdateHitSelf();

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
          mfChargeChange=mfRechargeRate;
        }
    }


    if(mpReactor && mfChargeChange>0.0f)
    {
        if(mpReactor->GenerateEnergy(mfEnergyCost)) mfCharge+=mfChargeChange;
    }
    else{ mfCharge+=mfChargeChange;}

if(mpBeam->Awake())
{

    if(WillHitSelf())
    {
        _SLEEP(mpBeam);
        mfChargeChange=mfRechargeRate;
    }
    else
    {
        cLeviathanComponent::Run();

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
                    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
                    float lfDamage[4]={mfCharge*mfDamageFactor,-mpBeam->Zx(),-mpBeam->Zy(),-mpBeam->Zz()};
                    lpProc->UserSignal(BEAM_COLLISION,lfDamage);
                }
                //delete the cCollisionList created earlier.
                delete lpList;

        }
        else{ mfDelayTimer-=0.04f; }
    }
}
};

void cLeviathanBeamTurret::Stop()
{
    _KILL(mpBeam);
    cLeviathanTurret::Stop();
};


//This is a function for receiving signals from other processes.
bool cLeviathanBeamTurret::UserSignal(SIGNAL lsSignal,void *lpData)
{
    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    //determine the type of signal.
    switch(lsSignal)
    {
        case LEVIATHAN_POWER_STATE :
        {
          bool *lbState=(bool*)lpData;
            if(!*lbState)
            {
                mfRechargeRate=0.0f;
                mfFullRecharge=mfCharge;
            }
            return 1;
        }
        default:
        {
            return 0;
        }
    }

    return 0;
};


void cLeviathanBeamTurret::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    if(mfHealth<0.0f)
    {
        SignalDeath();
        _KILL_THIS();
    }


}

void cLeviathanBeamTurret::Display(cCombatStatusBox *lpPoint)
{
    _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Charge:");
};

void cLeviathanBeamTurret::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(1.0f-(mfCharge/mfFullRecharge),(mfCharge/mfFullRecharge),0.0f,1.0f).Color());
    return ;
};

