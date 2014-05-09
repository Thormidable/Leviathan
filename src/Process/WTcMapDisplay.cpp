#include "stdafx.h"
#include "../main.h"

cMapDisplay *cMapDisplay::mpStaticThis=0;
/*
#define MAP_SIZE 10.0f
#define MAP_SCALE 1.0f/800.0f
#define MAP_LARGEST_SIZE sqrt(MAP_SIZE*MAP_SIZE)
#define MAP_DISPLAY_X 0.0f
#define MAP_DISPLAY_Y (mpCamera->Height()/1.8f)
#define MAP_DISPLAY_Z (mpCamera->Near()+MAP_SIZE)
*/

cMapDisplayObject::cMapDisplayObject(vRenderObject *lpObj,cRGBA lcColor,string lsTexture)
{
    mpPoint=_CREATE(cBillBoard(cMapDisplay::mpStaticThis->mpNode));
    mpPoint->Shader("BillBoardProgram");
    mpPoint->AddTexture(lsTexture);
    float lfSize=BATTLESCAPE_ICON_SIZE;
    mpPoint->SetUniform("Bb_Size",&lfSize);

    mpLine=_CREATE(cLine(cMapDisplay::mpStaticThis->mpNode));
    mpLine->Shader("SetUniformColorProgram");
    mpLine->SetVariable("ModelColor",lcColor.Color());
    mpLine->Transparency(13);

    mpFollow=&(lpObj->mmCache);

};

cMapDisplayObject::~cMapDisplayObject()
{
    _KILL(mpPoint);
    _KILL(mpLine);
    mpPoint=0;
    mpLine=0;
    mpFollow=0;
}

void cMapDisplay::Follow(cRenderObject *lpFollow)
{
    mpFollow=lpFollow;
}
cMapDisplay::cMapDisplay(cCamera *lpCamera)
{
 mpStaticThis=this;
 mpCamera=lpCamera;
 mpNode=new cRenderNode(lpCamera);
 mpNode->Position(MAP_DISPLAY_X,MAP_DISPLAY_Y,MAP_DISPLAY_Z);

 cRGBA MyColor(0.0f,1.0f,0.5f,0.5f);

 cLine *lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(-MAP_SIZE,0.0f,-MAP_SIZE);
 lpLine->Vector(0.0f,0.0f,MAP_SIZE*2);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(-MAP_SIZE,0.0f,-MAP_SIZE);
 lpLine->Vector(MAP_SIZE*2,0.0f,0.0f);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(MAP_SIZE,0.0f,MAP_SIZE);
 lpLine->Vector(-MAP_SIZE*2,0.0f,0.0f);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(MAP_SIZE,0.0f,MAP_SIZE);
 lpLine->Vector(0.0f,0.0f,-MAP_SIZE*2);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(MAP_SIZE,0.0f,0.0f);
 lpLine->Vector(-MAP_SIZE*2,0.0f,0.0f);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(0.0f,0.0f,MAP_SIZE);
 lpLine->Vector(0.0f,0.0f,-MAP_SIZE*2);







 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(-MAP_SIZE*0.5,0.0f,-MAP_SIZE);
 lpLine->Vector(0.0f,0.0f,MAP_SIZE*2);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(-MAP_SIZE,0.0f,-MAP_SIZE*0.5);
 lpLine->Vector(MAP_SIZE*2,0.0f,0.0f);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(MAP_SIZE,0.0f,MAP_SIZE*0.5);
 lpLine->Vector(-MAP_SIZE*2,0.0f,0.0f);

 lpLine=_CREATE(cLine(mpNode));
 lpLine->Shader("SetUniformColorProgram");
 lpLine->SetVariable("ModelColor",MyColor.Color());
 lpLine->Transparency(12);
 lpLine->Position(MAP_SIZE*0.5,0.0f,MAP_SIZE);
 lpLine->Vector(0.0f,0.0f,-MAP_SIZE*2);





};

void cMapDisplay::Run()
{
 mpNode->Equals(mpCamera);
 mpNode->Advance(MAP_DISPLAY_X,MAP_DISPLAY_Y,MAP_DISPLAY_Z);

};

void cMapDisplay::Stop()
{
 _KILL(mpNode);
 mpNode=0;
};

void cMapDisplay::MapObject(cMapDisplayObject *lpObj)
{
 if(gpPlayer)
 {
    c3DVf Coords=mpFollow->FindPointRelative(lpObj->mpFollow->Position());
    Coords*=MAP_SCALE;
    Coords[1]=-Coords[1];

    if(Coords.MagnitudeSq()>MAP_SIZE*MAP_SIZE)
    {
        _SLEEP(lpObj->mpPoint);
        _SLEEP(lpObj->mpLine);
    }
    else
    {
        _WAKE(lpObj->mpPoint);
        _WAKE(lpObj->mpLine);
        lpObj->mpLine->Position(Coords[0],0.0f,Coords[2]);
        lpObj->mpLine->Vector(0.0f,Coords[1],0.0f);
        lpObj->mpPoint->Position(Coords.v);
    }
 }
};



bool cMapDisplay::UserSignal(SIGNAL lsSignal,void* lpData)
{
 (void) lsSignal;
 (void) lpData;
    return 0;
};
