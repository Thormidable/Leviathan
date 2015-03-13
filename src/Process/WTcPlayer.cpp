
#include "../main.h"

vMissileSettings **cPlayer::mpMissileSettings=0;
/*=
{
    cRGBA(1.0f,0.0f,0.0f,1.0f),
    cRGBA(0.0f,0.0f,1.0f,1.0f),
    cRGBA(0.0f,1.0f,0.0f,1.0f),
    cRGBA(1.0f,1.0f,0.0f,1.0f),
    cRGBA(0.0f,0.0f,0.0f,1.0f)};*/

cMatrix4 cPlayer::HullMatrix;
cMomentumFRI *cPlayer::lpMomentum=0;

cPlayer *gpPlayer=0;

cPlayer::cPlayer(cCamera *lpCamera,float lfDistance)
{


    gpPlayer=this;



	//Set the cCamera pointer in this object to use the camera passed in the constructor.
	mpCamera=lpCamera;

    //Create a Color object to be passed to various objects as this ship is created.
   cRGBA lfColor(1.0f,1.0f,1.0f,1.0f);

    //Create a cModel to be this ships hull.
    //It has UV co-ordinates and a texture so use the shader TexturingProgram (This was loaded in the IMF Files in cCore)
    //Give it a Mesh and a Texture. (These were loaded in the IMF Files in cCore).
	mpHull = _CREATE(cModel);
	mpHull->Shader("TexturingProgram");
	mpHull->Mesh("PlayerShip");
	mpHull->AddTexture("PlayerShipTexture");
	mpHull->Advance(0.0f,0.0f,lfDistance);
	mpHull->RotateY(WT_PI);

	mcPlayerTarget.SetTarget(mpHull);

    //Create a Collision Object to detect Collisions with the ships hull.
    //Give it a Compound Collision object (made of several other collision objects) called "PlayerShipCollision" from an IMF File.
    //Set the Collison Filter, so only objects which care about colliding with the player ship will check collisions (This is a major speed optimisation)
	mpHullColl = _CREATE(cCollisionObject(mpHull,this));
	//mpHullColl->SetType(_GET_COMPOUND_COLLISION_FILE("PlayerShipCollision"));
	mpHullColl->SetType(1.0f);
	mpHullColl->CollisionFilter(PLAYER_SHIP_FILTER);

    /*Create 8 cPlayerShield Objects to be the player ships shields.
        Each takes several arguments:
            Object to Follow (mpHull)
            Mesh For Shield (_GET_MESH_FILE("ShieldLUFMesh"))
            Collision Mesh for Shield (_GET_COLLISION_MESH_FILE("ShieldLUFCollision"))
            The Collision Filter to use (_PLAYER_SHIELD_FILTER)
            A 4 float colour to use for the shield (cRGBA(0.0f,0.0f,0.8f,0.4f))
            Co-ordinates for the Shield Display (UPPER_SHIELD_DISPLAY_X and UPPER_SHIELD_DISPLAY_Y)
            Shield Status Display Size (SHIELD_DISPLAY_SIZE)
            Texture for shield Display (_GET_TEXTURE_FILE("PlayerShieldOutlineTL"))
        The 8 shields should entirely cover the ship, but they are not entirely perfect along the boundaries.
    */
    mpShields[0]=_CREATE(cPlayerShield(mpHull,"PlayerShieldLUFMesh","PlayerShieldLUFColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,UPPER_SHIELD_DISPLAY_X,UPPER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineTL")));
    mpShields[1]=_CREATE(cPlayerShield(mpHull,"PlayerShieldLURMesh","PlayerShieldLURColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,UPPER_SHIELD_DISPLAY_X,UPPER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineLL")));
    mpShields[2]=_CREATE(cPlayerShield(mpHull,"PlayerShieldRURMesh","PlayerShieldRURColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,UPPER_SHIELD_DISPLAY_X,UPPER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineLR")));
    mpShields[3]=_CREATE(cPlayerShield(mpHull,"PlayerShieldRUFMesh","PlayerShieldRUFColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,UPPER_SHIELD_DISPLAY_X,UPPER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineTR")));
    mpShields[4]=_CREATE(cPlayerShield(mpHull,"PlayerShieldLLFMesh","PlayerShieldLLFColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,LOWER_SHIELD_DISPLAY_X,LOWER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineTL")));
    mpShields[5]=_CREATE(cPlayerShield(mpHull,"PlayerShieldLLRMesh","PlayerShieldLLRColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,LOWER_SHIELD_DISPLAY_X,LOWER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineLL")));
    mpShields[6]=_CREATE(cPlayerShield(mpHull,"PlayerShieldRLRMesh","PlayerShieldRLRColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,LOWER_SHIELD_DISPLAY_X,LOWER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineLR")));
    mpShields[7]=_CREATE(cPlayerShield(mpHull,"PlayerShieldRLFMesh","PlayerShieldRLFColl",PLAYER_SHIELD_FILTER,cRGBA(0.0f,0.0f,0.8f,0.2f),PLAYER_SHIELD_RECHARGE,PLAYER_SHIELD_MAX,PLAYER_SHIELD_DELAY,LOWER_SHIELD_DISPLAY_X,LOWER_SHIELD_DISPLAY_Y,SHIELD_DISPLAY_SIZE,_GET_TEXTURE_FILE("PlayerShieldOutlineTR")));

    //Create a Dial Boundary. Use a different pointer as this will not be modified once created.
    //This is technically bad as it means the process cannot kill this object when it is destroyed.
    //Since this object is only required to be destroyed at the end of the program it doesn't notice.
    //Set a shader for it.
    //Set a texture for it (Image)
    //Set a Position and Size
	mpTargetReticule=_CREATE(cImage(gp2DCamera));
	mpTargetReticule->Shader("Image2DProgram");
	mpTargetReticule->AddTexture("DialBoundary");
	mpTargetReticule->Width(SLIDE_DIAL_SIZE);
	mpTargetReticule->Height(SLIDE_DIAL_SIZE);
	mpTargetReticule->Position(SLIDE_DIAL_X,SLIDE_DIAL_Y);


    //Prepare a Color for the Ships Slide Dial Indicator.
    mfMomentumColor[0]=1.0f;
    mfMomentumColor[1]=0.0f;
    mfMomentumColor[2]=0.0f;
    mfMomentumColor[3]=0.6f;

    //Create a Beam Mesh object, with radius 5 and length 40.
    //This will be rendered with the 2D Camera.
    //The shader will render it in camera space (relative the cameras position and orientation)
    //This means it is a 3D object rendered in orthoganol space
    //With its position measured in pixels.
    //The Shader Variable "ModelColor" is set to update automatically to be the same as teh data mfMomentumColor.
    //SetVariablePointer means it automatically updates.
    //To use the values currently in mfMomentumColor use the function SetVariable()
    lpZDisp=_CREATE(cBeam(5.0f,40.0f,12,gp2DCamera));
    lpZDisp->Shader("GlobalOrthoganolUniformColorProgram");
    lpZDisp->SetVariablePointer("ModelColor",cRGBA(1.0f,0.0f,0.0f,0.6f).Color());
    lpZDisp->Position(SLIDE_DIAL_X,SLIDE_DIAL_Y,-200.0f);

    mcBeamDamage.miType=DAMAGE_TYPE_CONTINUOUS;
    mcBulletDamage.miType=DAMAGE_TYPE_INSTANTANEOUS;
    mcBulletDamage.mfDamage=gcPlannedSettings.mcPlayerGun.mfDamage;
    mfBulletReloadTime=gcPlannedSettings.mcPlayerGun.mfReloadTime;

    //Create an Instance of a cMomentum object to track the momentum of the ship.
    //This is 6 axis momentum - X,Y,Z and X Rotation, Y Rotation and Z Rotation.
	lpMomentum=_CREATE(cMomentumFRI(mpHull));




   //Create an image to display the ships health.
    //As before, give it a shader a texture and set shader variables.
    //This shader is special, it will render the image in the color specified.
    mpHealthDisplay=_CREATE(cImage(gp2DCamera));
    mpHealthDisplay->Shader("Image2DUniformColorProgram");
    mpHealthDisplay->AddTexture("PlayerShipOutline");
    mpHealthDisplay->SetVariablePointer("UniformColor",mcHealthColor.Color());
    //Also set the position and size of the image.
    mpHealthDisplay->Position(PLAYER_HEALTH_DISPLAY_X,PLAYER_HEALTH_DISPLAY_Y);
    mpHealthDisplay->Width(PLAYER_HEALTH_DISPLAY_SIZE);
    mpHealthDisplay->Height(PLAYER_HEALTH_DISPLAY_SIZE);

    //Also make it a trasparent object so it will blend with objects behind it.
    mpHealthDisplay->Transparency(6);

    //Initialise the Color variable mcBeamColor
    mcBeamColor=cRGBA(1.0f,0.0f,0.0f,0.6f);

    //Create an image for displaying the charge in the ships beam cannon.
    //As before, give it a shader a texture and set shader variables.
    //This shader is special, it will render the image in the color specified.
    mpCannonDisplay=_CREATE(cImage(gp2DCamera));
    mpCannonDisplay->Shader("Image2DUniformColorProgram");
    mpCannonDisplay->AddTexture("PlayerShipCannonOutline");
    mpCannonDisplay->SetVariablePointer("UniformColor",mcBeamColor.Color());
    //Also set the position and size of the image.
    mpCannonDisplay->Position(PLAYER_HEALTH_DISPLAY_X,PLAYER_HEALTH_DISPLAY_Y);
    mpCannonDisplay->Width(PLAYER_HEALTH_DISPLAY_SIZE);
    mpCannonDisplay->Height(PLAYER_HEALTH_DISPLAY_SIZE);
    //Also make it a trasparent object so it will blend with objects behind it.
    mpCannonDisplay->Transparency(7);


    //Create an object to display the ships beam weapon.
    //Make it a cBeam of radius 0.3 and length 1000 with 12 segments.
    //As before give it a shader and set the shader variables.
	mpBeamWeapon=_CREATE(cBeam(PLAYER_BEAM_WIDTH,PLAYER_BEAM_LENGTH,BEAM_SEGMENTS));
	mpBeamWeapon->Shader("SetUniformColorProgram");
	mpBeamWeapon->SetVariablePointer("ModelColor",mcBeamColor.Color());
	//Make this object transparent.
	mpBeamWeapon->Transparency(1);


    //Create a Collision Object for detecting collisions with the beam weapon.
    //Again give it a collision filter so only objects interested in colliding with the beam will check it for collisions.
	mpBeamColl=_CREATE(cCollisionObject(mpBeamWeapon,this));
	mpBeamColl->SetType(mpBeamWeapon);
	mpBeamColl->CollisionFilter(PLAYER_BULLET_FILTER);

	//Give the ship a small initial thrust to get it moving.
	mfThrust=0.2f;

	//Adjust the color lfColor to be white (Red was already 1.0f)
	lfColor[1]=1.0f;
	lfColor[2]=1.0f;

    //Create some Text to display the ships current thrust
	mpThrust=_CREATE(cText(gp2DCamera));
	mpThrust->Shader("TextProgram");
	mpThrust->SetVariable("TextColor",lfColor.Color());
	//Fonts are a special type of texture compiled from Font files.
	mpThrust->AddFont("SFGothican");
	//Give it a size and position.
	mpThrust->Size(40.0f);
	mpThrust->Position(20.0f,_WINDOW->RenderAreaHeight()-450.0f);
	//Finally give teh cText object some text to render.
    mpThrust->Text("Thrust : ");
    mpThrust->Add(mfThrust);

    //Create a Viewport in the top right of the screen.
    //Make it proportional to the Screen Size.
    //Set the area for it to cover.
	mpViewport=new cViewport(mpCamera);
	mpViewport->Proportional(true);
	mpViewport->ViewportProportional(0.4f,0.4f,0.2f,0.2f);
	//Set the rendering range for the view port.
	//Make it highly zoomed (dependant on ratio of Near and Width / Height)
	//Update the Viewport with these rendering properties.
	mpViewport->Far(PLAYER_VIEWPORT_FAR);
	mpViewport->Near(PLAYER_VIEWPORT_NEAR);
	mpViewport->Width(PLAYER_VIEWPORT_WIDTH);
	mpViewport->Height(PLAYER_VIEWPORT_HEIGHT);
	mpViewport->UpdateProjectionMatrix();
	//Make the Clear Color slightly green
	mpViewport->ClearColor(0.0f,0.05f,0.0f);
	//Position the viewports 'camera' 5 units in front of the ships hull (mpHull)
	//mpViewport->Follow(mpHull,-5.0f);
	_SLEEP(mpViewport);
	mcZoomToggle.SetState(false);

	//This is a boolean variable so that the system will re target once for each press of the targeting key.
	TargetingToggle=false;

    //Set the ships health to be the max value.
	Life=PLAYER_MAX_HEALTH;
	//Set the Initial Color for the ships health (Green).
	mcHealthColor=cRGBA(0.0f,1.0f,0.0f,1.0f);

    //Create a border for the Zoomed Viewport.
    //Set it to use the 2D camera.
    //Set a 2D Image Shader.
    //Add a Texture (this shader only uses one texture).
    //Set the Width and Height to fit in the top right corner.

	mpViewportBorder=_CREATE(cImage(gp2DCamera));
	mpViewportBorder->Shader("Image2DProgram");
	mpViewportBorder->AddTexture("ScreenBorder");
	mpViewportBorder->Width(_WINDOW->RenderAreaWidth()*0.2);
	mpViewportBorder->Height(_WINDOW->RenderAreaHeight()*0.2);
	mpViewportBorder->Position(_WINDOW->RenderAreaWidth()*0.5,_WINDOW->RenderAreaHeight()*0.5);
	_SLEEP(mpViewportBorder);

	cImage *lpImage;
    //Create a Main screen Targeting Reticule.
    //Set it to use the 2D camera.
    //Set a 2D Image Shader.
    //Add a Texture (this shader only uses one texture).
    //Set the Width and Height to fit in the top right corner.
	lpImage=_CREATE(cImage(gp2DCamera));
	lpImage->Shader("Image2DProgram");
	lpImage->AddTexture("Reticule");
	lpImage->Width(31);
	lpImage->Height(31);
	lpImage->Position(SHIP_TARGET_RETICULE_X,SHIP_TARGET_RETICULE_Y);

    //Create a Reticule to track the targeted enemy
    //As usual, Shader, Texture and Size.
    //Positioning will be handled once a target is acquired
	mpTargetReticule=_CREATE(cImage(gp2DCamera));
	mpTargetReticule->Shader("Image2DProgram");
	mpTargetReticule->AddTexture("TrackingReticule");
	mpTargetReticule->Width(31);
	mpTargetReticule->Height(31);


	mpTargetDistance=_CREATE(cText(gp2DCamera));
	mpTargetDistance->Shader("TextProgram");
	mpTargetDistance->AddFont("Pirulen");
	mpTargetDistance->Size(15.0f);
	mpTargetDistance->SetUniform("TextColor",cRGBA(1.0f,1.0f,1.0f,1.0f).Color());


	mfReload=0.0f;

	mpFollowShip=_CREATE(cPoint);
	mpFollowShip->Shader("DiscardProgram");
	mpFollowShip->Equals(mpHull);

	mpWholeCollision=_CREATE(cCollisionObject(mpFollowShip,this));
	mpWholeCollision->SetType(1.0f);
	mpWholeCollision->CollisionFilter(PLAYER_WHOLE_CHECK);

	mpMissileSettings=PrepMissileSettings();
