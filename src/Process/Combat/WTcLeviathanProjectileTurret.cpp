
#include "../../main.h"

cLeviathanProjectileTurret::cLeviathanProjectileTurret(cLeviathanProjectileTurretSettings *lpSettings) : cLeviathanTurret(lpSettings)
{

   mpTracker=_CREATE(cPredictiveTracking(gpLeviathan->Target(),mpHull->GetListItem(1)));

 mfProjSpeed=lpSettings->mfProjSpeed;
 mcBulletDamage=lpSettings->mcBulletDamage;
 mcBulletDamage.miType=DAMAGE_TYPE_INSTANTANEOUS;

    mfReloadState=1.0f;
    mpTargeted=_CREATE(cAudioObject);
    mpTargeted->Buffer("GunTurretVoice");

};

void cLeviathanProjectileTurret::Run()
{
 mpTracker->Update(mfProjSpeed);
 //If the predictive targeting deems a hit possible open fire
 if(mpTracker->CanHit())
 {

    bool lbTracking=TrackVector(mpTracker->InterceptionVector().v);

    UpdateHitSelf();
 	 //If the fighters guns are reloaded - fire.
    if(mfReloadState<0.0f)
    {
        if(lbTracking)
        {
            if(!WillHitSelf())
            {
                //Create a bullet and set the guns to reload.
                _CREATE(cBullet(&(mpHull->GetListItem(1)->mmCache),c3DVf(0.0f,0.0f,0.0f),mfProjSpeed,&mcBulletDamage,ENEMY_BULLET_FILTER,PLAYER_SHIP_FILTER));
                mfReloadState=1.0f;
            }
        }
    }
    else
    {
      //If the guns are not firing this time step, continue to reload.

      if(mpReactor)
      {
        if(mpReactor->GenerateEnergy(mfEnergyCost)) mfReloadState-=mfReloadRate*_TIME_PER_FRAME;
      }
      else{ mfReloadState-=mfReloadRate*_TIME_PER_FRAME;}

    }
 }
 else
 {
     TrackPoint(gpLeviathan->Target()->Position());
 }

cLeviathanComponent::Run();

};

void cLeviathanProjectileTurret::Stop()
{

		delete mpTracker;
        cLeviathanTurret::Stop();
};


//This is a function for receiving signals from other processes.
bool cLeviathanProjectileTurret::UserSignal(SIGNAL lsSignal,void *lpData)
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
            mfReloadRate=0.0f;
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


void cLeviathanProjectileTurret::ReduceHealth()
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


void cLeviathanProjectileTurret::Display(cCombatStatusBox *lpPoint)
{
        _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Loading:");
};

void cLeviathanProjectileTurret::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(mfReloadState,1.0f-mfReloadState,0.0f,1.0f).Color());
    return ;
};
