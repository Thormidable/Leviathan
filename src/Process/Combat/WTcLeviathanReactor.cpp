
#include "../../main.h"

cLeviathanReactor::cLeviathanReactor(cLeviathanReactorSettings *lpSettings) : cLeviathanComponent(lpSettings)
{
         mpReactor=new cModel(mpComponentNode);
 		 mpReactor->Mesh(lpSettings->mpReactor);
 		 gpLeviathan->SetProgram(mpReactor);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpReactor,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpColl);

        mcOverloadDamage.miType=DAMAGE_TYPE_THROUGH;

        mfHeatFactor=1.0f;
        mfBaseHeat=lpSettings->mfBaseHeat;
        mfDamageHeatFactor=lpSettings->mfDamageHeatFactor;
        mfTemp=0.0f;
        mfInvOverload=1.0/lpSettings->mfOverload;
        mfMaxPowerGeneration=lpSettings->mfMaxPower;
        mfGenerated=0.0f;
        mfMaxHealthInv=lpSettings->mfInvMaxHealth;

         mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("ReactorVoice");

		 lpSettings->mpReactorComp=this;

};

uint8 cLeviathanReactorSettings::Type(){return LV_REACTOR;};
cLeviathanReactorSettings *cLeviathanReactorSettings::Reactor(){return this;};

void cLeviathanReactor::Run()
{
	cLeviathanComponent::Run();

    mfGenerated=0.0f;
    mfTemp+=mfBaseHeat*mfHeatFactor;
    if(mfTemp<0.0f)
    {
        mfTemp=0.0f;
    }
    else
    {
        cDamage::mfFinalDamage=((mfInvOverload*mfTemp-1.0)*REACTOR_OVERLOAD_FACTOR);
        if(cDamage::mfFinalDamage>0.0) ReduceHealth();
    }



};

void cLeviathanReactor::Stop()
{
    _KILL(mpReactor);
    cLeviathanComponent::Stop();
};


void cLeviathanReactor::ForceGenerateEnergy(float lfEnergy)
{
    mfTemp+=lfEnergy*mfHeatFactor;
    mfGenerated+=lfEnergy;
}

bool cLeviathanReactor::GenerateEnergy(float lfEnergy)
{

    if(mfGenerated+lfEnergy<mfMaxPowerGeneration)
    {
            mfTemp+=lfEnergy*mfHeatFactor;
            mfGenerated+=lfEnergy;
            return 1;
    }
    return 0;
}

void cLeviathanReactor::Cool(float lfCooling)
{
    mfTemp-=lfCooling;
}

float cLeviathanReactor::ReactorTemp()
{
    return mfTemp*mfInvOverload;
}


//This is a function for receiving signals from other processes.
bool cLeviathanReactor::UserSignal(SIGNAL lsSignal,void *lpData)
{
    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    //determine the type of signal.
    switch(lsSignal)
    {
        case LEVIATHAN_POWER_STATE :
        {
            if(mfHealth>0.0f)
            {
               bool *lbState=(bool*)lpData;
               *lbState=true;
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

void cLeviathanReactor::ReduceHealth()
{
            mfHealth-=cDamage::mfFinalDamage;
            mfHeatFactor=1.0f+mfDamageHeatFactor*(1.0f-mfHealth*mfMaxHealthInv);

            //If the damage is more than the fighter can take kill it.
            //This will call Stop()
            if(mfHealth<0.0f)
			{
                gpLeviathan->UserSignal(LEVIATHAN_REACTOR_DEATH,this);
               if(gpPlayer) gpPlayer->UserSignal(DEAD_FIGHTER,this);
			    _KILL_THIS();
			}

}


void cLeviathanReactor::Display(cCombatStatusBox *lpPoint)
{
    _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Temperature:");
};

void cLeviathanReactor::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(ReactorTemp(),1.0f-ReactorTemp(),0.0f,1.0f).Color());
    return ;
};