/*
    cMissileSettings *lpBaseMissile=new cMissileSettings(mpHull->ThisMatrixPointer(),"TLevTurretBarrelMesh","TLevTexture",c3DVf(0.0f,-0.5f,1.0f),0,ENEMY_SHIP_FILTER,15.0f,5.0f,0.003f,3000.0f,100.0f,300.0f,lpMomentum);
    mpMissileSettings[MISSILE_TYPE_EXPLOSIVE]=new cExplosiveMissileSettings(lpBaseMissile,300.0f,500.0f);
    mpMissileSettings[MISSILE_TYPE_EMP]=new cEMPMissileSettings(lpBaseMissile,300.0f);
    mpMissileSettings[MISSILE_TYPE_LASER]=new cLaserMissileSettings(lpBaseMissile,300.0f,1000.0f);
    mpMissileSettings[MISSILE_TYPE_CHAFF]=new cChaffSettings(mpHull->ThisMatrixPointer(),30,0.03f,30,5.0f,cRGBA(1.0f,1.0f,0.0f,0.8f));
*/

    miMissileSlots[0]=MISSILE_TYPE_EXPLOSIVE;
    miMissileSlots[1]=MISSILE_TYPE_EXPLOSIVE;

    /*miMissileSlots[3]=MISSILE_TYPE_LASER;
    miMissileSlots[4]=MISSILE_TYPE_LASER;
    miMissileSlots[5]=MISSILE_TYPE_LASER;
    miMissileSlots[6]=MISSILE_TYPE_EMP;
    miMissileSlots[7]=MISSILE_TYPE_EMP;
    miMissileSlots[8]=MISSILE_TYPE_EMP;*/


    mpMissileRack=_CREATE(cImage(gp2DCamera));
    mpMissileRack->Shader("Image2DUniformColorProgram");
    mpMissileRack->AddTexture("MissileRack");
    mpMissileRack->SetUniform("UniformColor",cRGBA(1.0f,1.0f,1.0f,0.3f).Color());
    mpMissileRack->PositionX(SHIP_MISSILE_RACK_X);
    mpMissileRack->PositionY(SHIP_MISSILE_RACK_Y);
    mpMissileRack->Width(SHIP_MISSILE_RACK_SIZE);
    mpMissileRack->Height(SHIP_MISSILE_RACK_SIZE);
    mpMissileRack->Transparency(4);


    for(uint8 liMissile=0;liMissile<MISSILE_SLOTS;++liMissile)
    {
        //miMissileSlots[liMissile]=(uint32)(RANDOM_NUMBER*MISSILE_TYPES)%MISSILE_TYPES;
        miMissileSlots[liMissile]=gcPlannedSettings.mpMissileSlots[liMissile];
        mpMissileSlots[liMissile]=_CREATE(cImage(gp2DCamera));
        mpMissileSlots[liMissile]->Shader("Image2DUniformColorProgram");
        switch(miMissileSlots[liMissile])
        {
            case MISSILE_TYPE_EXPLOSIVE :{mpMissileSlots[liMissile]->AddTexture("EXMissileID");}break;
            case MISSILE_TYPE_LASER :{mpMissileSlots[liMissile]->AddTexture("LSMissileID");}break;
            case MISSILE_TYPE_EMP:{mpMissileSlots[liMissile]->AddTexture("SDMissileID");}break;
            case MISSILE_TYPE_CHAFF :{mpMissileSlots[liMissile]->AddTexture("CHMissileID");}break;
            case MISSILE_TYPE_MW :{mpMissileSlots[liMissile]->AddTexture("MWMissileID");}break;
            default : {mpMissileSlots[liMissile]->AddTexture("MWMissileID");}
        }
        mpMissileSlots[liMissile]->Width(SHIP_MISSIlE_SLOT_SIZE);
        mpMissileSlots[liMissile]->Height(SHIP_MISSIlE_SLOT_SIZE);
        mpMissileSlots[liMissile]->SetUniformPointer("UniformColor",cPlanningMissileRack::msMissileColors[miMissileSlots[liMissile]].Color());
        mpMissileSlots[liMissile]->Transparency(5);
    }


    mfRackDisplayTimer=12.0f;


    miMissileSelected=0;
    mfMissileReload=0.0f;
	mbMissileSelectToggle=false;
    UpdateMissileRackDisplay();



	mpBeamSound=_CREATE(cAudioObject);
	mpBeamSound->Buffer("LasCannonSound");
	//mpBeamSound->Buffer("CannonShotSound");
	mpBeamSound->Gain(0.5f);
	mpBeamSound->Pitch(0.5f);
	mpBeamSound->Loop(0);
    mpGunShotSound=_CREATE(cAudioObject);
    mpGunShotSound->Buffer("CannonShotSound");
	mpJetSound=_CREATE(cAudioObject);
	mpJetSound->Buffer("JetTurbineSound");
	mpJetSound->Gain(mfThrust/THRUST_LIMIT);
	mpJetSound->Pitch(4*mfThrust/THRUST_LIMIT);
	mpJetSound->Loop(1);
	    if(gbSoundOn)
		{
			mpJetSound->Play();
		}

	mpHullSound=_CREATE(cAudioObject);
	mpHullSound->Buffer("HullHitSound");


	miHullSoundDelay=0;

	mpTargetStatus=new cCombatStatusBox;


    mpSlideIcon=_GET_TEXTURE_FILE("SlideIcon");
	mpBrakeIcon=_GET_TEXTURE_FILE("BrakeIcon");

	mpMoveIcon=_CREATE(cImage(gp2DCamera));
	mpMoveIcon->Shader("Image2DProgram");
	mpMoveIcon->AddTexture(mpBrakeIcon);
	mpMoveIcon->Width(PLAYER_MOVE_ICON_WIDTH);
	mpMoveIcon->Height(PLAYER_MOVE_ICON_HEIGHT);
	mpMoveIcon->Position(PLAYER_MOVE_ICON_X,PLAYER_MOVE_ICON_Y);
    mpMoveIcon->Transparency(3);
    _SLEEP(mpMoveIcon);

	miThrustChangeRate=0;

}

