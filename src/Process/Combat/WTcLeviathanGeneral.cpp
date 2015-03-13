
#include "../../main.h"

#define FREE_THRUST 100.0f
#define FREE_ANGLE_THRUST 50.0f

cParticleSettings *cLeviathanComponent::mpFlameTrailSettings=0;


cLeviathanDeath::cLeviathanDeath(vRenderNode *lpNode,float Life)
{
    mpComponentNode=lpNode;
    for(uint32 liCount=0;liCount<600;++liCount)
    {
        cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
        //cParticle *lpPart=_CREATE(cParticle());
        lpPart->SetLife(0.5f+1.5f*RANDOM_NUMBER);
        lpPart->SetSize(2500.0f);
        lpPart->SetSpeed(ParticleBallSpeeds(PARTICLE_SPEED,0.9f).v);
        lpPart->SetPosition(mpComponentNode->mmCache.Position());

        float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
        lpPart->SetColor(lpSecond);
    }
    mfLife=Life;
};
void cLeviathanDeath::Run()
{
        cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
        //cParticle *lpPart=_CREATE(cParticle());
        lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
        lpPart->SetSize(5000.0f);
        c3DVf Speed=c3DVf(ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED);
        lpPart->SetSpeed(Speed.v);
        lpPart->SetPosition(mpComponentNode->mmCache.Position());

        float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
        lpPart->SetColor(lpSecond);
        mfLife-=REACTOR_DEATH_DAMAGE_RATE;
        if(mfLife<REACTOR_DEATH_DAMAGE_RATE*2) _KILL_THIS();
};
void cLeviathanDeath::Stop()
{

};

cParticleSettings *cLeviathanDamage::mpSettings=0;

cLeviathanDamage::cLeviathanDamage(cLeviathanComponent *lpNode,float lfRate)
{
    mpComp=lpNode;
    mfRate=lfRate;
    mfTimer=RANDOM_NUMBER*mfRate;
    if(!mpSettings)
    {
        mpSettings=new cParticleSettings();
        float lfData[8]={0.8f,0.0f,0.0f,0.2f,0.2f,1.0f,0.0f,0.2f};
        mpSettings->SetColours(lfData);
        lfData[0]=5.0f;
        lfData[1]=5.0f;
        mpSettings->SetSizes(lfData);
        lfData[0]=2.0f;
        lfData[1]=1.5f;
        mpSettings->SetLife(lfData);
    }
};

void cLeviathanDamage::Run()
{

    if(mfTimer<0.0f)
    {
        c3DVf lfDirect=GenerateUniformRandomVector()*5*PARTICLE_SPEED;
        for(uint32 liCount=0;liCount<100;++liCount)
        {
            cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
            lpPart->SetLife(0.5f+1.0f*RANDOM_NUMBER);
            lpPart->SetSize(5000.0f);
            c3DVf lfTemp;
            lfTemp=mpComp->mpMoment->GSpeeds();

            lfTemp*=0.001;
            lfTemp+=ParticleArcSpeeds(lfDirect.v,0.8f,0.9f);
            lpPart->SetSpeed(lfTemp.v);

            lpPart->SetPosition(mpComp->ComponentNode()->mmCache.Position());
            float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
            lpPart->SetColor(lpSecond);

        }
        mfTimer=RANDOM_NUMBER*mfRate;
    }
    else
    {
        mfTimer-=0.04f;
    }
};

void cLeviathanDamage::Stop()
{

};





cMomentumFRI *cLeviathanComponent::Momentum(){return mpMoment;};

cLeviathanComponent::cLeviathanComponent(cLeviathanComponentSettings *lpSettings) : cFoundationTracking(lpSettings->mpFoundations)
{

 if(!mpFlameTrailSettings)
 {
     mpFlameTrailSettings=_CREATE(cParticleSettings);
                float lfData[8]={0.8f,0.0f,0.0f,0.3f,0.2f,1.0f,0.0f,0.1f};
        mpFlameTrailSettings->SetColours(lfData);
        lfData[0]=3000.0f;
        lfData[1]=3000.0f;
        mpFlameTrailSettings->SetSizes(lfData);
        lfData[0]=0.5f;
        lfData[1]=0.4f;
        mpFlameTrailSettings->SetLife(lfData);

        lfData[0]=0.0f;
        lfData[1]=0.0f;
        lfData[2]=0.0f;
        lfData[3]=0.0f;
        lfData[4]=0.0f;
        lfData[5]=0.0f;
        mpFlameTrailSettings->SetPositions(lfData);
 }


mpComponentNode->Process(this);

 mpMoment=0;
 mbReactorDeath=false;
 mfHealth=lpSettings->mfHealth;
 mfMaxHealthInv=1.0f/mfHealth;
 mpDamage=0;
 mpTreeBase=0;
 mpTargeted=0;

 mfEnergyCost=lpSettings->mfEnergyCost;

 if(lpSettings->mpReactor)
 {
   mpReactor=lpSettings->mpReactor->mpReactorComp;
 }
 else mpReactor=0;

 mpArmour=vArmour::MakeArmour(lpSettings->mpArmour,mpReactor);
}

void cLeviathanComponent::PlayTargetedNoise(){if(mpTargeted && gbSoundOn) mpTargeted->Play();};

void cLeviathanComponent::Run()
{
    mpArmour->Reset();

    if(mpMoment)
    {
        mpMoment->Update();
    }
    if(mbReactorDeath)
    {
        gpLeviathan->mcReactorDamage.mfPos=c3DVf(mpComponentNode->mmCache.X()+ZEROED_RANDOM_NUMBER*FLAME_TRAIL_SCATTER,mpComponentNode->mmCache.Y()+ZEROED_RANDOM_NUMBER*FLAME_TRAIL_SCATTER,mpComponentNode->mmCache.Z()+ZEROED_RANDOM_NUMBER*FLAME_TRAIL_SCATTER);
        cDamage::mfFinalDamage=gpLeviathan->mcReactorDamage.mfDamage;
        ReduceHealth();
    }


}

