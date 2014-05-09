
#include "stdafx.h"
#include "../main.h"

cIcoSphere *cCore::mpIcoSphereBase=0;
cCircleLineData *cCore::mpCircleBase=0;

cText *cCore::mpDead=0;

//Global Pointers to make access to the cPlayer object and the 2DCamera easier.
cCamera *gp2DCamera=0;
cCamera *gpClearCamera=0;
cPlanningScreen *cCore::mpPlanScreen=0;
cLeviathanSettings *cCore::mpLevSettings=0;

cStarMap *gpStarMap=0;


//Constructor for cCore to initialise and setup the game.
//Currently no menu.
cCore::cCore()
{

	trace("Enterting cCore::cCore")
    //Randomise the Random number generator, so random numbers have seed based on current time.
	SEED_RANDOM_NUMBERS;

    //Load Media Files to be used by this program.
    //This is currently loading ALL media for the program.
    //Each of these files contains several media items.
    //open these files with the IMF Handler to see the details of the items.
	trace("Loading imf files...")

	//_LOAD("../Media/Shaders/TexturingLightProgram.imf");
	//_LOAD("../Media/Shaders/NormalMappingProgram.imf");
	//_LOAD("../Media/Shaders/NewPointSizingProgram.imf");
	_LOAD_SETTINGS_FILE("../Media/Settings/UserSettings.txt");

	cUserSettings::FileSettings();

	_SETTINGS_STORE->Output("../Media/Settings/TestFile.txt");


	_LOAD("../Media/Shaders/CompleteProgram.imf");
	_LOAD("../Media/Shaders/SolarShader.imf");
	//_LOAD("../Media/Audio/SoundPack.imf");
    _LOAD("../Media/Fonts/FontPack.imf");

	_LOAD("../Media/Models/FlyingModelPack.imf");
	//_LOAD("../Media/Models/PlayerShip.imf");
	//_LOAD("../Media/Models/PlayerShields.imf");
	_LOAD("../Media/Audio/LeviathanSounds.imf");
	_LOAD("../Media/Audio/LeviathanVoices.imf");
	_LOAD("../Media/Models/CompletePlayerShip.imf");
	_LOAD("../Media/Models/UnitBox.imf");
	_LOAD("../Media/Models/UnitSphere.imf");
	_LOAD("../Media/Textures/LeviathanImages.imf");
	//_LOAD("../Media/Textures/DialBoundary.imf");
	_LOAD("../Media/Textures/PlayerShipDisplayImages.imf");
	_LOAD("../Media/Textures/BricksMaps.imf");
	_LOAD("../Media/Textures/PerlinNoise.imf");
	_LOAD("../Media/Textures/ComponentIcons.imf");
	_LOAD("../Media/Textures/TypeIcons.imf");
	//_LOAD("../Media/Textures/HullDamageDecal.imf");
	//_LOAD("../Media/Textures/NormalMappingTexture.imf");
	/*
	_LOAD("../Media/Models/LeviathanTraining.imf");
	_LOAD("../Media/Models/LeviathanTrainingCollisions.imf");
	_LOAD("../Media/Models/LeviathanTrainingComponents.imf");
	_LOAD("../Media/Models/LeviathanTrainingComponents2.imf");
	_LOAD("../Media/Models/LeviathanTrainingShields.imf");
*/
    _LOAD("../Media/Models/TrainingLeviathan.imf");

	mpIcoSphereBase=new cIcoSphere(3,1.0f,1,1);
  	mpCircleBase=new cCircleLineData(1.0f,100);

    //Set the Background Clear Colour for the default camera to Black.
	_CAMERA->ClearColor(0.0f,0.0f,0.0f,0.0f);

    //Lock the mouse to the centre of the screen.
	//_MOUSE->Lock();
	//Hide The Cursor
	//_MOUSE->Hide();

//Set up the viewing parameters for the default camera.
//Give a good view depth (unfortunately requiring a large near depth to avoid precision loss.
//Adjust for big depth with wide and high camera dimensions.
//Finally apply the changes to the Camera. See cCamera.
_CAMERA->Far(CAMERA_FAR);
_CAMERA->Near(CAMERA_NEAR);
_CAMERA->Width(CAMERA_WIDTH);
_CAMERA->Height(CAMERA_HEIGHT);
_CAMERA->UpdateProjectionMatrix();

    //Create a second camera to be used for 2D effects. This Allows 2D images and text to be applied after the primary camera has rendered.
    //The default camera could be used for this, but rendering order would not be controlled.
    //Make it take the entire screen size with a smaller render range than the primary camera.
    //Tell it not to clear the screen before rendering (as it would clear everything done by the default camera).

    gpClearCamera=_CREATE(cCamera);
    gpClearCamera->Clear(false);

	gp2DCamera=_CREATE(cCamera);
	gp2DCamera->Proportional(1);
	gp2DCamera->ViewportProportional(0.0,0.0,1.0,1.0);
	gp2DCamera->mmPerspective2D.Far(1000.0f);
	gp2DCamera->mmPerspective2D.Near(1.0f);
	gp2DCamera->UpdateProjectionMatrix();
	gp2DCamera->Clear(false);

    cLeviathanArray::Instance();

}

