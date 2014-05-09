#include "stdafx.h"
#include "../../main.h"

cRGBA *cPlanningMissileRack::msMissileColors=PrepMissileColors();

cPlanningMissileRack::~cPlanningMissileRack()
{
    delete []mpSlots;
    mpSlots=0;
};

cPlanningMissileRack::cPlanningMissileRack(uint32 liSlots)
{
    mpImage=_CREATE(cImage(gp2DCamera));
    mpImage->Shader("Image2DProgram");
    mpImage->AddTexture("MissileRack");
    mpImage->PositionX(PLANNING_MISSILE_RACK_X);
    mpImage->PositionY(PLANNING_MISSILE_RACK_Y);
    mpImage->Width(PLANNING_MISSILE_RACK_SIZE);
    mpImage->Height(PLANNING_MISSILE_RACK_SIZE);
    //mpImage->Priority(4.0f);
	mpImage->Transparency(4);

    miSlots=liSlots;
    mpSlots=new cPlanningMissileSlot[miSlots];

    float lfAngle=2*WT_PI/miSlots;

    for(uint32 liCount=0;liCount<miSlots;++liCount)
    {
        mpSlots[liCount].miType=(uint32)(RANDOM_NUMBER*MISSILE_TYPES)%MISSILE_TYPES;
        mpSlots[liCount].mpButton=_CREATE(cButton(gp2DCamera));
        mpSlots[liCount].mpButton->Shader("Image2DUniformColorProgram");

        switch(mpSlots[liCount].miType)
        {
            case MISSILE_TYPE_EXPLOSIVE :{mpSlots[liCount].mpButton->AddTexture("EXMissileID");}break;
            case MISSILE_TYPE_LASER :{mpSlots[liCount].mpButton->AddTexture("LSMissileID");}break;
            case MISSILE_TYPE_EMP:{mpSlots[liCount].mpButton->AddTexture("SDMissileID");}break;
            case MISSILE_TYPE_CHAFF :{mpSlots[liCount].mpButton->AddTexture("CHMissileID");}break;
            case MISSILE_TYPE_MW :{mpSlots[liCount].mpButton->AddTexture("MWMissileID");}break;
            default : {mpSlots[liCount].mpButton->AddTexture("MWMissileID");}
        }

        mpSlots[liCount].mpButton->Width(PLANNING_MISSIlE_SLOT_SIZE);
        mpSlots[liCount].mpButton->Height(PLANNING_MISSIlE_SLOT_SIZE);
        mpSlots[liCount].mpButton->SetUniformPointer("UniformColor",msMissileColors[mpSlots[liCount].miType].Color());
        //mpSlots[liCount].mpButton->Priority(3.0f);
        mpSlots[liCount].mpButton->Transparency(5);
        mpSlots[liCount].mpButton->Position(PLANNING_MISSILE_RACK_X-sin(lfAngle*(MISSILE_SLOTS-liCount))*PLANNING_MISSILE_SLOT_RADIUS,PLANNING_MISSILE_RACK_Y+cos(lfAngle*(MISSILE_SLOTS-liCount))*PLANNING_MISSILE_SLOT_RADIUS);
    }

};

void cPlanningMissileRack::Run()
{
    for(uint32 liCount=0;liCount<miSlots;++liCount)
    {
		//Normally would use Clicked, but Locking the mouse for Leviathan rotation, plays with this
        if(mpSlots[liCount].mpButton->Clicked())
        {
           mpSlots[liCount].miType=(mpSlots[liCount].miType+1)%MISSILE_TYPES;
           mpSlots[liCount].mpButton->ClearTextureStack();
         switch(mpSlots[liCount].miType)
         {
            case MISSILE_TYPE_EXPLOSIVE :{mpSlots[liCount].mpButton->AddTexture("EXMissileID");}break;
            case MISSILE_TYPE_LASER :{mpSlots[liCount].mpButton->AddTexture("LSMissileID");}break;
            case MISSILE_TYPE_EMP:{mpSlots[liCount].mpButton->AddTexture("SDMissileID");}break;
            case MISSILE_TYPE_CHAFF :{mpSlots[liCount].mpButton->AddTexture("CHMissileID");}break;
            case MISSILE_TYPE_MW :{mpSlots[liCount].mpButton->AddTexture("MWMissileID");}break;
            default : {mpSlots[liCount].mpButton->AddTexture("MWMissileID");}
        }
           mpSlots[liCount].mpButton->SetUniformPointer("UniformColor",msMissileColors[mpSlots[liCount].miType].Color());
        }

    }
};
void cPlanningMissileRack::Stop()
{
    _KILL(mpImage);
    mpImage=0;

    for(uint32 liCount=0;liCount<miSlots;++liCount)
    {
        _KILL(mpSlots[liCount].mpButton);
    }

};

cRGBA *cPlanningMissileRack::PrepMissileColors()
{
 cRGBA *lsColors=new cRGBA[MISSILE_TYPES+1];
 lsColors[MISSILE_TYPE_EXPLOSIVE]=MISSILE_EXPLOSIVE_COLOR;
 lsColors[MISSILE_TYPE_LASER]=MISSILE_LASER_COLOR;
 lsColors[MISSILE_TYPE_EMP]=MISSILE_EMP_COLOR;
 lsColors[MISSILE_TYPE_CHAFF]=MISSILE_CHAFF_COLOR;
 lsColors[MISSILE_TYPE_MW]=MISSILE_MW_COLOR;
 lsColors[MISSILE_TYPE_EMPTY]=MISSILE_EMPTY_COLOR;
return lsColors;
}