void cLeviathanComponent::FlameTrail(cDamage *lfCentre)
{
    if(cDamage::mfFinalDamage>FLAME_TRAIL_DAMAGE_LIMIT && RANDOM_NUMBER>FLAME_TRAIL_PROBABILITY)
    {
        float lfDirect[5];
        memcpy(lfDirect,(GenerateUniformRandomVector()*0.1f).v,sizeof(float)*3);
        lfDirect[3]=0.2f;
        lfDirect[4]=0.03f;
        mpFlameTrailSettings->SetSpeeds(lfDirect);

        c3DVf lfValue=lfCentre->mfPos-mpComponentNode->mmCache.Position();

        _CREATE(cParticleSource(12.0f,25.0f,*mpFlameTrailSettings,mpComponentNode,lfValue,cLeviathan::mpLeviathanParticleHandler));

    }
}

void cLeviathanComponent::Stop()
{
    if(mpMoment) {delete mpMoment; mpMoment=0;}
    if(mpDamage) {_KILL(mpDamage);};
    for(uint32 liCount=0;liCount<500;++liCount)
        {
            cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
            lpPart->SetLife(0.5f+1.0f*RANDOM_NUMBER);
            lpPart->SetSize(5000.0f);
            lpPart->SetSpeed(ParticleBallSpeeds(0.5f,0.5f).v);
            lpPart->SetPosition(mpComponentNode->mmCache.Position());
            float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
            lpPart->SetColor(lpSecond);

        }
    mpComponentNode->Process(0);
    _KILL(mpComponentNode);

    delete mpArmour;
    mpArmour=0;

}

bool cLeviathanComponent::UserSignal(SIGNAL lsSignal,void *lpData)
{
    (void) lpData;
        //determine the type of signal.
    switch(lsSignal)
    {
         case LEVIATHAN_COMPONENT_KILL :
         {
            _KILL_THIS();
            return 1;
         }
        case CHANGE_TREE_BASE :
        {
            mpTreeBase=(cLeviathanComponent*)lpData;
            return 1;
        }
         case LEVIATHAN_REACTOR_DEATH :
        {
            mbReactorDeath=true;
           if(mpMoment)  return 1;
        }
        case LEVIATHAN_COMPONENT_FREE :
        {
            if(FoundationDeath(reinterpret_cast<vRenderNode*>(lpData)))
            {

                if(lpData) mpComponentNode->Equals(mpComponentNode->mmCache);
                 mpMoment=_CREATE(cMomentumFRI(&(mpComponentNode->ThisMatrix())));
                if(lsSignal==LEVIATHAN_REACTOR_DEATH) mpDamage=_CREATE(cLeviathanDamage(this,10.0f));
                 if(mpTreeBase)
                 {
                     mpMoment->EqualsRelative(mpTreeBase->Momentum(),&(mpComponentNode->mmCache),&(mpTreeBase->ComponentNode()->mmCache));
                 }
                 c3DVf lpMomentVector=mpComponentNode->Position();
                 lpMomentVector.Normalise();
                 lpMomentVector=ParticleArcSpeeds(lpMomentVector,0.4f,0.6f);
                 lpMomentVector*=FREE_THRUST;
                 mpMoment->Thrust(lpMomentVector);
                 mpMoment->ThrustAngle(ZEROED_RANDOM_NUMBER*FREE_ANGLE_THRUST,ZEROED_RANDOM_NUMBER*FREE_ANGLE_THRUST,ZEROED_RANDOM_NUMBER*FREE_ANGLE_THRUST);

                 mpComponentNode->TreeProcessUserSignal(CHANGE_TREE_BASE,this);

                 cCollisionObject *lpTemp=_CREATE(cCollisionObject(mpComponentNode,this));
                 lpTemp->SetType(mpComponentNode->GetSize());
                 lpTemp->CollisionFilter(ENEMY_WHOLE_CHECK);
            }
             return 1;
        }
        case BEAM_COLLISION :
        {
            mpArmour->Damage(reinterpret_cast<cDamage*>(lpData));
            FlameTrail(reinterpret_cast<cDamage*>(lpData));
        }
        case EXPLOSION_COLLISION :
        {
            mpArmour->Damage(reinterpret_cast<cDamage*>(lpData));
            ReduceHealth();
            return 1;
        }

        default :
        {
            return 0;
        }
    }
return 0;
}

void cLeviathanComponent::SignalDeath()
{
    if(mbReactorDeath) gpLeviathan->UserSignal(LEVIATHAN_REACTOR_DEATH,this);
    else gpLeviathan->UserSignal(LEVIATHAN_COMPONENT_DEATH,this);
   if(gpPlayer) gpPlayer->UserSignal(DEAD_FIGHTER,this);
};

void cLeviathanComponent::Display(cCombatStatusBox *lpPoint)
{
    _WAKE(lpPoint->mpFieldDisplay[0]);
    _WAKE(lpPoint->mpFields[0]);
    _SLEEP(lpPoint->mpFieldDisplay[1]);
    _SLEEP(lpPoint->mpFields[1]);
 lpPoint->mpFields[0]->Text("Health");
};

void cLeviathanComponent::UpdateFieldColors(cCombatStatusBox *lpPoint)
{
    lpPoint->mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(1.0f-mfHealth*mfMaxHealthInv,mfHealth*mfMaxHealthInv,0.0f,1.0f).Color());
    return ;
};

float cLeviathanComponent::Health()
{
 return mfHealth*mfMaxHealthInv;
};
