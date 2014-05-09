#include "stdafx.h"
#include "../../main.h"


cMessageFeed *cPlanningScreen::mpFeed=0;
cPlanningScreen::cPlanningScreen(cLeviathanSettings *lpSettings)
{

 mpLeviathanSettings=lpSettings;
 if(!mpFeed) mpFeed=_CREATE(cMessageFeed(7,_GET_TEXTURE_FILE("DataDisplayBox"),cRGBA(0.0f,0.8f,0.0f,0.9f),_GET_FONT_FILE("Ecliptic"),cRGBA(0.0f,0.0f,0.0f,1.0f),c2DVf(gpWindow->RenderAreaWidth()-100.0f,gpWindow->RenderAreaHeight()-100.0f),gp2DCamera));
 mpLev=_CREATE(cPlanningLeviathan(lpSettings));

    _CAMERA->Identity();
    _CAMERA->Position(0.0f,0.0f,1000.0f);

 _CAMERA->Width(PLANNING_CAMERA_WIDTH);
 _CAMERA->Height(PLANNING_CAMERA_HEIGHT);
 _CAMERA->ViewportX(DATA_BOX_WIDTH);
 _CAMERA->ViewportWidth(_WINDOW->RenderAreaWidth()-DATA_BOX_WIDTH);
 _CAMERA->UpdateProjectionMatrix();


 gpClearCamera->Clear(1);
 gpClearCamera->ClearColor(cRGBA(0.0f,0.0f,0.0f,1.0f).Color());
 gpClearCamera->ViewportWidth(DATA_BOX_WIDTH);
 gpClearCamera->ViewportHeight(_WINDOW->RenderAreaHeight());
 gpClearCamera->ViewportX(0.0f);
 gpClearCamera->ViewportY(0.0f);

 mpButton=_CREATE(cButton(gp2DCamera));
 mpButton->Shader("Image2DUniformColorProgram");
 mpButton->AddTexture("LaunchMission");
 mpButton->SetUniform("UniformColor",cRGBA(0.0f,1.0f,0.0f,1.0f).Color());
 mpButton->Width(120.0f);
 mpButton->Height(90.0f);

 mpButton->Position(_WINDOW->RenderAreaWidth()-60.0f,45.0f);

 mpRack=_CREATE(cPlanningMissileRack(MISSILE_SLOTS));

 mpPlayerGun=_CREATE(cPlayerGun);


    cLight *mpLight=_CREATE(cLight);
	mpLight->Ambient(0.3f,0.3f,0.3f,1.0f);
	mpLight->Specular(1.0f,1.0f,1.0f,1.0f);
	mpLight->Diffuse(1.0f,1.0f,1.0f,1.0f);
	mpLight->Position(0.0f,0.0f,0.0f);

}

void cPlanningScreen::UpdateWindow()
{
 if(gpClearCamera) gpClearCamera->ViewportHeight(_WINDOW->RenderAreaHeight());
 if(mpFeed)mpFeed->UpdatePosition();
};



void cPlanningScreen::Run()
{
 if(mpButton->Hover()) mpButton->SetUniform("UniformColor",cRGBA(1.0f,0.0f,0.0f,1.0f).Color());
 else mpButton->SetUniform("UniformColor",cRGBA(0.0f,1.0f,0.0f,1.0f).Color());

  if(mpButton->Pressed())
  {
	 _KILL_THIS();
	 _KILL(mpButton);
	mpButton=0;
    _KILL(mpLev);
    mpLev=0;
	_KILL(gpClearCamera);
 	gpClearCamera=0;
	_KILL(mpFeed);
	mpFeed=0;
	cCore::mpPlanScreen=0;

	for(uint32 liCount=0;liCount<MISSILE_SLOTS;++liCount)
	{
        gcPlannedSettings.mpMissileSlots[liCount]=mpRack->mpSlots[liCount].miType;
	}

	gcPlannedSettings.mcPlayerGun.mfReloadTime=mpPlayerGun->mfReloadTime;
	gcPlannedSettings.mcPlayerGun.mfDamage=mpPlayerGun->mfDamage;


	_KILL(mpRack);
	mpRack=0;

	_KILL(mpPlayerGun);

	_CREATE(cCombatScreen(mpLeviathanSettings));
  }

  if(KEY_BACKSPACE)
  {
		_KILL(this);
		_KILL(mpButton);
		mpButton=0;
    	_KILL(mpLev);
    	mpLev=0;
		gpClearCamera->Clear(0);
		_KILL(mpFeed);
		mpFeed=0;
		cCore::mpPlanScreen=0;

		_KILL(mpRack);
		mpRack=0;
		_KILL(mpPlayerGun);

	cLeviathanArray::Instance()->SolarSystemMap();
  }

}

void cPlanningScreen::Stop()
{

}
