
#include "../main.h"

cShield::cShield(cModel *lpGenerator,cLeviathanShieldSettings *lpSettings)
{

    mfRecharge=lpSettings->mfShieldRecharge;
    mfMax=lpSettings->mfShieldMax;
	mfInvMax=1.0f/mfMax;
    mfDelay=-fabs(lpSettings->mfShieldDelay);
    //Store the pointer to the generating Model
    mpGenerator=lpGenerator;

    //Store the Shields Color. Set the Current Shield Color to be the Shield Color.
    mcCurrColor=mcShieldColor=lpSettings->mcShieldColor;
	mcShieldColor[3]=0.2;

    //Set the Shields health to be it's maximum value.
    mfHealth=mfMax;

    //Create a Model to display the shield around it's generator
    //Give it a Shader and set it's variables.
    //Give it a Mesh and position it over it's generator.
    //Make it a Transparent Object.
    mpShield=_CREATE(cModel(mpGenerator->Renderer()));
    mpShield->Shader("SetUniformColorProgram");
    mpShield->SetVariablePointer("ModelColor",mcCurrColor.Color());
    mpShield->Mesh(lpSettings->mpShield);
    //mpShield->Equals(lpGenerator->ThisMatrix()*InvMatrix);
	//mpShield->Equals(lpGenerator->Matrix());
    mpShield->Transparency(4);

    InvMatrix.Equals(lpSettings->mpFoundations->Matrix(0)->InversionMatrix());
    float lfX,lfY,lfZ;
    lfX=InvMatrix[0]*InvMatrix[12]+InvMatrix[4]*InvMatrix[13]+InvMatrix[8]*InvMatrix[14];
    lfY=InvMatrix[1]*InvMatrix[12]+InvMatrix[5]*InvMatrix[13]+InvMatrix[9]*InvMatrix[14];
    lfZ=InvMatrix[2]*InvMatrix[12]+InvMatrix[6]*InvMatrix[13]+InvMatrix[10]*InvMatrix[14];
    InvMatrix.PositionX(lfX);
    InvMatrix.PositionY(lfY);
    InvMatrix.PositionZ(lfZ);
    mpShield->Equals(InvMatrix);


    //Create a cCollisionObject for it.
    //Make it use the cCollisionmesh handed to the object.
    //Finally set it's Collision Filter.
    mpShieldColl=_CREATE(cCollisionObject(mpShield,this));
    mpShieldColl->SetTypeMesh(lpSettings->mpShieldColl);
    mpShieldColl->CollisionFilter(lpSettings->miFilter);
	mpShieldColl->Delay(3);
};

//Constructor for a Shield
//It wants a cModel to follow
//A Mesh to form the displayed sheild
//A Collision Mesh to detect collisions
//A Collision Filter
//And a Color to render the shield
cShield::cShield(cModel *lpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float lfDelay,cMatrix4 *OffSet)
{

    mfRecharge=lfRecharge;
    mfMax=lfMax;
	mfInvMax=1.0f/mfMax;
    mfDelay=-fabs(lfDelay);
    //Store the pointer to the generating Model
    mpGenerator=lpGenerator;

    //Store the Shields Color. Set the Current Shield Color to be the Shield Color.
    mcCurrColor=mcShieldColor=lcShieldColor;

    //Set the Shields health to be it's maximum value.
    mfHealth=mfMax;

    //Create a Model to display the shield around it's generator
    //Give it a Shader and set it's variables.
    //Give it a Mesh and position it over it's generator.
    //Make it a Transparent Object.
    mpShield=_CREATE(cModel(mpGenerator->Renderer()));
    mpShield->Shader("SetUniformColorProgram");
    mpShield->SetVariablePointer("ModelColor",mcCurrColor.Color());
    mpShield->Mesh(_GET_MESH_FILE(lpShield.c_str()));
    //mpShield->Equals(lpGenerator->ThisMatrix()*InvMatrix);
	//mpShield->Equals(lpGenerator->Matrix());
    mpShield->Transparency(4);

	if(OffSet)
	{
		InvMatrix.Equals(OffSet->InversionMatrix());
		float lfX,lfY,lfZ;
		lfX=InvMatrix[0]*InvMatrix[12]+InvMatrix[4]*InvMatrix[13]+InvMatrix[8]*InvMatrix[14];
		lfY=InvMatrix[1]*InvMatrix[12]+InvMatrix[5]*InvMatrix[13]+InvMatrix[9]*InvMatrix[14];
		lfZ=InvMatrix[2]*InvMatrix[12]+InvMatrix[6]*InvMatrix[13]+InvMatrix[10]*InvMatrix[14];
		InvMatrix.PositionX(lfX);
		InvMatrix.PositionY(lfY);
		InvMatrix.PositionZ(lfZ);
	}

    mpShield->Equals(InvMatrix);


    //Create a cCollisionObject for it.
    //Make it use the cCollisionmesh handed to the object.
    //Finally set it's Collision Filter.
    mpShieldColl=_CREATE(cCollisionObject(mpShield,this));
    mpShieldColl->SetTypeMesh(_GET_COLLISION_MESH_FILE(lpShieldColl.c_str()));
    mpShieldColl->CollisionFilter(liFilter);
	mpShieldColl->Delay(3);



};

