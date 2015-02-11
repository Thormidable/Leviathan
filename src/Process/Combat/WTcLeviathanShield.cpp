
#include "../../main.h"

cLeviathanShield::cLeviathanShield(cLeviathanShieldSettings *lpSettings) : cLeviathanComponent(lpSettings)
{
    	 mpHull=new cModel(mpComponentNode);
 		 mpHull->Mesh(lpSettings->mpHull);
 		 gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpColl);

		 mfMaxHealthInv=1.0f/mfHealth;

		 mpShield=_CREATE(cShield(mpHull,lpSettings));

        mpTargeted=_CREATE(cAudioObject);
        mpTargeted->Buffer("ShieldGeneratorVoice");
};

cLeviathanShield::cLeviathanShield(cLeviathanComponentSettings *lpSettings,
	string lsMesh,
	string lsCollision,
	string lsShieldMesh,
	string lsShieldCollision,
	float lfShieldMax,
	float lfShieldRecharge,
	float lfShieldDelay,
	cRGBA lcShieldColor) : cLeviathanComponent(lpSettings)
{

		 mpHull=new cModel(mpComponentNode);
 		 mpHull->Mesh(lsMesh.c_str());
 		 gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lsCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;

		 mpShield=_CREATE(cShield(mpHull,lsShieldMesh,lsShieldCollision,ENEMY_SHIELD_FILTER,lcShieldColor,lfShieldRecharge,lfShieldMax,lfShieldDelay,lpSettings->mpFoundations->Matrix(0)));

        mpTargeted=_CREATE(cAudioObject);
        mpTargeted->Buffer("ShieldGeneratorVoice");
};

void cLeviathanShield::Run()
{
	cLeviathanComponent::Run();

    if(mpReactor && !mpReactor->GenerateEnergy(mfEnergyCost)) mpShield->NoPower();

};

	void cLeviathanShield::Stop()
	{
		_KILL(mpHull);
		_KILL(mpShield);
		cLeviathanComponent::Stop();
	};


//This is a function for receiving signals from other processes.
bool cLeviathanShield::UserSignal(SIGNAL lsSignal,void *lpData)
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
                mpShield->Max(-1.0f);
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

void cLeviathanShield::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    mpShield->Max(mfHealth*mfMaxHealthInv);

    if(mfHealth<0.0f)
    {
        SignalDeath();
        _KILL_THIS();

    }

}

void cLeviathanShield::Display(cCombatStatusBox *lpPoint)
{
        _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFieldDisplay[1]);
    _WAKE(lpPoint->mpFields[0]);
    _WAKE(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health:");
 lpPoint->mpFields[1]->Text("Shield:");
};

void cLeviathanShield::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    lpPoint->mpFieldDisplay[1]->SetUniform("UniformColor",mpShield->ShieldStatusColor().Color());
    return ;
};