void cPlayer::Run()
{
/*
	//Control Targeting enemy fighters.
	//If cPlayer is not targeting an enemy try to find one.
	if(!mpTarget)
	{
        //Search the cKernel for any cProcess objects of type cFighter.
		_KERNEL->ResetFindProcess();
		mpTarget=_FIND_PROCESS(PLAYER_TARGETING_TYPE);
	}
*/
    //TargetingToggle being true means that last frame the TargetingKey was pressed.
    if(TargetingToggle)
    {
        //If the Targeting Key was not pressed turn the toggle off (the next detected press will toggle the targeting)
         if(!TARGETING_INPUT) TargetingToggle=false;
    }
    else
    {
        //If the toggle is not on, then a detected key press will try to change the target
        if(TARGETING_INPUT)
        {
            //If one is not found, the previous one was the last in the list.
            if(!mcTargeting.Targeted())
            {
                PLAYER_TARGETING_TYPE *lpTarg;
                //Start the search from the beginning.
                _KERNEL->ResetFindProcess();
                lpTarg=_FIND_PROCESS(PLAYER_TARGETING_TYPE);
                while(dynamic_cast<cLeviathanHull*>(lpTarg) || dynamic_cast<cLeviathanMultiHull*>(lpTarg))
                {
                    lpTarg=_FIND_PROCESS_START(PLAYER_TARGETING_TYPE,lpTarg);
                }
                mcTargeting.SetTarget(lpTarg);
            }
            else
            {
             //Search for another cProcess Obnject of type cFighter
             PLAYER_TARGETING_TYPE *lpTarg=_FIND_PROCESS_START(PLAYER_TARGETING_TYPE,mcTargeting.mpComponent);
                while(dynamic_cast<cLeviathanHull*>(lpTarg) || dynamic_cast<cLeviathanMultiHull*>(lpTarg))
                {
                    lpTarg=_FIND_PROCESS_START(PLAYER_TARGETING_TYPE,lpTarg);
                }
                mcTargeting.SetTarget(lpTarg);

            }
            if(mcTargeting.Targeted())
            {
                NewTarget(mcTargeting);
            }

            TargetingToggle=true;
        }
    }

    if(KEY_F1 && gcGameSettings.mcTargets[0].Targeted()){NewTarget(gcGameSettings.mcTargets[0]);}
    if(KEY_F2 && gcGameSettings.mcTargets[1].Targeted()){NewTarget(gcGameSettings.mcTargets[1]);}
    if(KEY_F3 && gcGameSettings.mcTargets[2].Targeted()){NewTarget(gcGameSettings.mcTargets[2]);}
    if(KEY_F4 && gcGameSettings.mcTargets[3].Targeted()){NewTarget(gcGameSettings.mcTargets[3]);}
    if(KEY_F5 && gcGameSettings.mcTargets[4].Targeted()){NewTarget(gcGameSettings.mcTargets[4]);}
    if(KEY_F6 && gcGameSettings.mcTargets[5].Targeted()){NewTarget(gcGameSettings.mcTargets[5]);}
    if(KEY_F7 && gcGameSettings.mcTargets[6].Targeted()){NewTarget(gcGameSettings.mcTargets[6]);}
    if(KEY_F8 && gcGameSettings.mcTargets[7].Targeted()){NewTarget(gcGameSettings.mcTargets[7]);}
    if(KEY_F9 && gcGameSettings.mcTargets[8].Targeted()){NewTarget(gcGameSettings.mcTargets[8]);}
    if(KEY_F10 && gcGameSettings.mcTargets[9].Targeted()){NewTarget(gcGameSettings.mcTargets[9]);}
    if(KEY_F11 && gcGameSettings.mcTargets[10].Targeted()){NewTarget(gcGameSettings.mcTargets[10]);}
    if(KEY_F12 && gcGameSettings.mcTargets[11].Targeted()){NewTarget(gcGameSettings.mcTargets[11]);}


    //If there is a target update the position of the tracking reticule.
    if(mcTargeting.Targeted())
	{
	    //Get the screen position of the target.
	    c3DVf lfTemp;
	    if(mcZoomToggle.On())
	    {
	        lfTemp=mcTargeting.mpComponent->ComponentNode()->GetScreenPosition(mpViewport);
	    }
	    else
	    {
            lfTemp=mcTargeting.mpComponent->ComponentNode()->GetScreenPosition();
	    }


		if(lfTemp.Z()<0.0f || (lfTemp.X()<0.0f || lfTemp.X()>_WINDOW->RenderAreaWidth() || lfTemp.Y()<0.0f || lfTemp.Y()>_WINDOW->RenderAreaHeight()))
		{
			if(lfTemp.Z()<0.0f)
			{
				lfTemp[0]=-lfTemp[0];
				lfTemp[1]=-lfTemp[1];

			}
		 c3DVf lfOther((float)_WINDOW->RenderAreaWidth()*0.5f,(float)_WINDOW->RenderAreaHeight()*0.5f,0.0f);
		 lfTemp-=lfOther;

		float lfAngle=atan2(lfTemp[0],lfTemp[1]);

		float lfRange=_WINDOW->RenderAreaWidth()+_WINDOW->RenderAreaHeight();
		lfRange*=0.35f;

		lfTemp[0]=ClampValueRange(sin(lfAngle)*lfRange+_WINDOW->RenderAreaWidth()*0.5f,0.0f,(float)_WINDOW->RenderAreaWidth());
		lfTemp[1]=ClampValueRange(cos(lfAngle)*lfRange+_WINDOW->RenderAreaHeight()*0.5f,0.0f,(float)_WINDOW->RenderAreaHeight());

		}

			mpTargetReticule->Position(lfTemp.X(),lfTemp.Y());
			mpTargetDistance->Text("Dist: ");
			double ldValue=mcTargeting.mpComponent->ComponentNode()->Distance(mpHull);
			mpTargetDistance->Add(ldValue,0);
			if(lfTemp.Y()>gpWindow->RenderAreaHeight()) mpTargetDistance->Position(lfTemp.X()-75.0f,lfTemp.Y()-30.0f);
			else mpTargetDistance->Position(lfTemp.X()-75.0f,lfTemp.Y()+30.0f);
	}
	else
	{
	    //If there is no target, sleep the targetting reticule so it does not appear.
	    	    _SLEEP(mpTargetReticule);
	    	    _SLEEP(mpTargetDistance);
	}

    mpTargetStatus->Display();

    if(MISSILE_LAUNCH_KEY && mfMissileReload<=0.0f && miMissileSlots[miMissileSelected]!=MISSILE_TYPE_EMPTY)
     {
        if(mcTargeting.Targeted() || miMissileSlots[miMissileSelected]==MISSILE_TYPE_CHAFF)
        {
            switch(miMissileSlots[miMissileSelected])
            {
                case MISSILE_TYPE_EXPLOSIVE:
                {
                    mpMissileSettings[MISSILE_TYPE_EXPLOSIVE]->mpTarget=mcTargeting;
                  _CREATE(cExplosiveMissile(dynamic_cast<cExplosiveMissileSettings*>(mpMissileSettings[MISSILE_TYPE_EXPLOSIVE])));
                }break;
                case MISSILE_TYPE_LASER:
                {
                   mpMissileSettings[MISSILE_TYPE_LASER]->mpTarget=mcTargeting;
                  _CREATE(cLaserMissile(dynamic_cast<cLaserMissileSettings*>(mpMissileSettings[MISSILE_TYPE_LASER])));
                }break;
                case MISSILE_TYPE_EMP:
                {
                  mpMissileSettings[MISSILE_TYPE_EMP]->mpTarget=mcTargeting;
                  _CREATE(cEMPMissile(dynamic_cast<cEMPMissileSettings*>(mpMissileSettings[MISSILE_TYPE_EMP])));
                }break;
                case MISSILE_TYPE_CHAFF:
                {
                  cChaffCharge::ActivateChaff(dynamic_cast<cChaffSettings*>(mpMissileSettings[MISSILE_TYPE_CHAFF]));
                }break;
                case MISSILE_TYPE_MW:
                {
                    mpMissileSettings[MISSILE_TYPE_MW]->mpTarget=mcTargeting;
                  _CREATE(cMWMissileScatter(dynamic_cast<cMWMissileSettings*>(mpMissileSettings[MISSILE_TYPE_MW])));
                }break;
            };
            miMissileSlots[miMissileSelected]=MISSILE_TYPE_EMPTY;
            mpMissileSlots[miMissileSelected]->SetUniformPointer("UniformColor",cPlanningMissileRack::msMissileColors[MISSILE_TYPE_EMPTY].Color());
            NextMissileType();
            UpdateMissileRackDisplay();
            mfMissileReload=PLAYER_MISSILE_RELOAD_TIME;
            DisplayMissileRack(12.0f);
        }
     }


	if(mfMissileReload>0.0f) mfMissileReload-=0.4f*_TIME_PER_FRAME;

    if(mfRackDisplayTimer>=0.0f)
    {
        mfRackDisplayTimer-=0.4f*_TIME_PER_FRAME;
        if(mfRackDisplayTimer<=0.0f)
        {
            _SLEEP(mpMissileRack);
            for(uint8 liMissile=0;liMissile<MISSILE_SLOTS;++liMissile)
            {
                _SLEEP(mpMissileSlots[liMissile]);
            }
        }
    }

    if(DISPLAY_MISSILE_RACK)
    {
        DisplayMissileRack(12.0f);
    }


//Determine whether Mouse Y Axis Updates Ships Thrust or Ships Pitch (Angular Momentum)
if(!cUserSettings::mbKeyThrustControl)
{
	if(THRUST_CHANGE_INPUT)
	{
	    //If the Thrust input is true then Mouse movements will update the ships thrust.
		mfThrust-=_MOUSE->YSpeed()*cUserSettings::mfMouseThrustSensitivity*_TIME_PER_FRAME;

		//Limit the ships thrust to the defined thrust range
		mfThrust=ClampValueRange(mfThrust,0.0f,THRUST_LIMIT);

		//Update the text displaying the ships thrust.
        mpThrust->Text("Thrust : ");
        mpThrust->Add(mfThrust);
        if(gbSoundOn)
        {
            mpJetSound->Gain(mfThrust/THRUST_LIMIT);
            mpJetSound->Pitch(4*mfThrust/THRUST_LIMIT);
        }
	}
	else
    {
	    if(cUserSettings::mbYawPitchControls)
	    {
            //If thrust input is not true then:
            //Update Ships Pitch (Angular Momentum) based off mouse movement
            lpMomentum->ThrustAngleX(_MOUSE->YSpeed()*cUserSettings::mfMouseYAngleSensitivity);
            lpMomentum->ThrustAngleY(_MOUSE->XSpeed()*cUserSettings::mfMouseXAngleSensitivity);
	    }
	    else
	    {

            //If thrust input is not true then:
            //Update Ships Pitch (Angular Momentum) based off mouse movement
            lpMomentum->ThrustAngleX(_MOUSE->YSpeed()*cUserSettings::mfMouseYAngleSensitivity);
            lpMomentum->ThrustAngleZ(_MOUSE->XSpeed()*cUserSettings::mfMouseXAngleSensitivity);
	    }
	}
}
else
{

	bool lbThrustChange=false;
	if(KEY_1 || KEY_NP1){mfThrust=0.1*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_2 || KEY_NP2){mfThrust=0.2*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_3 || KEY_NP3){mfThrust=0.3*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_4 || KEY_NP4){mfThrust=0.4*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_5 || KEY_NP5){mfThrust=0.5*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_6 || KEY_NP6){mfThrust=0.6*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_7 || KEY_NP7){mfThrust=0.7*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_8 || KEY_NP8){mfThrust=0.8*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_9 || KEY_NP9){mfThrust=0.9*THRUST_LIMIT; lbThrustChange=true;}
	if(KEY_0 || KEY_NP0){mfThrust=THRUST_LIMIT; lbThrustChange=true;}
	if(miThrustChangeRate)
	{
	    --miThrustChangeRate;
	}
	else
	{
	    if((KEY_SBC || KEY_NP_PLUS)){mfThrust+=0.1*THRUST_LIMIT; lbThrustChange=true; miThrustChangeRate=THRUST_CHANGE_DELAY;}
        if((KEY_SBO || KEY_NP_SUBTRACT)){mfThrust-=0.1*THRUST_LIMIT; lbThrustChange=true; miThrustChangeRate=THRUST_CHANGE_DELAY;}
	}
	if(lbThrustChange==true)
	{
	    mfThrust=ClampValueRange(mfThrust,0.0f,THRUST_LIMIT);
        mpThrust->Text("Thrust : ");
        mpThrust->Add(mfThrust);
        if(gbSoundOn)
        {
            mpJetSound->Gain(mfThrust/THRUST_LIMIT);
            mpJetSound->Pitch(4*mfThrust/THRUST_LIMIT);
        }
	}

    if(cUserSettings::mbYawPitchControls)
    {
        //If thrust input is not true then:
        //Update Ships Pitch (Angular Momentum) based off mouse movement
        lpMomentum->ThrustAngleX(_MOUSE->YSpeed()*cUserSettings::mfMouseYAngleSensitivity);
        lpMomentum->ThrustAngleZ(_MOUSE->XSpeed()*cUserSettings::mfMouseXAngleSensitivity);
    }
    else
    {
        //If thrust input is not true then:
        //Update Ships Pitch (Angular Momentum) based off mouse movement
        lpMomentum->ThrustAngleX(_MOUSE->YSpeed()*cUserSettings::mfMouseYAngleSensitivity);
        lpMomentum->ThrustAngleZ(_MOUSE->XSpeed()*cUserSettings::mfMouseXAngleSensitivity);
    }
}

    if(TOGGLE_MISSILE_SELECTED)
    {
        if(!mbMissileSelectToggle)
        {
            NextMissileType();
            UpdateMissileRackDisplay();
            DisplayMissileRack(12.0f);
        }
        mbMissileSelectToggle=true;

    }
    else
    {
     mbMissileSelectToggle=false;
    }




//Update Up / Down Slide thrust
if(SLIDE_UP_INPUT || SLIDE_DOWN_INPUT)
{
	//If Up Input is pressed
	if(SLIDE_UP_INPUT)
	{
		//Check for double tap. If so do instantaneous thrust up.
		if(mfDodgeY<KEY_TAP_TIME && mfDodgeY>0.1f) lpMomentum->ThrustY(INST_THRUST);
		//Apply Continuous Thrust
		lpMomentum->LimitedThrustY(NON_DIRECT_THRUST,SLIDE_SPEED_LIMIT);
		//Reset the mfDodgeY counter
		mfDodgeY=0.0f;
	}
    //If the down input is pressed
	if(SLIDE_DOWN_INPUT)
	{
		//Check for double tap. If so do instantaneous thrust down
		if(mfDodgeY<KEY_TAP_TIME && mfDodgeY>0.1f) lpMomentum->ThrustY(-INST_THRUST);
		//Apply Continuous Thrust
		lpMomentum->LimitedThrustY(-NON_DIRECT_THRUST,SLIDE_SPEED_LIMIT);
		//Reset the mfDodgeY counter
		mfDodgeY=0.0f;
	}
}
else
{
	//If Up / Down keys are not pressed update double tap timer
	mfDodgeY+=0.01f;
	//If the activate Slide key is not pressed, slow slide movement.
	if(!SLIDE_KEY_INPUT) lpMomentum->StraightenY(STRAIGHTEN_THRUST);
}

//Check if the slide left / right keys are pressed.
if(SLIDE_LEFT_INPUT || SLIDE_RIGHT_INPUT)
{
    //If the left slide input is true slide the ship left
	if(SLIDE_LEFT_INPUT)
	{
	    //If the mfDodgeX counter is short enough since the last press do a Instantaneous burst of thrust.
		if(mfDodgeX<KEY_TAP_TIME && mfDodgeX>0.1f) lpMomentum->ThrustX(-INST_THRUST);
		//Sincethe left slide input is true thrust the ship left.
		lpMomentum->LimitedThrustX(-NON_DIRECT_THRUST,SLIDE_SPEED_LIMIT);
		//Reset the mfDodgeX Timer
		mfDodgeX=0.0f;
	}
    //If the right slide input is pressed, slide the ship right.
	if(SLIDE_RIGHT_INPUT)
	{
		if(mfDodgeX<KEY_TAP_TIME && mfDodgeX>0.1f) lpMomentum->ThrustX(INST_THRUST);
	//	lpMomentum->LimitedThrustX(_NON_DIRECT_THRUST,_SPEED_LIMIT);
		lpMomentum->LimitedThrustX(NON_DIRECT_THRUST,SLIDE_SPEED_LIMIT);
		mfDodgeX=0.0f;
	}

}
else
{
    //Update the mfDodgeX Counter as the keys have not been pressed.
	mfDodgeX+=0.01f;
	//If the activate Slide key is not pressed, slow slide movement.
	if(!SLIDE_KEY_INPUT) lpMomentum->StraightenX(STRAIGHTEN_THRUST);
}


	if(!SLIDE_KEY_INPUT)
	{
		if(!BRAKE_KEY_INPUT)
		{
            _SLEEP(mpMoveIcon);
            lpMomentum->LimitedThrustZ(mfThrust,SPEED_LIMIT);
		}
		else
		{
            _WAKE(mpMoveIcon);
            mpMoveIcon->ClearTextureStack();
            mpMoveIcon->AddTexture(mpBrakeIcon);
            lpMomentum->StraightenZ(THRUST_LIMIT);
		}
	}
	else
	{
        _WAKE(mpMoveIcon);
        mpMoveIcon->ClearTextureStack();
        mpMoveIcon->AddTexture(mpSlideIcon);
	}


	//Dampen the angular momentum of the ship (to make control easier and less sickness inducing...)
	lpMomentum->DampenAngular(ANGULAR_DAMPENING_FACTOR);
	//Update the ships position based on it's momentum.
	lpMomentum->Update();

    //Note : Z axis is forwards.
    //       Y Axis is up.
    //       X Axis is right.
    //Update the Movement direction dial.
    //Make it the same as the ships momentum Vector.
    //Then rotate this vector based on the ships facing.
    //Finally Set the dial to face in the direction the ship is moving.
    c3DVf lfMomentumVector=c3DVf(lpMomentum->GMomentumVector());
    lfMomentumVector=mpHull->RotateVectorByAngles(lfMomentumVector*_TIME_PER_FRAME);
	lpZDisp->LookVector(lfMomentumVector);

	//Set the color for the Movement direction dial. Green if forwards. Red if backwards.
	if(lfMomentumVector.Z()<0.0f)
	{
		mfMomentumColor[0]=lfMomentumVector.Magnitude()*SLIDE_INDICATOR_MULTIPLIER;
		mfMomentumColor[1]=0.0f;
	}
	else
	{
		mfMomentumColor[0]=0.0f;
		mfMomentumColor[1]=lfMomentumVector.Magnitude()*SLIDE_INDICATOR_MULTIPLIER;
	}

    //Make the Beam weapon equal the ships position.
    //This comes after updating the ships position so it does not tail behind.
	mpBeamWeapon->Equals(mpHull);
	//move the beam forwards so it is not inside the ship.
	mpBeamWeapon->AdvanceZ(PLAYER_BEAM_OFFSET_Z);
	//Move the beam down so it is inline with the ships main cannon.
	mpBeamWeapon->AdvanceY(PLAYER_BEAM_OFFSET_Y);

    //This is a processor expensive function which will recalculate the ships cache matrix.
    //This is so the camera will be following the ships position this frame.
    //(Cameras require global matrices to track)
    mpHull->CalculateGlobalMatrix();

    //Have the Camera and View port follow the ships position and orientation.
    mpCamera->Follow(dynamic_cast<cMatrix4*>(mpHull),0.0f,CAMERA_OFFSET_DISTANCE,CAMERA_FOLLOW_DISTANCE);

	if(mcZoomToggle.UpdateOnToggle(TOGGLE_ZOOM_VIEWPORT))
	{
		if(mcZoomToggle.On())
		{
			_WAKE(mpViewport);
			_WAKE(mpViewportBorder);
		}
		else
		{
			_SLEEP(mpViewportBorder);
			_SLEEP(mpViewport);
		}
	}
	if(mcZoomToggle.On()) mpViewport->Follow(dynamic_cast<cMatrix4*>(mpHull),0.0f,PLAYER_VIEWPORT_OFFSET_Y ,PLAYER_VIEWPORT_OFFSET_Z );

	mpFollowShip->Equals(mpHull);


    cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpWholeCollision,ENEMY_SHIP_FILTER+2);
    if(lpList->NextCollisionItem())
    {

        delete lpList;
        cProcess *lpProc;
        lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,ENEMY_SHIP_FILTER);
        //This will step through all the collisions making lpProc point at the next process.
        for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
        {
            _KILL_THIS();
        }

    }

	delete lpList;

    if(miHullSoundDelay) --miHullSoundDelay;

    //If the player is firing his beam weapon
	if(BEAM_FIRE_INPUT)
	{
	    if(mpBeamWeapon->Asleep())
	    {
            //Wake the Beam so it will collide and is visible.
            _WAKE(mpBeamWeapon);
            if(gbSoundOn) mpBeamSound->Play();

	    }

	     //Set the alpha (transparency) of the beam.
	     //Discharge some ofmpShields[8] the power in the beam by multiplying it by a factor which is slightly less than 1.0f
	     //This is also the beams charge level
	     mcBeamColor.A(mcBeamColor.A()*BEAM_DISCHARGE_RATE);

	         //This will check for collisions
    //lpProc will point at each Collisions owning process.
    //lpList will store the list of detected collisions.
    //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpBeamColl,ENEMY_SHIP_FILTER+2);
	//This will step through all the collisions making lpProc point at the next process.
	if(lpList->NextCollisionItem())
	{
	    delete lpList;
            //This will check for collisions
            //lpProc will point at each Collisions owning process.
            //lpList will store the list of detected collisions.
            //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
            lpList=_COLLISION_HANDLER->GenerateDetailedCollisionList(mpBeamColl,ENEMY_SHIP_FILTER+1);
            _COLLISION_HANDLER->GenerateDetailedCollisionList(mpBeamColl,ENEMY_SHIP_FILTER,lpList);

            lpList->RecalculateDistances();
            lpList->SortByDistance();
            //This will step through all the collisions making lpProc point at the next process.
            lpProc=lpList->NextCollisionP();
            if(lpProc)
            {
                mcBeamDamage.mfPos=lpList->CurrentCollisionDetail()->Centre();
                mcBeamDamage.mfDamage=mcBeamColor.A()*BEAM_DAMAGE_MULTIPLIER*_TIME_PER_FRAME;
                gpRenderCollision=dynamic_cast<cRenderObject*>(lpList->CurrentCollisionR());
                lpProc->UserSignal(BEAM_COLLISION,&mcBeamDamage);
                if(!dynamic_cast<cShield*>(lpProc))
                {
                    GenerateDamageParticles(lpList->CurrentCollisionDetail()->Centre());
                    cModel *lpModel=dynamic_cast<cModel*>(gpRenderCollision);
                    if(lpModel)
                    {
                        c2DVf UVCoords=lpModel->GetUVCoords(lpList->CurrentCollisionDetail()->Centre());
                        if(UVCoords[0]>=0.0f && UVCoords[0]<1.0f && UVCoords[1]>=0.0f && UVCoords[1]<1.0f)
                        {
                                cTexture *lpTex=lpModel->TextureItem(1).mpTexture;
                                if(lpTex)
                                {
                                    //lpTex->Write(cRGB(1.0f,0.0f,0.0f),UVCoords);
                                    lpTex->Blend(_GET_TEXTURE_FILE("HullDamageDecal"),UVCoords);
                                    //lpTex->UpdateTexture();
                                }
                        }
                     }
                }
            }

            delete lpList;
             lpList=_COLLISION_HANDLER->GenerateCollisionList(mpBeamColl,MISSILE_FILTER);
            //This will step through all the collisions making lpProc point at the next process.
            lpProc=lpList->NextCollisionP();
            if(lpProc)
            {
                lpProc->UserSignal(BEAM_COLLISION,0);
            }

    }

    delete lpList;
    }
	else
	{
	    //If the Beam is not being fired.
	    //Sleep it so it will not collide or be visible
	    _SLEEP(mpBeamWeapon);
	    //If the beam is not fully charged recharge the beam.
	    if(mcBeamColor.A()<1.0f)mcBeamColor.A(mcBeamColor.A()+BEAM_RECHARGE_RATE);
    }

    //If the player is firing their machine guns AND the guns are reloaded fire the guns.
    if(BULLETS_FIRE_INPUT && mfReload<0.0f)
    {
        //Create two bullets. Give them offset values.
        //see WTcBullet.h and WTcBullet.cpp
        //No more needs to be done, the bullets will handle themselves after this.
         _CREATE(cBullet(mpHull,c3DVf(0.5f,0.0f,0.0f),PLAYER_BULLET_SPEED,&mcBulletDamage,0,ENEMY_SHIP_FILTER));
         _CREATE(cBullet(mpHull,c3DVf(-0.5f,0.0f,0.0f),PLAYER_BULLET_SPEED,&mcBulletDamage,0,ENEMY_SHIP_FILTER));
        if(gbSoundOn)
		{
             mpGunShotSound->Gain(0.1*RANDOM_NUMBER+0.9f);
             mpGunShotSound->Pitch(0.1*RANDOM_NUMBER+0.9f);
             mpGunShotSound->Play();
		}
         //Set the reload counter so the guns are not loaded
         mfReload=mfBulletReloadTime;
         lpMomentum->ThrustZ(-BULLET_THRUST);
    }
    //Update the reload counter to continue reloading the guns/
    mfReload-=_TIME_PER_FRAME;


    HullMatrix.Equals(mpHull->ThisMatrix());

       cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
        lpPart->SetLife(0.5f+0.5f*RANDOM_NUMBER);
        lpPart->SetSize(1000.0f);
        c3DVf Speed(-mpHull->Zx(),-mpHull->Zy(),-mpHull->Zz());
        Speed=ParticleSideVelocity((Speed*0.01).v,0.3,1.0f);
        lpPart->SetSpeed(Speed.v);
        lpPart->SetPosition(mpHull->Position());
        float lfColor=RANDOM_NUMBER;
        float lpSecond[4]={lfColor,lfColor,lfColor,SMOKE_TRANSPARENCY};
        lpPart->SetColor(lpSecond);

}