//This function will run every frame and update the shield.
void cShield::Run()
{
    //This will update the Shields position about it's ship.
    //mpShield->Equals(mpGenerator->mmCache*InvMatrix);
	//mpShield->Equals(mpGenerator->mmCache.Matrix());

    //If the Shield is damaged recharge it.
    if(mfHealth<mfMax) mfHealth+=mfRecharge*_TIME_PER_FRAME;

    //If the shield is destroyed, sleep it. Otherwise Wake it.
    //Sleeping it will stop it being visible and stop it colliding with other objects.
    if(mfHealth<0.0f) _SLEEP(mpShield);
    else _WAKE(mpShield);

    //Restore the sheilds color to it's normal color.
    mcCurrColor-=(mcCurrColor-mcShieldColor)*0.01f;

    //Set the Alpha based on the health of the shield
	mcCurrColor.A(SHIELD_ALPHA*mfHealth*mfInvMax);



};

//This is killed when the Shield Process is killed.
void cShield::Stop()
{
 //Kill the Shield Object
 _KILL(mpShield);
};


//This receives signals sent from other Processes
bool cShield::UserSignal(SIGNAL lsSignal,void *lpData)
{
  //Determine the type of signal
   switch(lsSignal)
   {
     //If it is a collision with a projectile take the damage
     case EXPLOSION_COLLISION:
     case BEAM_COLLISION:
     {
        float Damage=*((float*)lpData);
        //Take the Damage
        mfHealth-=Damage;
        _SLEEP(mpShield);
        PlaySound();
        //If the shield is destroyed start the shield delay
        if(mfHealth<0.0f) mfHealth=mfDelay;
        else
        {
            //The shield has been hit, so make the color white to show the impact.
            mcCurrColor.R(1.0f);
            mcCurrColor.G(1.0f);
            mcCurrColor.B(1.0f);
        }
        return 1;
     }
	 case DROP_SHIELDS:
	 {
		mfHealth=mfDelay;
		_SLEEP(mpShield);
		 return 1;
	 }
     default :
     {
       return 0;
     }
   };

   return 0;

}

void cShield::NoPower()
{
    mfHealth-=mfRecharge*2;
};

//This is a constructor for a subtype of shield : the cPlayerShield.
//This is the same as a normal shield but also displays the shield status to the screen.
//Note how some, but not all arguments are passed to cShield.
cPlayerShield::cPlayerShield(cModel *lpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float lfDelay, float lfX,float lfY, float lfSize,cTexture *lpTexture): cShield(lpGenerator,lpShield,lpShieldColl,liFilter,lcShieldColor,lfRecharge,lfMax,lfDelay)
{

//Create a cImage to display the shield status
//Give it a Shader a texture and set the Shader Variable "UniformColor"
mpDisplay=_CREATE(cImage(gp2DCamera));
mpDisplay->Shader("Image2DUniformColorProgram");
mpDisplay->AddTexture(lpTexture);
mpDisplay->SetVariablePointer("UniformColor",mcCurrColor.Color());

//Set the Position, Size and Transparency
mpDisplay->Position(lfX,lfY);
mpDisplay->Width(lfSize);
mpDisplay->Height(lfSize);
mpDisplay->Transparency(2);

if(!mpShieldSound)
{
    #if ACTIVATE_SOUND
	mpShieldSound = _CREATE(cAudioObject);
	mpShieldSound -> Buffer ("ShieldStrikeSound");
	#endif
}


};

