#include "stdafx.h"
#include "../main.h"


//Bullet cProcess constructor.
//cBullet::cBullet(cMatrix4 *lpMatrix,float lfDist)
cBullet::cBullet(cMatrix4 *lpMatrix,c3DVf lfOffset,float lfSpeed,cDamage *lpDamage,uint32 liFilter,uint32 liTargetFilter)
{
 mfSpeed=lfSpeed;
 miTargetFilter=liTargetFilter;
 mcDamage=lpDamage;

 //Create a cPoint for the Bullet (this is a render lite object which can still carry cCollisionObjects)
 //Give it a Shader and a color.
 /*mpBullet=new cPoint;
 mpBullet->Shader("PointFadeProgram");
 mpBullet->Color(BULLET_COLOR);
*/

 mpBullet=new cLine;
 mpBullet->Shader("SetUniformColorProgram");
 cRGBA MyColor(1.0f,1.0f,0.0f,1.0f);
 mpBullet->SetVariable("ModelColor",MyColor.Color());
 mpBullet->Width(3.0f);


 //Set mfLife so it can be used to set a Shader variable.
 mfLife=4.0f;

 //Set the Shader Variable mfLife to be the value currently in mfLife  (4.0)
 //mpBullet->SetVariable("mfSize",&mfLife);
 //Set the Shader Variable to track the value in the variable mfLife (currently 4.0, soon to be 70.0)
 //Set mfLife to 70. This will change the Shader variabler mfFade to be 70.
//This is the life the bullet has.
mfLife=70.0f;
// mpBullet->SetVariable("mfFade",&mfLife);
 //Tell these objects to be transparent.
 mpBullet->Transparency(1);
 //Make the Bullet orientate and position the same as the cMatrix4 it was passed.
 mpBullet->Equals(lpMatrix);
 //Offset the Bullets start position by the distance lfDist
 mpBullet->Advance(lfOffset);



 c3DVf MyVector(0.0f,0.0f,-lfSpeed*3);
 mpBullet->Vector(MyVector.v);


 //Create a cCollisionObject to detect Collisions for the bullets
mpBulletColl=_CREATE(cCollisionObject(mpBullet,this));
//Set the type to be a Ray type.
//This is used as bullets travel much faster than their size.
//As such it is easy for standard collisions to be missed.
//Ray collisions track the object and check for collisions along it's entire path.
mpBulletColl->SetType(mpBullet,BULLET_SIZE);
//Finally give it the collision filter value for this type of bullet.
mpBulletColl->CollisionFilter(liFilter);

mfLife=BULLET_RANGE;
}

//This happens every fram
void cBullet::Run()
{
    bool lbColl=false;

    //Check for Collisions with Shields (If there are collisions with shields, the bullet is killed before it can go further.
    //Collision Detection is the same as in WTcPlayer.cpp
    //Note mfTargetFilter and mfTargetFilter+1. Shields filter values have been set one higher than the ship they protect.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpBulletColl,miTargetFilter+2);
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    lbColl=true;
	    break;
	}
    delete lpList;

 if(lbColl)
 {
    //Check for Collisions with Shields (If there are collisions with shields, the bullet is killed before it can go further.
    //Collision Detection is the same as in WTcPlayer.cpp
    //Note mfTargetFilter and mfTargetFilter+1. Shields filter values have been set one higher than the ship they protect.
	lpList=_COLLISION_HANDLER->GenerateDetailedCollisionList(mpBulletColl,miTargetFilter+1);
	_COLLISION_HANDLER->GenerateDetailedCollisionList(mpBulletColl,miTargetFilter,lpList);
	lpList->RecalculateDistances();
	lpList->SortByDistance();
	lpProc=lpList->NextCollisionP();
	if(lpProc)
	{
	    mcDamage->mfPos=lpList->CurrentCollisionDetail()->Centre();
	    gpRenderCollision=dynamic_cast<cRenderObject*>(lpList->CurrentCollisionR());
        lpProc->UserSignal(BEAM_COLLISION,mcDamage);
        if(!dynamic_cast<cShield*>(lpProc) && !dynamic_cast<cPlayer*>(lpProc) ) GenerateDamageParticles(lpList->CurrentCollisionDetail()->Centre(),3);

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



        _KILL_THIS();
        delete lpList;
        return;
	}
	delete lpList;

 }


    lpList=_COLLISION_HANDLER->GeneratePossibleCollisionList(mpBulletColl,MISSILE_FILTER);
    vRenderObject *lpRend=lpList->NextCollisionR();
	while(lpRend)
	{
	    if(lpList->CurrentCollisionP() && lpRend->mmCache.DistanceSq(mpBullet->mmCache)<BULLET_MISSILE_INTERACTION_DISTANCE)
	    {
	        lpList->CurrentCollisionP()->UserSignal(BEAM_COLLISION,0);
            _KILL_THIS();
            delete lpList;
            return;
	    }

	    lpRend=lpList->NextCollisionR();
	}

    delete lpList;

    //Advance the bullet by its speed.
    mpBullet->AdvanceZ(mfSpeed);

    //Reduce it's life (duration of existence based on time alive)
    mfLife-=mfSpeed;
    //One the bullet has used up it's duration kill it.
    if(mfLife<0.0f) _KILL_THIS();
}


//This is called when a bullet dies.
void cBullet::Stop()
{
    //Kill the object representing the bullet.
    //This will also disable collisions.
    _KILL(mpBullet);
    //This is good practice to make pointers zero when not in use.
    mpBullet=0;

}

void GenerateDamageParticles(c3DVf mpCentre,uint32 liParticles)
{
		    while(liParticles)
		    {
		        cParticle *lpPart=cLeviathan::mpLeviathanParticleHandler->NewParticle();
		        //cParticle *lpPart=_CREATE(cParticle());
                lpPart->SetSize(2500.0f);
                lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
                lpPart->SetSpeed(ParticleBallSpeeds(PARTICLE_SPEED,0.8f).v);
                lpPart->SetPosition(mpCentre.v);
                float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.6f};
                lpPart->SetColor(lpSecond);
                --liParticles;
		    }
};


void GenerateDamageParticles(c3DVf mpCentre)
{
	/*
                cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
		        //cParticle *lpPart=_CREATE(cParticle());
		        lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
                lpPart->SetSize(2500.0f);

                lpPart->SetSpeed(ParticleBallSpeeds(PARTICLE_SPEED,0.8f).v);
                lpPart->SetPosition(mpCentre.v);
                float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.6f};
                lpPart->SetColor(lpSecond);*/
};