//This is a function to allow other processes to send signals to this object.
bool cPlayer::UserSignal(SIGNAL lsSignal,void* lpData)
{
 //Check the type of signal.
 switch (lsSignal)
 {
     //Signal to tell the ship that a fighter is dead and a new target must be sought.
	 case DEAD_FIGHTER:
	 {
	     mcTargeting.CheckDeath((PLAYER_TARGETING_TYPE*)lpData);
	     gcGameSettings.CheckDeath((PLAYER_TARGETING_TYPE*)lpData);
		return 1;
	 }

    //This is a signal to say that the ship should take damage.
	 case BEAM_COLLISION:
	 {

	     float *lpPosition=((float*)lpData);
	     ++lpPosition;
	     //Find out how much damage
	     float Yaw=mpHull->mmCache.YawToVector(lpPosition);
	     int16 miShield=(int)(Yaw/DEGREES_TO_RADIANS(90));
	     if(Yaw<0.0f) --miShield;
	     if(miShield<0) {miShield+=4;};
	     if(mpHull->mmCache.PitchToVector(lpPosition)>0.0f) miShield+=4;
	     if(mpShields[miShield]->Health()>0.0f)
	     {
	         mpShields[miShield]->UserSignal(BEAM_COLLISION,lpData);
	     }
	     else
	     {
    if(gbSoundOn)
	{
	     if(!miHullSoundDelay)
	     {
	     	 mpHullSound->Gain(0.1f*RANDOM_NUMBER+0.8f);
	         mpHullSound->Pitch(0.4f*RANDOM_NUMBER+0.3f);
	         mpHullSound->Play();
	         miHullSoundDelay=(1.0+RANDOM_NUMBER*0.2)*HULL_SOUND_DELAY;
	     }
	}
             GenerateDamageParticles(mpHull->mmCache.Position(),3);
             //Reduce our ships health by the amount of damage.
             Life-=((cDamage*)lpData)->mfDamage;
             //Update the ships health display color.
             //This will make the stages be:
             //           Full health : 0.0f,1.0f,0.0f,1.0f
             //           Half health : 0.5f,0.5f,0.0f,1.0f
             //           Full health : 1.0f,0.0f,0.0f,1.0f
             // This makes a nice progression from green to red though orange
             mcHealthColor=cRGBA(1.0f-PLAYER_HEALTH_SCALE*Life,PLAYER_HEALTH_SCALE*Life,0.0f,1.0f);
             if(Life<0.0f) _KILL_THIS();
	     }
	     return 1;
	 }

	 case EXPLOSION_COLLISION:
	 {
	     if(!miHullSoundDelay)
	     {
            if(gbSoundOn)
			{
	     	 mpHullSound->Gain(0.1f*RANDOM_NUMBER+0.8f);
	         mpHullSound->Pitch(0.4f*RANDOM_NUMBER+0.3f);
	         mpHullSound->Play();
	         miHullSoundDelay=(1.0+RANDOM_NUMBER*0.2)*HULL_SOUND_DELAY;
			}
	     }
            mpShields[0]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[1]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[2]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[3]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[4]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[5]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[6]->UserSignal(BEAM_COLLISION,lpData);
            mpShields[7]->UserSignal(BEAM_COLLISION,lpData);

             //Reduce our ships health by the amount of damage.
             Life-=((cDamage*)lpData)->mfDamage;
             //Update the ships health display color.
             //This will make the stages be:
             //           Full health : 0.0f,1.0f,0.0f,1.0f
             //           Half health : 0.5f,0.5f,0.0f,1.0f
             //           Full health : 1.0f,0.0f,0.0f,1.0f
             // This makes a nice progression from green to red though orange
             mcHealthColor=cRGBA(1.0f-PLAYER_HEALTH_SCALE*Life,PLAYER_HEALTH_SCALE*Life,0.0f,1.0f);
             if(Life<0.0f) _KILL_THIS();
	     return 1;
	 }

	 case DROP_SHIELDS:
	 {
		mpShields[0]->UserSignal(DROP_SHIELDS,0);
		mpShields[1]->UserSignal(DROP_SHIELDS,0);
		mpShields[2]->UserSignal(DROP_SHIELDS,0);
		mpShields[3]->UserSignal(DROP_SHIELDS,0);
		mpShields[4]->UserSignal(DROP_SHIELDS,0);
		mpShields[5]->UserSignal(DROP_SHIELDS,0);
		mpShields[6]->UserSignal(DROP_SHIELDS,0);
		mpShields[7]->UserSignal(DROP_SHIELDS,0);


		 return 1;
	 }

	 default:
	 {
        return 0;
	 }
 }
 return 0;
}


