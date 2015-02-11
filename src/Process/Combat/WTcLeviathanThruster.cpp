
#include "../../main.h"



cLeviathanThruster::cLeviathanThruster(cLeviathanThrusterSettings *lpSettings) : cLeviathanComponent(lpSettings)
{

		 mpThruster=new cModel(mpComponentNode);
		 mpThruster->Mesh(lpSettings->mpThruster);
		 gpLeviathan->SetProgram(mpThruster);

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpThruster,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lpSettings->mpThrusterColl);

		 mfStartMaxThrust=mfMaxThrust=lpSettings->mfStartMaxThrust;
		 mfThrustLimit=lpSettings->mfThrustLimit;

        mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("ThrusterVoice");
};
cLeviathanThruster::cLeviathanThruster(cLeviathanComponentSettings *lpSettings, string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit) : cLeviathanComponent(lpSettings)
{

		 mpThruster=new cModel(mpComponentNode);
		 mpThruster->Mesh(lsMesh.c_str());
		 gpLeviathan->SetProgram(mpThruster);
		 //mpThruster->Shader("TexturingProgram");
		 //mpThruster->AddTexture("TLevThrusterTexture");

		 cCollisionObject *lpColl;
		 lpColl=_CREATE(cCollisionObject(mpThruster,this));
		 lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
		 lpColl->SetTypeMesh(lsCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;
		 mfStartMaxThrust=mfMaxThrust=lfMaxThrust;
		 mfThrustLimit=lfThrustLimit;

        mpTargeted=_CREATE(cAudioObject);
		 mpTargeted->Buffer("ThrusterVoice");

};

void cLeviathanThruster::Thrust(float lfDesired)
{

 if(mpTreeBase && mpTreeBase->Momentum())
 {
	 lfDesired=ClampValue(-lfDesired,mfMaxThrust);
	 mpTreeBase->Momentum()->LimitedVectorThrust(lfDesired,lfDesired*ANGLE_THRUST_FACTOR,mfThrustLimit,mpThruster->mmCache);
	 mpTreeBase->Momentum()->DampenMomentum(0.9999);
 }

    for(uint8 liCount=0;liCount<2;++liCount)
    {

        cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
        lpPart->SetLife(0.3f+0.3f*RANDOM_NUMBER);
        lpPart->SetSize(5000.0f);
        c3DVf Speed=c3DVf(ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED);
        Speed[0]+=mpThruster->mmCache.Zx();
        Speed[1]+=mpThruster->mmCache.Zy();
        Speed[2]+=mpThruster->mmCache.Zz();
        lpPart->SetSpeed(ParticleArcSpeeds(Speed,0.3,0.6).v);
        Speed*=10.0f;
        Speed+=mpThruster->mmCache.Position();
        lpPart->SetPosition(Speed.v);

        float lpSecond[4]={0.1f,RANDOM_NUMBER,0.8f+RANDOM_NUMBER*0.2f,0.1f};
        lpPart->SetColor(lpSecond);
    }

};


void cLeviathanThruster::Run()
{
	cLeviathanComponent::Run();
    if(mpReactor && mpReactor->GenerateEnergy(mfEnergyCost)) Thrust(mfMaxThrust);
};

	void cLeviathanThruster::Stop()
	{
		_KILL(mpThruster);
	    cLeviathanComponent::Stop();

	};


//This is a function for receiving signals from other processes.
bool cLeviathanThruster::UserSignal(SIGNAL lsSignal,void *lpData)
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
                mfMaxThrust=0.0f;
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

void cLeviathanThruster::ReduceHealth()
{
    mfHealth-=cDamage::mfFinalDamage;
    mfMaxThrust=mfStartMaxThrust*mfHealth*mfMaxHealthInv;
    //If the damage is more than the fighter can take kill it.
    //This will call Stop()
    if(mfHealth<0.0f)
    {
        SignalDeath();
        _KILL_THIS();
    }

}

