
#include "../../main.h"

cLeviathanSensor::cLeviathanSensor(cLeviathanSensorSettings *lpSettings) : cLeviathanComponent(lpSettings)
{

		 mpHull=new cModel(mpComponentNode);
 		 mpHull->Mesh(lpSettings->mpHull);
        gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpColl);

		 mfMaxHealthInv=1.0f/mfHealth;
		 mfMaxSensorDegredation=lpSettings->mfMaxSensorDegredation;
		 mfSensorDegredation=mfSensorBaseDegredation=lpSettings->mfSensorBaseDegredation;

        mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("SensorsVoice");
};

cLeviathanSensor::cLeviathanSensor(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorDegredation) : cLeviathanComponent(lpSettings)
{

		 mpHull=new cModel(mpComponentNode);
 		 mpHull->Mesh(lsMesh.c_str());
        gpLeviathan->SetProgram(mpHull);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpHull,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lsCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;
		 mfMaxSensorDegredation=lfSensorDegredation;
		 mfSensorDegredation=mfSensorBaseDegredation=lfBaseDegredation;

        mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("SensorsVoice");

};

void cLeviathanSensor::Run()
{
	cLeviathanComponent::Run();

    if(mpReactor)
    {
        if(mpReactor->GenerateEnergy(mfEnergyCost)) gpLeviathan->SensorInput(mfSensorDegredation);
        else gpLeviathan->SensorInput(mfMaxSensorDegredation);
    }

};

void cLeviathanSensor::Stop()
{
		if(mpHull) _KILL(mpHull);
		cLeviathanComponent::Stop();
};

//This is a function for receiving signals from other processes.
bool cLeviathanSensor::UserSignal(SIGNAL lsSignal,void *lpData)
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
                mfSensorDegredation=mfMaxSensorDegredation+mfSensorBaseDegredation;
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


void cLeviathanSensor::ReduceHealth()
{

            mfHealth-=cDamage::mfFinalDamage;
            //If the damage is more than the fighter can take kill it.
            //This will call Stop()
			mfSensorDegredation=(1.0f-mfHealth*mfMaxHealthInv)*mfMaxSensorDegredation+mfSensorBaseDegredation;

            if(mfHealth<0.0f)
			{
			    SignalDeath();
				_KILL_THIS();
			}

}