void cPlayer::Stop()
{
        delete mpTargetStatus;
        mpTargetStatus=0;

        for(uint32 liCount=0;liCount<3000;++liCount)
        {
            cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
		    lpPart->SetLife(10.0f+30.0f*RANDOM_NUMBER);
            lpPart->SetSize(2500.0f);
            c3DVf Speed=ParticleBallSpeeds(PARTICLE_SPEED,1.0f);
            lpPart->SetSpeed(Speed.v);
            lpPart->SetPosition(mpHull->Position());
            float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
            lpPart->SetColor(lpSecond);
        }

    //When this cProcess is killed it should also kill the ships hull.
    //Really it should kill everything it created, but since this only dies at the end of the program it won't notice.
	_KILL(mpHull);
	_KILL(mpShields[0]);
	_KILL(mpShields[1]);
	_KILL(mpShields[2]);
	_KILL(mpShields[3]);
	_KILL(mpShields[4]);
	_KILL(mpShields[5]);
	_KILL(mpShields[6]);
	_KILL(mpShields[7]);

	_KILL(mpBeamWeapon);
    if(gbSoundOn)
	{
        mpJetSound->Stop();
        mpJetSound->Buffer("ExplosionSound");
        mpJetSound->Gain(1.0f);
        mpJetSound->Pitch(1.0f);
        mpJetSound->Loop(0);
        mpJetSound->Play();
	}

	gpPlayer=0;

    delete []cPlanningMissileRack::msMissileColors;
    cPlanningMissileRack::msMissileColors=0;

    cCore::mpDead=_CREATE(cText(gp2DCamera));
    cCore::mpDead->Shader("TextProgram");
    cCore::mpDead->AddFont("Ecliptic");
    cCore::mpDead->SetUniform("TextColor",cRGBA(1.0f,1.0f,1.0f,1.0f).Color());
    cCore::mpDead->Text("You were Killed");
    cCore::mpDead->Size(48);
    cCore::mpDead->Position(50.0f,gpWindow->RenderAreaHeight()/2);
    cCore::mpDead->Transparency(8);
}

