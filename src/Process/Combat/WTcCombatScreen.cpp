#include "stdafx.h"
#include "../../main.h"
cCombatScreen::cCombatScreen(cLeviathanSettings *mpLevSettings)
{
	cLeviathanArray::Instance()->ResetForCombat();

//Set up the viewing parameters for the default camera.
//Give a good view depth (unfortunately requiring a large near depth to avoid precision loss.
//Adjust for big depth with wide and high camera dimensions.
//Finally apply the changes to the Camera. See cCamera.
_CAMERA->Far(CAMERA_FAR);
_CAMERA->Near(CAMERA_NEAR);
_CAMERA->Proportional(1);
_CAMERA->ViewportProportional(0.0,0.0,1.0,1.0);
_CAMERA->Width(CAMERA_WIDTH);
_CAMERA->Height(CAMERA_HEIGHT);
_CAMERA->UpdateProjectionMatrix();

    //Set a Shader for the cCameras default Particle Handler.
	_CAMERA->ParticleHandler()->Shader("NewPointSizingProgram");
    _CAMERA->ParticleHandler()->Transparency(5);

    cMapDisplay *mpMap=_CREATE(cMapDisplay(_CAMERA));

	//Asteroids();

    //Lock the mouse to the centre of the screen.
	_MOUSE->Lock();
	//Hide The Cursor
	_MOUSE->Hide();

	mbSoundKey=TOGGLE_SOUND;


    _CREATE(cPlayer(_CAMERA));
    mpMap->Follow(gpPlayer->mpHull);

    _CREATE(cLeviathan(mpLevSettings));

};

void cCombatScreen::Run()
{
	if(TOGGLE_SOUND && !mbSoundKey)
	{
		if(gpPlayer)
		{
			if(gbSoundOn) gpPlayer->MuteSounds();
			else gpPlayer->UnmuteSounds();
		}
		gbSoundOn=!gbSoundOn;
	}
	mbSoundKey=TOGGLE_SOUND;

	if(!gpPlayer)
	{
	    _CAMERA->RotateZ(_MOUSE->XSpeed()*0.003f);
	    _CAMERA->RotateX(_MOUSE->YSpeed()*0.003f);
	    if(_MOUSE->Left()) _CAMERA->Advance(0.1f);
	    if(_MOUSE->Right()) _CAMERA->Advance(-0.1f);
	}
};

void cCombatScreen::Stop()
{

};
