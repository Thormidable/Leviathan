
#include "../main.h"

//Constructor for the enemy fighter.
cFighter::cFighter(cDamage lcDamage)
{
	mcBulletDamage=lcDamage;
	lpVertex=0;
	lfThrust=0.0f;
	//Set the Fighters Health to full.
	mfHealth=FIGHTER_HEALTH;

	//Create a model to represent the fighter.
	//Give it a mesh, a shader and a texture.

	mpHull=new cModel();
	mpHull->Mesh("DogFighter");
	mpHull->Shader("TexturingProgram");
	mpHull->AddTexture("DogFighterTexture");
	//Position the ship randomly in a cube 2000 on a side.
	mpHull->Position(ZEROED_RANDOM_NUMBER*2000.0f,ZEROED_RANDOM_NUMBER*2000.0f,ZEROED_RANDOM_NUMBER*2000.0f);
	//Rotate the Ship to face in a random direction.
	mpHull->RotateX(RANDOM_NUMBER*360.0f);
	mpHull->RotateY(RANDOM_NUMBER*360.0f);
	mpHull->RotateZ(RANDOM_NUMBER*360.0f);

	//Create a cCollisionObject to detect collisions with the fighter.
	mpHullColl=new cCollisionObject(mpHull,this);

	//Make it a box for speed and simplicity
	float lpTemp[6]={-4.0f,4.0f,-1.3f,1.3f,-2.5f,2.5f};
	mpHullColl->SetType(lpTemp);

	//Give it a filter so only player projectiles will try to collide.
	mpHullColl->CollisionFilter(ENEMY_SHIP_FILTER);

	//Tell the fighter it's guns are reloaded.
	mfReload=0.0f;

	//Start Predictive Tracking the player
	mpTrack=_CREATE(cPredictiveTracking(&cPlayer::HullMatrix,mpHull));
}

//Activated each Frame
void cFighter::Run()
{
	//Move the ship forwards by the Fighter Speed.
	mpHull->Advance(FIGHTER_SPEED*_TIME_PER_FRAME);

	//Find the Distance to the Player ship (Squared is much cheaper to find)
	double lfDistance=mpHull->DistanceSq(cPlayer::HullMatrix);


	//The use of modes makes the fighters seem to line up attack runs and run away when targeted
	//If this fighter is too close to the player, make it go into flee mode
	if(lfDistance<FIGHTER_FLEE_DISTANCE) {miState=FIGHTER_FLEE; mfFleeingTime=0.0f;}
	//If this fighter is too far to the player, make it go into attack mode
	if(lfDistance>FIGHTER_ATTACK_DISTANCE || mfFleeingTime>FIGHTER_MAX_FLEE) miState=FIGHTER_ATTACK;

	//If Fleeing
	if(miState==FIGHTER_FLEE)
	{
		//Find the players location.
		c3DVf lfPlayer(cPlayer::HullMatrix.Position());
		//Find this Fighters position
		c3DVf lfHull(mpHull->Position());
		//Find the vector between the two, from player to fighter
		lfPlayer=lfHull-lfPlayer;

		//Roll the fighter so it is inline with the flee vector.
		if(mpHull->AngleToVector(lfPlayer)<0.05f)  mpHull->RotateZ(ClampValue(mpHull->RollToVectorPitch(lfPlayer),0.3f*_TIME_PER_FRAME));
		//Pitch the fighter so it is inline with the flee vector.
		mpHull->RotateX(ClampValue(mpHull->PitchToPoint(lfPlayer),0.1f*_TIME_PER_FRAME));

		//Increment the counter for timing how long the fighter has been fleeing.
		mfFleeingTime+=0.04f*_TIME_PER_FRAME;

	}

	//If Attacking
	if(miState==FIGHTER_ATTACK)
	{
		//If the Ship is close enough to try and shoot the player.
		if(lfDistance<FIGHTER_FIRE_DISTANCE)
		{
			//Update Predictive Tracking with the fighters projectile speed.
			//This will update the Predictive targeting with the ships trajectory and calculate the best interception point.
			mpTrack->Update(FIGHTER_BULLET_SPEED);
			//If the predictive targeting deems a hit possible open fire
			if(mpTrack->CanHit())
			{
				//Try to align the ship to the targeting vector
				mpHull->RotateZ(ClampValue(mpHull->RollToVectorPitch(mpTrack->InterceptionVector()),0.3f*_TIME_PER_FRAME));
				mpHull->RotateX(ClampValue(mpHull->PitchToVector(mpTrack->InterceptionVector()),0.1f*_TIME_PER_FRAME));

				//If the fighters guns are reloaded - fire.
				if(mfReload<=0.0f)
				{
					//Create a bullet and set the guns to reload.
					_CREATE(cBullet(mpHull,c3DVf(0.0f,0.0f,1.0f),FIGHTER_BULLET_SPEED,&mcBulletDamage,ENEMY_BULLET_FILTER,PLAYER_SHIP_FILTER));
					mfReload=FIGHTER_RELOAD_TIME;
				}
				else
				{
					//If the guns are not firing this time step, continue to reload.
					mfReload-=0.4*_TIME_PER_FRAME;
				}
			}
			else
			{
				//If the shot cannot hit, track the players position
				mpHull->RotateZ(ClampValue(mpHull->RollToPointPitch(cPlayer::HullMatrix.Position()),0.3f*_TIME_PER_FRAME));
				mpHull->RotateX(ClampValue(mpHull->PitchToPoint(cPlayer::HullMatrix.Position()),0.1f*_TIME_PER_FRAME));
			}

		}
		else
		{
			//If the fighter is too far away to shoot, track the players position
			mpHull->RotateZ(ClampValue(mpHull->RollToPointPitch(cPlayer::HullMatrix.Position()),0.3f*_TIME_PER_FRAME));
			mpHull->RotateX(ClampValue(mpHull->PitchToPoint(cPlayer::HullMatrix.Position()),0.1f*_TIME_PER_FRAME));
		}


	}

	//If the Fighter has taken sufficient Damage
	//Generate particles
	if(mfParticleRate<=0.0f)
	{
		//If the Helath is low enough to create particles
		if(mfHealth<FIGHTER_HEALTH*FIGHTER_FLAMETRAILS)
		{
			//Create a particle object.
			cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
			//cParticle *lpPart=_CREATE(cParticle());
			lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
			//Set a size for it.
			lpPart->SetSize(5.0f);
			//Give it a speed.
			c3DVf Speed=c3DVf(ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED);
			lpPart->SetSpeed(Speed.v);
			//Set it to position on the centre of the Hull
			lpPart->SetPosition(mpHull->Position());
			//Give it a randomised red / yellow / orange color.
			float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,0.5f+RANDOM_NUMBER*0.5f,0.0f,0.3f};
			lpPart->SetColor(lpSecond);
			//Set the generator to 'reload' the particle generation based on damage sustained.
			mfParticleRate=mfHealth*0.8f*_TIME_PER_FRAME;
		}
	}
	else
	{
		//Update the Particle Rate counter to determine when the next particle should be generated
		mfParticleRate-=1.0f*_TIME_PER_FRAME;
	}

}