void cPlayer::MuteSounds()
{
	mpGunShotSound->Stop();
	mpJetSound->Pause();
	mpBeamSound->Stop();
	mpHullSound->Stop();
};

void cPlayer::UnmuteSounds()
{
	mpJetSound->Play();
};

void cPlayer::NextMissileType()
{
    ++miMissileSelected;
if(miMissileSelected>=MISSILE_SLOTS){miMissileSelected=0;}
}

void cPlayer::UpdateMissileRackDisplay()
{
float lfAngle=2*WT_PI/MISSILE_SLOTS;
    for(uint8 liCount=0;liCount<MISSILE_SLOTS;++liCount)
    {
        mpMissileSlots[liCount]->Position(SHIP_MISSILE_RACK_X-sin(lfAngle*(miMissileSelected-liCount))*SHIP_MISSILE_SLOT_RADIUS,SHIP_MISSILE_RACK_Y+cos(lfAngle*(miMissileSelected-liCount))*SHIP_MISSILE_SLOT_RADIUS);
    }
}


vMissileSettings **cPlayer::PrepMissileSettings()
{
    vMissileSettings **lpMissileSettings=new vMissileSettings*[MISSILE_TYPES];
    cMissileSettings *lpBaseMissile=new cMissileSettings(mpHull->ThisMatrixPointer(),"TLevTurretBarrelMesh","TLevTexture",c3DVf(0.0f,-0.5f,1.0f),cGameTarget(),ENEMY_SHIP_FILTER,15.0f,5.0f,0.003f,3000.0f,100.0f,300.0f,lpMomentum);
    lpMissileSettings[MISSILE_TYPE_EXPLOSIVE]=new cExplosiveMissileSettings(lpBaseMissile,300.0f,cDamage(500.0f,DAMAGE_TYPE_AREA));
    lpMissileSettings[MISSILE_TYPE_EMP]=new cEMPMissileSettings(lpBaseMissile,300.0f);
    lpMissileSettings[MISSILE_TYPE_LASER]=new cLaserMissileSettings(lpBaseMissile,300.0f,cDamage(1000.0f,DAMAGE_TYPE_INSTANTANEOUS));
    lpMissileSettings[MISSILE_TYPE_CHAFF]=new cChaffSettings(mpHull->ThisMatrixPointer(),90,0.9f,300.0f,40.0f,cRGBA(1.0f,1.0f,0.6f,1.0f),lpMomentum);
    cMissileSettings *lpSubMunition=new cExplosiveMissileSettings(mpHull->ThisMatrixPointer(),"TLevTurretBarrelMesh","TLevTexture",c3DVf(0.0f,-0.5f,1.0f),cGameTarget(),ENEMY_SHIP_FILTER,15.0f,10.0f,0.004f,3000.0f,100.0f,50.0f,lpMomentum,150.0f,cDamage(75.0f,DAMAGE_TYPE_AREA));
    lpMissileSettings[MISSILE_TYPE_MW]=new cMWMissileSettings(mpHull->ThisMatrixPointer(),"TLevTurretBarrelMesh","TLevTexture",c3DVf(0.0f,-0.5f,1.0f),cGameTarget(),ENEMY_SHIP_FILTER,15.0f,5.0f,0.003f,3000.0f,50.0f,2000.0f,lpMomentum,13,WT_PI*3/8,lpSubMunition);
    return lpMissileSettings;
}

void cPlayer::NewTarget(cGameTarget lpTarget)
{
    mcTargeting=lpTarget;
   _WAKE(mpTargetReticule);
   _WAKE(mpTargetDistance);
    mcTargeting.mpComponent->PlayTargetedNoise();
};

void cPlayer::DisplayMissileRack(float lfTime)
{
    _WAKE(mpMissileRack);
    for(uint8 liMissile=0;liMissile<MISSILE_SLOTS;++liMissile)
    {
        _WAKE(mpMissileSlots[liMissile]);
    }
    mfRackDisplayTimer=lfTime;
};