void cCore::Run()
{
    //If the User has pressed ESC or Ctrl+C Quit the program.
	if(KEY_ESC || (KEY_CTRL && KEY_c)) {_QUIT;}


}
//Function to be called when cCore Dies.
void cCore::Stop()
{
	delete mpLevSettings;
	mpLevSettings=0;

	_KILL(gpStarMap);

	if(mpDead) _KILL(mpDead);
}

void cCore::Planning()
{
    //Asteroids();

mpPlanScreen=_CREATE(cPlanningScreen(mpLevSettings));

};
void cCore::Game()
{
    _CREATE(cCombatScreen(mpLevSettings));

};

void cCore::Fighters()
{

    //Set a Shader for the cCameras default Particle Handler.
//float mfLife=50.0f;
    //_CAMERA->ParticleHandler()->Shader("BbPointSizingProgram");
	_CAMERA->ParticleHandler()->Shader("NewPointSizingProgram");
	//_CAMERA->ParticleHandler()->Transparency(2);
	//_CAMERA->ParticleHandler()->DepthTest(0);
    _CAMERA->ParticleHandler()->Transparency(5);

    cMapDisplay *mpMap=_CREATE(cMapDisplay(_CAMERA));

    //Give it default values.
    //Set the Shader Variable called mfSize to equal mfLife (3.0)
    //_CAMERA->ParticleHandler()->SetVariable("Bb_Size",&mfLife);
    //mfLife=90.0f;
    //Set the Shader Variable called mfFade to equal mfLife (90.0)
    //_CAMERA->ParticleHandler()->SetVariable("mfFade",&mfLife);

	Asteroids();

    //Lock the mouse to the centre of the screen.
	_MOUSE->Lock();
	//Hide The Cursor
	_MOUSE->Hide();

//Create a cProcess object of type cPlayer. see ./WTcPlayer.cpp and ./WTcPlayer.h
//Pass it the default Camera as it's owner.
//It will use this camera for creating it's view port.
    _CREATE(cPlayer(_CAMERA));
    mpMap->Follow(gpPlayer->mpHull);


    _CREATE( cFighter(cDamage(25.0f,DAMAGE_TYPE_INSTANTANEOUS)) );
    _CREATE( cFighter(cDamage(25.0f,DAMAGE_TYPE_INSTANTANEOUS)) );
    _CREATE( cFighter(cDamage(25.0f,DAMAGE_TYPE_INSTANTANEOUS)) );
    _CREATE( cFighter(cDamage(25.0f,DAMAGE_TYPE_INSTANTANEOUS)) );
    _CREATE( cFighter(cDamage(25.0f,DAMAGE_TYPE_INSTANTANEOUS)) );

}

void cCore::Asteroids()
{
    for(uint8 liCount=0;liCount<5;++liCount)
	{
        _CREATE(cAsteroidObject(5));
	}
}
