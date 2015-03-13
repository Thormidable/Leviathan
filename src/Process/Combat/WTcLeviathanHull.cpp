
#include "../../main.h"

cLeviathanHull::cLeviathanHull(cLeviathanHullSettings *lpSettings) : cLeviathanComponent(lpSettings)
{
        mpHull=new cModel(mpComponentNode);
 		mpHull->Mesh(lpSettings->mpMesh);
        gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpCollision);

		 mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("HullVoice");
};

cLeviathanHull::cLeviathanHull(cLeviathanComponentSettings *lpSettings, string lsMesh,string lsCollision) : cLeviathanComponent(lpSettings)
{

		 mpHull=new cModel(mpComponentNode);
 		 mpHull->Mesh(lsMesh.c_str());
        gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lsCollision.c_str());

		 mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("HullVoice");

};

void cLeviathanHull::Run()
{
	cLeviathanComponent::Run();

};

	void cLeviathanHull::Stop()
	{
		_KILL(mpHull);
	    cLeviathanComponent::Stop();

	};

void cLeviathanHull::ReduceHealth()
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


//This is a function for receiving signals from other processes.
bool cLeviathanHull::UserSignal(SIGNAL lsSignal,void *lpData)
{
    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    //determine the type of signal.
    switch(lsSignal)
    {
        //If it is damage, update the health of the fighter.
        case LEVIATHAN_POWER_STATE :
        {
            return 1;
        }
        default:
        {
            return 0;
        }
    }

    return 0;
};

