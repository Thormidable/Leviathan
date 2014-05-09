#include "stdafx.h"
#include "../../main.h"

cLeviathanMultiHullComponent::cLeviathanMultiHullComponent()
{
    mpHull=0;
    mfHealth=0.0f;
};

cLeviathanMultiHull::cLeviathanMultiHull(cLeviathanMultiHullSettings *lpSettings) : cLeviathanComponent(lpSettings)
{
    mpList=new cLeviathanMultiHullComponent[lpSettings->miComponents];
    miComponents=0;

    if(lpSettings->mpCoreMesh)
    {
        mpCoreMesh=_CREATE(cModel(mpComponentNode));
        mpCoreMesh->Mesh(lpSettings->mpCoreMesh);
        gpLeviathan->SetProgram(mpCoreMesh);
    }
    else
    {
        mpCoreMesh=0;
    }

    mpTargeted=_CREATE(cAudioObject);
    mpTargeted->Buffer("HullVoice");

    for(uint32 liCount=0;liCount<lpSettings->miComponents;++liCount)
    {
        AddComponent(lpSettings->mpList[liCount]);
    }
};

cLeviathanMultiHull::cLeviathanMultiHull(cLeviathanComponentSettings *lpSettings,uint32 liComponents,string CoreMesh) : cLeviathanComponent(lpSettings)
{
    mpList=new cLeviathanMultiHullComponent[liComponents];
    miComponents=0;

    if(CoreMesh!="")
    {
        mpCoreMesh=_CREATE(cModel(mpComponentNode));
        mpCoreMesh->Mesh(CoreMesh.c_str());
        gpLeviathan->SetProgram(mpCoreMesh);
    }
    else
    {
        mpCoreMesh=0;
    }

    mpTargeted=_CREATE(cAudioObject);
    mpTargeted->Buffer("HullVoice");
};


void cLeviathanMultiHull::AddComponent(cLeviathanMultiHullComponentSettings &lpSettings)
{
    mpList[miComponents].mpHull=_CREATE(cModel(mpComponentNode));
 	mpList[miComponents].mpHull->Mesh(lpSettings.mpMesh);
    gpLeviathan->SetProgram(mpList[miComponents].mpHull);
    mpList[miComponents].mpHull->Equals(lpSettings.mmPos);

	cCollisionObject *lpColl;
	lpColl=_CREATE(cCollisionObject(mpList[miComponents].mpHull,this));
	lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
    lpColl->SetTypeMesh(lpSettings.mpCollMesh);

    mpList[miComponents].mfHealth=lpSettings.mfStartHealth;
    ++miComponents;
};

void cLeviathanMultiHull::AddComponent(string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos)
{
    mpList[miComponents].mpHull=_CREATE(cModel(mpComponentNode));
 	mpList[miComponents].mpHull->Mesh(Mesh.c_str());
    gpLeviathan->SetProgram(mpList[miComponents].mpHull);
    if(lpPos) mpList[miComponents].mpHull->Equals(lpPos);

	cCollisionObject *lpColl;
	lpColl=_CREATE(cCollisionObject(mpList[miComponents].mpHull,this));
	lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
    lpColl->SetTypeMesh(CollMesh.c_str());

    mpList[miComponents].mfHealth=lfHealth;
    ++miComponents;
};

void cLeviathanMultiHull::SetComponent(uint32 liSlot,string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos)
{
    if(mpList[liSlot].mpHull) _KILL(mpList[liSlot].mpHull);

    mpList[liSlot].mpHull=_CREATE(cModel(mpComponentNode));
 	mpList[liSlot].mpHull->Mesh(Mesh.c_str());
    gpLeviathan->SetProgram(mpList[liSlot].mpHull);
    if(lpPos) mpList[liSlot].mpHull->Equals(lpPos);

	cCollisionObject *lpColl;
	lpColl=_CREATE(cCollisionObject(mpList[liSlot].mpHull,this));
	lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
    lpColl->SetTypeMesh(CollMesh.c_str());

    mpList[liSlot].mfHealth=lfHealth;
};


void cLeviathanMultiHull::Run()
{
	cLeviathanComponent::Run();
    if(mbReactorDeath)
	{
	    bool lbDead=true;
        for(uint32 liCount=0;liCount<miComponents;++liCount)
        {
            mpList[liCount].mfHealth-=REACTOR_DEATH_DAMAGE_RATE;
            if(mpList[liCount].mfHealth<=0.0f)
            {
                if(mpList[liCount].mpHull)
                {
                  _KILL(mpList[liCount].mpHull);
                  mpList[liCount].mpHull=0;
                }

            }
            else lbDead=false;
        }
        if(lbDead)
        {
            _KILL_THIS();
        }
	}

};

	void cLeviathanMultiHull::Stop()
	{
		if(mpCoreMesh) _KILL(mpCoreMesh);
		mpCoreMesh=0;
	    cLeviathanComponent::Stop();

	};

void cLeviathanMultiHull::ReduceHealth()
{

}


//This is a function for receiving signals from other processes.
bool cLeviathanMultiHull::UserSignal(SIGNAL lsSignal,void *lpData)
{
    //determine the type of signal.
    switch(lsSignal)
    {
        //If it is damage, update the health of the fighter.
        case EXPLOSION_COLLISION :
        case BEAM_COLLISION :
        {
            cModel *lpModel=dynamic_cast<cModel*>(gpRenderCollision);
            if(lpModel)
            {
                uint32 liCount;
                for(liCount=0;liCount<miComponents;++liCount)
                {
                    if(mpList[liCount].mpHull==lpModel) break;
                }
                if(liCount<miComponents)
                {
                    mpList[liCount].mfHealth-=*(float*)lpData;
                    if(mpList[liCount].mfHealth<0.0f)
                    {
                        _KILL(mpList[liCount].mpHull);
                        mpList[liCount].mpHull=0;
                        bool lbDead=true;
                        for(liCount=0;liCount<miComponents;++liCount)
                        {
                            if(mpList[miComponents].mpHull) lbDead=false;
                        }
                        if(lbDead==true)
                        {
                            SignalDeath();
                        }
                    }
                }

                if(lsSignal==BEAM_COLLISION) FlameTrail(reinterpret_cast<cDamage*>(lpData));
            }
			return 1;
        }
        case LEVIATHAN_POWER_STATE :
        {
            return 1;
        }
    }

    if(cLeviathanComponent::UserSignal(lsSignal,lpData)) return 1;

    return 0;
};

