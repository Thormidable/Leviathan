
#include "../../main.h"

cFoundationSettings::cFoundationSettings()
{
    mpComponent=0;
};

void cFoundationSettingsList::Set(cFoundationSettingsList *lpList)
{
    if(lpList)
    {
        delete []mpFoundations;
        miFoundations=lpList->miFoundations;
        mpFoundations=new cFoundationSettings[miFoundations];
        memcpy(mpFoundations,lpList->mpFoundations,sizeof(cFoundationSettings)*miFoundations);
    }
    else
    {
        delete []mpFoundations;
        mpFoundations=0;
        miFoundations=0;
    }
}


cFoundationSettingsList::cFoundationSettingsList(cFoundationSettingsList *lpFoundSet)
{
    miFoundations=lpFoundSet->miFoundations;
    mpFoundations=new cFoundationSettings[miFoundations];
    memcpy(mpFoundations,lpFoundSet->mpFoundations,sizeof(cFoundationSettings)*miFoundations);
};

cFoundationSettingsList::cFoundationSettingsList()
{
    miFoundations=0;
    mpFoundations=0;
}

cFoundationSettingsList::cFoundationSettingsList(uint8 liFoundations)
{
    miFoundations=liFoundations;
    mpFoundations=new cFoundationSettings[miFoundations];
};

cFoundationSettingsList::cFoundationSettingsList(cLeviathanComponentSettings *lpComponent,cMatrix4 lpMatrix)
{
    miFoundations=1;
    mpFoundations=new cFoundationSettings[1];
    mpFoundations->mpComponent=lpComponent;
    mpFoundations->mmMatrix=lpMatrix;
};

cFoundationSettingsList::~cFoundationSettingsList()
{
    delete []mpFoundations;
    mpFoundations=0;
};

cFoundationSettingsList *cFoundationSettingsList::operator=(cFoundationSettingsList *lpList)
{
 Set(lpList);
 return this;
};
cFoundationSettingsList &cFoundationSettingsList::operator=(cFoundationSettingsList &lpList)
{
 Set(&lpList);
 return *this;
};

void cFoundationSettingsList::Foundation(uint8 liFoundation, cLeviathanComponentSettings *lpComponent,cMatrix4 lpMatrix)
{
    if(liFoundation<miFoundations)
    {
        mpFoundations[liFoundation].mpComponent=lpComponent;
        mpFoundations[liFoundation].mmMatrix=lpMatrix;
    }
};

cFoundationSettings *cFoundationSettingsList::Foundation(uint8 liFoundation)
{
    return &mpFoundations[liFoundation];
};

cLeviathanComponentSettings *cFoundationSettingsList::Component(uint8 liFoundation)
{
    return mpFoundations[liFoundation].mpComponent;
};
cMatrix4 *cFoundationSettingsList::Matrix(uint8 liFoundation)
{
    return &(mpFoundations[liFoundation].mmMatrix);
};