//One Fighter Death this function will run
void cFighter::Stop()
{
	//Tell the player this fighter is dead so it can re target if neccessary.
	if(gpPlayer) gpPlayer->UserSignal(DEAD_FIGHTER,this);

	//Create a particle explosion, moving with the fighters last speed.
	//Like before but generate a large number instantaneously
	for(uint32 liCount=0;liCount<600;++liCount)
	{
		cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
		//cParticle *lpPart=_CREATE(cParticle());
		lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
		lpPart->SetSize(5.0f);
		c3DVf Speed=c3DVf(ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED);
		Speed[0]+=mpHull->Zx()*FIGHTER_SPEED/2;
		Speed[1]+=mpHull->Zy()*FIGHTER_SPEED/2;
		Speed[2]+=mpHull->Zz()*FIGHTER_SPEED/2;
		Speed*=_TIME_PER_FRAME;
		lpPart->SetSpeed(Speed.v);
		lpPart->SetPosition(mpHull->Position());

		float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
		lpPart->SetColor(lpSecond);
	}


	//Generate some shrapnel particles
	//These are like before, but random colors of grey.
	for(uint32 liCount=0;liCount<200;++liCount)
	{
		cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
		//cParticle *lpPart=_CREATE(cParticle());
		lpPart->SetLife(0.5f+1.5f*RANDOM_NUMBER);
		lpPart->SetSize(5.0f);
		c3DVf Speed=c3DVf(ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED,ZEROED_RANDOM_NUMBER*PARTICLE_SPEED);
		Speed[0]+=mpHull->Zx()*FIGHTER_SPEED/2;
		Speed[1]+=mpHull->Zy()*FIGHTER_SPEED/2;
		Speed[2]+=mpHull->Zz()*FIGHTER_SPEED/2;
		lpPart->SetSpeed(Speed.v);
		lpPart->SetPosition(mpHull->Position());
		float lfRandom=RANDOM_NUMBER;
		float lpSecond[4]={lfRandom,lfRandom,lfRandom,1.0f};
		lpPart->SetColor(lpSecond);
	}

	//Finally make the fighters hull die.
	//This will also stop collisions.
	_KILL(mpHull);
}

//This is a function for receiving signals from other processes.
bool cFighter::UserSignal(SIGNAL lsSignal,void *lpData)
{
	//determine the type of signal.
	switch(lsSignal)
	{
		//If it is damage, update the health of the fighter.
	case BEAM_COLLISION :
		{
			float lpDamage=(*(float*)lpData);
			mfHealth-=lpDamage;
			//If the damage is more than the fighter can take kill it.
			//This will call Stop()
			if(mfHealth<0.0f) _KILL_THIS();
			return 1;
		}
	default:
		{
			return 0;

		}
	}
	return 0;

}
