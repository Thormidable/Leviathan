
#include "../../main.h"

cLeviathanRepair::cLeviathanRepair(cLeviathanRepairSettings *lpSettings) : cLeviathanComponent(lpSettings)
{

		 mpRepair=new cModel(mpComponentNode);
 		 mpRepair->Mesh(lpSettings->mpMesh);
 		 gpLeviathan->SetProgram(mpRepair);


		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpRepair,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpCollision);

		mfCurrentRepairRate=mfRepairRate=lpSettings->mfRepairRate;
		mfRepairLimit=lpSettings->mfRepairLimit;
		mfInvLimit=1.0f/mfRepairLimit;

         mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("HullVoice");


};


void cLeviathanRepair::Run()
{
	cLeviathanComponent::Run();
	cLeviathanComponent *lpLow=gpLeviathan->LowestHealth();
	if(lpLow->Health()<1.0f) Repair(lpLow);

};

void cLeviathanRepair::Stop()
{
    _KILL(mpRepair);
    cLeviathanComponent::Stop();

};

void cLeviathanRepair::Repair(cLeviathanComponent *lpComp)
{
	if(mfRepairLimit>0.0f)
	{
		cDamage::mfFinalDamage=-mfCurrentRepairRate;
		lpComp->ReduceHealth();
		mfRepairLimit-=mfRepairRate;
	}
};


//This is a function for receiving signals from other processes.
bool cLeviathanRepair::UserSignal(SIGNAL lsSignal,void *lpData)
{
    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    //determine the type of signal.
    switch(lsSignal)
    {
        case LEVIATHAN_POWER_STATE :
        {

        }
        default:
        {
            return 0;
        }
    }

    return 0;
};

void cLeviathanRepair::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    if(mfHealth<0.0f)
	{
		mfCurrentRepairRate=mfRepairRate*mfHealth*mfMaxHealthInv;

        SignalDeath();
		_KILL_THIS();
	}


}

void cLeviathanRepair::Display(cCombatStatusBox *lpPoint)
{
    _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Repair:");
};

void cLeviathanRepair::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(1.0f-mfInvLimit*mfRepairLimit,mfInvLimit*mfRepairLimit,0.0f,1.0f).Color());

    return ;
};
