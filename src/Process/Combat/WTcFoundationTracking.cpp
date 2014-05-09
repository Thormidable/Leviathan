#include "stdafx.h"
#include "../../main.h"

cFoundation::cFoundation()
{
    mpComponent=0;
};

cFoundationTracking::cFoundationTracking(cFoundationSettingsList *lpFoundSet)
{
    miFoundations=lpFoundSet->miFoundations;
    mpFoundations=new cFoundation[miFoundations];

    for(uint8 liCount=0;liCount<miFoundations;++liCount)
    {
        if(lpFoundSet->Component(liCount)) mpFoundations[liCount].mpComponent=lpFoundSet->Component(liCount)->mpNode;
        else mpFoundations[liCount].mpComponent=cLeviathan::spLast;
        mpFoundations[liCount].mmMatrix=lpFoundSet->Matrix(liCount);
    }

if(lpFoundSet->Component(0)) mpCurrentFoundation=lpFoundSet->Component(0)->mpNode;
else mpCurrentFoundation=cLeviathan::spLast;

mpComponentNode=_CREATE(cRenderNode(mpCurrentFoundation));
mpComponentNode->Equals(lpFoundSet->Matrix(0));

};
cFoundationTracking::~cFoundationTracking()
{
    delete []mpFoundations;
    mpFoundations=0;
    mpCurrentFoundation=0;
};

cFoundation &cFoundationTracking::operator[](uint8 liFoundation)
{
    return mpFoundations[liFoundation];
};

bool cFoundationTracking::FoundationDeath(vRenderNode *lpComponent)
{
 if(miFoundations<2)
 {
   if(lpComponent==mpCurrentFoundation) {mpCurrentFoundation=0;} return 1;
 }

    for(uint8 liCount=0;liCount<miFoundations;++liCount)
    {
        if(mpFoundations[liCount].mpComponent==lpComponent)
        {
            if(mpCurrentFoundation==lpComponent)
            {
                mpFoundations[liCount].mpComponent=0;
                for(uint8 liLoop=0;liLoop<miFoundations;++liLoop)
                {
                    if(mpFoundations[liLoop].mpComponent)
                    {
                        mpComponentNode->Renderer(mpFoundations[liLoop].mpComponent);
                        mpComponentNode->Equals(mpFoundations[liLoop].mmMatrix);
                        mpCurrentFoundation=mpFoundations[liLoop].mpComponent;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                mpFoundations[liCount].mpComponent=0;
            }
        }
    }
    return 0;
};

vRenderNode *cFoundationTracking::ComponentNode(){return mpComponentNode;};
