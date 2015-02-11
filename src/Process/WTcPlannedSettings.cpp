
#include "../main.h"

cPlannedSettings gcPlannedSettings;
cGameSettings gcGameSettings;

uint16 cTargetingFlag::ID(){return miComponentID;};
c3DVf cTargetingFlag::Position(){return mfPosition;};

cTargetingFlag::cTargetingFlag()
{
    miComponentID=0;
};

void cTargetingFlag::SetID(uint16 liID,c3DVf lfPos)
{
    miComponentID=liID+1;
    mfPosition=lfPos;
};

void cGameTarget::operator=(cGameTarget lpOther)
{
    mpComponent=lpOther.mpComponent;
    mpMatrix=lpOther.mpMatrix;
    mfPosition=lpOther.mfPosition;
};

void cGameTarget::SetTarget(cMatrix4 *lpMatrix,c3DVf lfPos)
{
    mpComponent=0;
    mpMatrix=lpMatrix;
    mfPosition=lfPos;
};

void cGameTarget::SetTarget(cLeviathanComponent *lpComponent,c3DVf lfPos)
{
    if(lpComponent)
    {
        mpComponent=lpComponent;
        mpMatrix=&(lpComponent->ComponentNode()->mmCache);
        mfPosition=lfPos;
    }
    else
    {
        Clear();
    }
};

void cGameTarget::SetTarget(vRenderObject *lpComponent,c3DVf lfPos)
{
    mpComponent=0;
    mpMatrix=&(lpComponent->mmCache);
    mfPosition=lfPos;
};
bool cGameTarget::CheckDeath(cLeviathanComponent *lpComp)
{
    if(mpComponent==lpComp){mpComponent=0; mpMatrix=0; return 1;}
    return 0;
};
bool cGameTarget::CheckDeath(cMatrix4 *lpMat)
{
    if(mpMatrix==lpMat){mpComponent=0; mpMatrix=0; return 1;}
    return 0;
};

bool cGameTarget::Targeted()
{
    return mpMatrix;
}

c3DVf cGameTarget::GetPosition()
{
    if(mpMatrix)
    {
        c3DVf lfReturn;
        lfReturn=mpMatrix->RotateVectorByAngles(mfPosition);
        lfReturn+=mpMatrix->Position();
        return lfReturn;
    }

    return c3DVf(0.0f,0.0f,0.0f);
};

cGameTarget::cGameTarget()
{
    mpComponent=0;
    mpMatrix=0;
};

void cGameTarget::Clear()
{
    mpComponent=0;
    mpMatrix=0;
};

void cGameSettings::CheckDeath(cLeviathanComponent* lpComp)
{
    for(uint32 liCount=0;liCount<12;++liCount) mcTargets[liCount].CheckDeath(lpComp);
};
