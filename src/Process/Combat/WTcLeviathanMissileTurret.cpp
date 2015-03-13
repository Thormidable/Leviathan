
#include "../../main.h"

cLeviathanMissileTurret::cLeviathanMissileTurret(cLeviathanMissileTurretSettings *lpSettings) : cLeviathanTurret(lpSettings)
{

 mpMissileSettings=lpSettings->mpMissileSettings;
 mpMissileSettings->mpTarget=gpPlayer->mcPlayerTarget;

 mfReloadRate=lpSettings->mfReloadRate;
 mfReloadState=1.0f;
 mfRange=lpSettings->mfRange;

 mpTargeted=_CREATE(cAudioObject);
 mpTargeted->Buffer("MissileTurretVoice");

 mpLaunch=_CREATE(cAudioObject);
 mpLaunch->Buffer("MissileIncomingVoice");
};

cLeviathanMissileTurret::cLeviathanMissileTurret(cLeviathanTurretSettings *lpSettings,float lfRange,cMissileSettings *lpMissileSettings) : cLeviathanTurret(lpSettings)
{

 mpMissileSettings=lpMissileSettings;
 mpMissileSettings->mpTarget=gpPlayer->mcPlayerTarget;

 mfReloadRate=lpSettings->mfReloadRate;
 mfReloadState=1.0f;
 mfRange=lfRange;

 mpTargeted=_CREATE(cAudioObject);
 mpTargeted->Buffer("MissileTurretVoice");

 mpLaunch=_CREATE(cAudioObject);
 mpLaunch->Buffer("MissileIncomingVoice");
};


void cLeviathanMissileTurret::Run()
{

  TrackPoint(gpLeviathan->Target()->Position());

    UpdateHitSelf();

    //If the fighters guns are reloaded - fire.
    if(mfReloadState<=0.0f)
    {
            if(!WillHitSelf())
            {
                //Create a bullet and set the guns to reload.
                mpMissileSettings->mpMatrix=&(mpHull->GetListItem(1)->mmCache);
                mpMissileSettings->mpMomentumBase=mpTreeBase->Momentum();
                if(gbSoundOn) mpLaunch->Play();
                if(dynamic_cast<cExplosiveMissileSettings*>(mpMissileSettings)) _CREATE(cExplosiveMissile((cExplosiveMissileSettings*)mpMissileSettings));
                if(dynamic_cast<cLaserMissileSettings*>(mpMissileSettings)) _CREATE(cLaserMissile((cLaserMissileSettings*)mpMissileSettings));
                if(dynamic_cast<cEMPMissileSettings*>(mpMissileSettings)) _CREATE(cEMPMissile((cEMPMissileSettings*)mpMissileSettings));
                mfReloadState=1.0f;
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


//This is a function for receiving signals from other processes.
bool cLeviathanMissileTurret::UserSignal(SIGNAL lsSignal,void *lpData)
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


void cLeviathanMissileTurret::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage*_TIME_PER_FRAME;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    if(mfHealth<0.0f)
    {
        SignalDeath();
        _KILL_THIS();
    }


}

void cLeviathanMissileTurret::Display(cCombatStatusBox *lpPoint)
{
        _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Loading:");
};

void cLeviathanMissileTurret::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(mfReloadState,1.0f-mfReloadState,0.0f,1.0f).Color());
    return ;
};
