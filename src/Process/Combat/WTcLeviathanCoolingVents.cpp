#include "stdafx.h"
#include "../../main.h"

vArmour cLeviathanVent::mcOpenArmour;

cLeviathanVent::cLeviathanVent(cLeviathanVentSettings *lpSettings) : cLeviathanComponent(lpSettings)
{

		 mpVent=new cModel(mpComponentNode);
 		 mpVent->Mesh(lpSettings->mpVent);
 		 gpLeviathan->SetProgram(mpVent);


		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpVent,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpVentColl);

		 mfOpenAngle=lpSettings->mfOpenAngle;
		 mfOpeningRate=lpSettings->mfOpeningRate;
         miState=0;
         mfBaseCool=lpSettings->mfBaseCool;
         mfMaxCool=lpSettings->mfMaxCool;

         mpClosedArmour=mpArmour;

         mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("HeatSinksVoice");
};

cLeviathanVent::cLeviathanVent(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool) : cLeviathanComponent(lpSettings)
{

		 mpVent=new cModel(mpComponentNode);
 		 mpVent->Mesh(lsMesh.c_str());
 		 gpLeviathan->SetProgram(mpVent);


		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpVent,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lsCollision.c_str());

		 mfOpenAngle=lfOpenAngle;
		 mfOpeningRate=lfOpenRate;
         miState=0;
         mfBaseCool=lfBaseCool;
         mfMaxCool=lfMaxCool;

         mpClosedArmour=mpArmour;

         mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("HeatSinksVoice");

};

void cLeviathanVent::Open()
{
    if(miState!=2)
    {
        mpVent->RotateX(mfOpenAngle);
        miState=2;
        mpArmour=&mcOpenArmour;
    }

};

void cLeviathanVent::Close()
{
     if(miState)
    {
        mpVent->RotateX(-mfOpenAngle);
        miState=0;
        mpArmour=mpClosedArmour;
    }
};

float cLeviathanVent::Cooling()
{
    if(miState==2) return mfMaxCool;
    return mfBaseCool;
}

void cLeviathanVent::Run()
{
	cLeviathanComponent::Run();
	if(mpReactor)
	{
	    float lfReactTemp=mpReactor->ReactorTemp();
	    lfReactTemp*=lfReactTemp*lfReactTemp;
	    if(RANDOM_NUMBER<lfReactTemp) Open();
	    else if(lfReactTemp>RANDOM_NUMBER) Close();
	    mpReactor->Cool(Cooling());
	}
};

void cLeviathanVent::Stop()
{
    _KILL(mpVent);
	mpArmour=mpClosedArmour;
    cLeviathanComponent::Stop();

};


//This is a function for receiving signals from other processes.
bool cLeviathanVent::UserSignal(SIGNAL lsSignal,void *lpData)
{
    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    //determine the type of signal.
    switch(lsSignal)
    {
        case LEVIATHAN_POWER_STATE :
        {
            if(miState==2) mfBaseCool=mfMaxCool;
            else mfMaxCool=mfBaseCool;
            mfOpenAngle=0.0f;
        }
        default:
        {
            return 0;
        }
    }

    return 0;
};

void cLeviathanVent::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    if(mfHealth<0.0f)
	{
	    if(miState==2) mfBaseCool=mfMaxCool;
        else mfMaxCool=mfBaseCool;
        mfOpenAngle=0.0f;

        SignalDeath();
		_KILL_THIS();
	}


}

void cLeviathanVent::Display(cCombatStatusBox *lpPoint)
{
    _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Cooling:");
};

void cLeviathanVent::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    if(miState==2) lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(0.0f,1.0f,0.0f,1.0f).Color());
    else lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(1.0f,0.0f,0.0f,1.0f).Color());

    return ;
};
