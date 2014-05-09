#include "stdafx.h"
#include "../../main.h"

cLeviathanComponentSettings *cLeviathanSettings::spLast=0;

cLeviathanSettings::cLeviathanSettings()
{
    miComponents=0;
    mpComponents=0;
    miNodes=0;
    mpNodes=0;
};

void cLeviathanSettings::Initialise(uint16 liComponents,uint16 liNodes)
{
    miComponents=liComponents;
    mpComponents=new cLeviathanComponentSettings*[miComponents];
    miNodes=liNodes;
    mpNodes=new cLeviathanComponentSettings*[miNodes];
};

cLeviathanSettings::~cLeviathanSettings()
{
    if(mpComponents)
    {
        for(uint32 liCount=0;liCount<miComponents;++liCount)
        {
            delete mpComponents[liCount];
        }
        delete []mpComponents;
        mpComponents=0;
    }
    if(mpNodes) {delete []mpNodes; mpNodes=0;}

};