cAudioObject *cPlayerShield::mpShieldSound=0;

void cPlayerShield::PlaySound()
{
    #if ACTIVATE_SOUND
        mpShieldSound->Pitch(RANDOM_NUMBER+0.5f);
        mpShieldSound->Gain(RANDOM_NUMBER+0.1f);
        mpShieldSound->Play();
    #endif
};

void cPlayerShield::Run()
{
 cShield::Run();

mpShield->Equals(mpGenerator->mmCache*InvMatrix);

//This will check for collisions
//lpProc will point at each Collisions owning process.
//lpList will store the list of detected collisions.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpShieldColl,ENEMY_SHIP_FILTER+1);
    bool lbFound=false;
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy shield is detected, drop the shield
        lpProc->UserSignal(DROP_SHIELDS,0);
		lbFound=true;
	}
	if(lbFound) gpPlayer->UserSignal(DROP_SHIELDS,0);
	delete lpList;


};



/*
//Constructor for a Shield
//It wants a cModel to follow
//A Mesh to form the displayed sheild
//A Collision Mesh to detect collisions
//A Collision Filter
//And a Color to render the shield
cShield::cShield(cModel *lpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float lfDelay,cMatrix4 *OffSet)
{

    mfRecharge=lfRecharge;
    mfMax=lfMax;
	mfInvMax=1.0f/mfMax;
    mfDelay=-fabs(lfDelay);
    //Store the pointer to the generating Model
    mpGenerator=lpGenerator;

    //Store the Shields Color. Set the Current Shield Color to be the Shield Color.
    mcCurrColor=mcShieldColor=lcShieldColor;

    //Set the Shields health to be it's maximum value.
    mfHealth=mfMax;


	if(OffSet)
	{

		InvMatrix.Equals(OffSet->InversionMatrix());
		float lfX,lfY,lfZ;
		lfX=InvMatrix[0]*InvMatrix[12]+InvMatrix[4]*InvMatrix[13]+InvMatrix[8]*InvMatrix[14];
		lfY=InvMatrix[1]*InvMatrix[12]+InvMatrix[5]*InvMatrix[13]+InvMatrix[9]*InvMatrix[14];
		lfZ=InvMatrix[2]*InvMatrix[12]+InvMatrix[6]*InvMatrix[13]+InvMatrix[10]*InvMatrix[14];
		InvMatrix.PositionX(lfX);
		InvMatrix.PositionY(lfY);
		InvMatrix.PositionZ(lfZ);
	}

    //Create a Model to display the shield around it's generator
    //Give it a Shader and set it's variables.
    //Give it a Mesh and position it over it's generator.
    //Make it a Transparent Object.
    mpShield=_CREATE(cModel);
    mpShield->Shader("SetUniformColorProgram");
    mpShield->SetVariablePointer("ModelColor",mcCurrColor.Color());
    mpShield->Mesh(_GET_MESH_FILE(lpShield.c_str()));
    mpShield->Equals(lpGenerator->ThisMatrix()*InvMatrix);
	//mpShield->Equals(lpGenerator->Matrix());
    mpShield->Transparency(1);

    //Create a cCollisionObject for it.
    //Make it use the cCollisionmesh handed to the object.
    //Finally set it's Collision Filter.
    mpShieldColl=_CREATE(cCollisionObject(mpShield,this));
    mpShieldColl->SetTypeMesh(_GET_COLLISION_MESH_FILE(lpShieldColl.c_str()));
    mpShieldColl->CollisionFilter(liFilter);
	mpShieldColl->Delay(3);



};

//This function will run every frame and update the shield.
void cShield::Run()
{
    //This will update the Shields position about it's ship.
    mpShield->Equals(mpGenerator->mmCache*InvMatrix);
	//mpShield->Equals(mpGenerator->mmCache.Matrix());

    //If the Shield is damaged recharge it.
    if(mfHealth<mfMax) mfHealth+=mfRecharge;

    //If the shield is destroyed, sleep it. Otherwise Wake it.
    //Sleeping it will stop it being visible and stop it colliding with other objects.
    if(mfHealth<0.0f) _SLEEP(mpShield);
    else _WAKE(mpShield);

    //Restore the sheilds color to it's normal color.
    mcCurrColor-=(mcCurrColor-mcShieldColor)*0.01f;

    //Set the Alpha based on the health of the shield
	mcCurrColor.A(SHIELD_ALPHA*mfHealth*mfInvMax);



};

//This is killed when the Shield Process is killed.
void cShield::Stop()
{
 //Kill the Shield Object
 _KILL(mpShield);
};


//This receives signals sent from other Processes
bool cShield::UserSignal(SIGNAL lsSignal,void *lpData)
{
  //Determine the type of signal
   switch(lsSignal)
   {
     //If it is a collision with a projectile take the damage
     case BEAM_COLLISION:
     {
        float Damage=*((float*)lpData);
        //Take the Damage
        mfHealth-=Damage;
        _SLEEP(mpShield);
        PlaySound();
        //If the shield is destroyed start the shield delay
        if(mfHealth<0.0f) mfHealth=mfDelay;
        else
        {
            //The shield has been hit, so make the color white to show the impact.
            mcCurrColor.R(1.0f);
            mcCurrColor.G(1.0f);
            mcCurrColor.B(1.0f);
        }
        return 1;
     }
	 case DROP_SHIELDS:
	 {
		mfHealth=mfDelay;
		_SLEEP(mpShield);
		 return 1;
	 }
     default :
     {
       return 0;
     }
   };

   return 0;

}

//This is a constructor for a subtype of shield : the cPlayerShield.
//This is the same as a normal shield but also displays the shield status to the screen.
//Note how some, but not all arguments are passed to cShield.
cPlayerShield::cPlayerShield(cModel *lpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float lfDelay, float lfX,float lfY, float lfSize,cTexture *lpTexture): cShield(lpGenerator,lpShield,lpShieldColl,liFilter,lcShieldColor,lfRecharge,lfMax,lfDelay)
{

//Create a cImage to display the shield status
//Give it a Shader a texture and set the Shader Variable "UniformColor"
mpDisplay=_CREATE(cImage(gp2DCamera));
mpDisplay->Shader("Image2DUniformColorProgram");
mpDisplay->AddTexture(lpTexture);
mpDisplay->SetVariablePointer("UniformColor",mcCurrColor.Color());

//Set the Position, Size and Transparency
mpDisplay->Position(lfX,lfY);
mpDisplay->Width(lfSize);
mpDisplay->Height(lfSize);
mpDisplay->Transparency(1);

if(!mpShieldSound)
{
	mpShieldSound = _CREATE(cAudioObject);
	mpShieldSound -> Buffer ("ShieldStrikeSound");
}


};

cAudioObject *cPlayerShield::mpShieldSound=0;

void cPlayerShield::PlaySound()
{
    mpShieldSound->Pitch(RANDOM_NUMBER+0.5f);
    mpShieldSound->Gain(RANDOM_NUMBER+0.1f);
    mpShieldSound->Play();
};

void cPlayerShield::Run()
{
 cShield::Run();


//This will check for collisions
//lpProc will point at each Collisions owning process.
//lpList will store the list of detected collisions.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpShieldColl,ENEMY_SHIP_FILTER+1);
    bool lbFound=false;
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy shield is detected, drop the shield
        lpProc->UserSignal(DROP_SHIELDS,0);
		lbFound=true;
	}
	if(lbFound) gpPlayer->UserSignal(DROP_SHIELDS,0);
	delete lpList;


};
*/

cRGBA cShield::ShieldStatusColor()
{
    return cRGBA(1.0f-((mfHealth*mfInvMax)*0.5+0.5),(mfHealth*mfInvMax)*0.5+0.5,0.0f,1.0f).Color();
};
