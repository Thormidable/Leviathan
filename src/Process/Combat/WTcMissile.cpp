

#include "../../main.h"

cChaffCharge *cMissile::spChaffDeployed=0;


  cMissile::cMissile(cMissileSettings *lpSettings)
  {
     mpSettings=lpSettings;

     mpHull=_CREATE(cModel());
     mpHull->Shader("TexturingProgram");
     mpHull->Mesh(mpSettings->mpMesh);
     mpHull->AddTexture(mpSettings->mpTexture);
     mpHull->Equals(mpSettings->mpMatrix);
     mpHull->Advance(mpSettings->mfOffset);

     mpHullColl=_CREATE(cCollisionObject(mpHull,this));
     mpHullColl->CollisionFilter(MISSILE_FILTER);
     mpHullColl->SetTypeRay(mpHull,3.0f);

     mpMomentum=_CREATE(cMomentum(mpHull));
     if(mpSettings->mpMomentumBase) mpMomentum->Equals(mpSettings->mpMomentumBase);

     mpTarget=mpSettings->mpTarget;
     mfHealth=mpSettings->mfHealth;

	 mpReticule=_CREATE(cImage(gp2DCamera));
	 mpReticule->Shader("Image2DProgram");
	mpReticule->AddTexture("MissileTrackingReticule");
	mpReticule->Width(21);
	mpReticule->Height(21);
	mpReticule->Position(_WINDOW->RenderAreaWidth()*0.85,_WINDOW->RenderAreaHeight()*0.85);
	mpReticule->Transparency(1);

	mpMapDisp=new cMapDisplayObject(mpHull,cRGBA(1.0f,1.0f,0.0f,0.5f),"MissileTrackingReticule");

	mf180Delay=-1.0f;
	mbTracking=true;

  };

void cMissile::Run()
{
    if(!mpTarget.Targeted()) {Detonate(); _KILL_THIS(); return;}

    cMapDisplay::mpStaticThis->MapObject(mpMapDisp);

	c3DVf lfTemp=mpHull->GetScreenPosition();

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

        mpReticule->Position(lfTemp.X(),lfTemp.Y());

    ChaffCheck();

    if(mf180Delay<0.0f)
    {
        float lfCheck=mpHull->YawToPoint(mpTarget.GetPosition());
        if(fabs(lfCheck)>WT_PI/2) {if(mbTracking){mf180Delay=ENEMY_MISSILE_PASS_DELAY; mbTracking=false;}}
        else mbTracking=true;
        mpHull->RotateY(ClampValue(lfCheck,mpSettings->mfTrack));

        lfCheck=mpHull->PitchToPoint(mpTarget.GetPosition());
        if(fabs(lfCheck)>WT_PI/2) {if(mbTracking){mf180Delay=ENEMY_MISSILE_PASS_DELAY; mbTracking=false;}}
        else mbTracking=true;
        mpHull->RotateX(ClampValue(lfCheck,mpSettings->mfTrack));
    }
    else
    {
        mf180Delay-=0.04f;
    }
    mpMomentum->LimitedThrustZ(mpSettings->mfThrust,mpSettings->mfThrustLimit);
    mpMomentum->Straighten(mpSettings->mfSideThrust);
    mpMomentum->Update();

    if(mfHealth<0.0f || mpHull->DistanceSq(mpTarget.GetPosition())<mpSettings->mfDetonationDistance)
    {
        Detonate();
      _KILL_THIS();
      return;
    }



   bool lbColl=false;

    //Check for Collisions with Shields (If there are collisions with shields, the bullet is killed before it can go further.
    //Collision Detection is the same as in WTcPlayer.cpp
    //Note mfTargetFilter and mfTargetFilter+1. Shields filter values have been set one higher than the ship they protect.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter+2);
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
        lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter+1);
        for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
        {
            Detonate();
            _KILL_THIS();
            delete lpList;
            return;
        }
        delete lpList;
    }

            cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
            lpPart->SetLife(0.5f+0.5f*RANDOM_NUMBER);
            lpPart->SetSize(8000.0f);
            c3DVf Speed(-mpHull->Zx(),-mpHull->Zy(),-mpHull->Zz());
            lpPart->SetSpeed(ParticleSideVelocity(Speed*0.1f,0.2f,0.5f).v);
            lpPart->SetPosition(mpHull->Position());
            float lfColor=RANDOM_NUMBER;
            float lpSecond[4]={lfColor,lfColor,lfColor,SMOKE_TRANSPARENCY};
            lpPart->SetColor(lpSecond);

    mfHealth-=MISSILE_HEALTH_BURN_RATE;



};

bool cMissile::UserSignal(SIGNAL lsSignal,void *lpData)
{
    (void) lpData;
    switch(lsSignal)
    {
        case BEAM_COLLISION:
        {
            _KILL_THIS();
            return 1;
        };
        default :
        {
            return 0;
        };
    };
    return 0;
}

void cMissile::Stop()
{


    _KILL(mpHull);
	_KILL(mpReticule);
	delete mpMapDisp;
    delete mpMomentum;
    mpMomentum=0;
};


cExplosiveMissile::cExplosiveMissile(cExplosiveMissileSettings *lpSettings) : cMissile(lpSettings)
{

}

cLaserMissile::cLaserMissile(cLaserMissileSettings *lpSettings) : cMissile(lpSettings)
{

}

cEMPMissile::cEMPMissile(cEMPMissileSettings *lpSettings) : cMissile(lpSettings)
{

}

void cExplosiveMissile::Detonate()
{

 mpHullColl->SetType(mpSettings->DetonationSize());

     //This will check for collisions
    //lpProc will point at each Collisions owning process.
    //lpList will store the list of detected collisions.
    //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter+1);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    mpSettings->mcDamage.mfPos=mpHull->mmCache.Position();
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(EXPLOSION_COLLISION,&(mpSettings->mcDamage));
	}
	delete lpList;

    lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
        mpSettings->mcDamage.mfPos=mpHull->mmCache.Position();
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(EXPLOSION_COLLISION,&(mpSettings->mcDamage));
	}

	delete lpList;

        for(uint32 liCount=0;liCount<2000;++liCount)
        {
            cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
            lpPart->SetLife(1.0f+1.0f*RANDOM_NUMBER);
            lpPart->SetSize(2500.0f);
            lpPart->SetSpeed(ParticleBallSpeeds(PARTICLE_SPEED,0.9f).v);
            lpPart->SetPosition(mpHull->Position());
            float lpSecond[4]={0.8f+RANDOM_NUMBER*0.2f,RANDOM_NUMBER,0.0f,0.3f};
            lpPart->SetColor(lpSecond);
        }


};


void cLaserMissile::Detonate()
{

 mpHullColl->SetType(1.0f,mpSettings->DetonationSize());

     //This will check for collisions
    //lpProc will point at each Collisions owning process.
    //lpList will store the list of detected collisions.
    //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter+1);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(BEAM_COLLISION,&(mpSettings->mcDamage));
	}
	delete lpList;

    lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,mpSettings->miFilter);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(BEAM_COLLISION,&(mpSettings->mcDamage));
	}
delete lpList;
};

void cEMPMissile::Detonate()
{

 mpHullColl->SetType(mpSettings->DetonationSize());

     //This will check for collisions
    //lpProc will point at each Collisions owning process.
    //lpList will store the list of detected collisions.
    //GenerateCollisionList() will find all collisions with mpBeamColl where the other object has the filter value _ENEMY_SHIP_FILTER.
	cProcess *lpProc;
	cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,ENEMY_SHIP_FILTER+1);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(DROP_SHIELDS,0);
	}
	delete lpList;

	lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl,PLAYER_SHIP_FILTER+1);
	//This will step through all the collisions making lpProc point at the next process.
	for(lpProc=lpList->NextCollisionP();lpProc;lpProc=lpList->NextCollisionP())
	{
	    //If a collision with an enemy fighter is detected, tell the fighter how much damage to take.
        lpProc->UserSignal(DROP_SHIELDS,0);
	}
	delete lpList;

	       for(uint32 liCount=0;liCount<3000;++liCount)
        {
            cParticle *lpPart=_CAMERA->ParticleHandler()->NewParticle();
            //cParticle *lpPart=_CREATE(cParticle());
            lpPart->SetLife(1.0f+3.0f*RANDOM_NUMBER);
            lpPart->SetSize(2500.0f);
            lpPart->SetSpeed(ParticleBallSpeeds(PARTICLE_SPEED,0.9f).v);
            lpPart->SetPosition(mpHull->Position());
            float lpSecond[4]={0.0f,RANDOM_NUMBER,RANDOM_NUMBER*0.3f,0.3f};
            lpPart->SetColor(lpSecond);
        }


};


    cChaffCharge::cChaffCharge(cChaffSettings *lpSettings)
    {
        mbChaffBlind=0;
        cMissile::spChaffDeployed=this;
        mvSpeed=lpSettings->mpCurSpeed->GSpeeds();
        mvSpeed*=0.001f;
        mvSpeed+=GenerateUniformRandomVector()*lpSettings->mfSpreadRate*RANDOM_NUMBER;
        mfDelay=RANDOM_NUMBER*lpSettings->mfChargeDelay;
        mfSize=lpSettings->mfChargeSize*(0.5f+0.5f*RANDOM_NUMBER);
        mfCurrentSize=3.0f;

        mpCharge=_CREATE(cBillBoard);
        mpCharge->Shader("ChaffFlareProgram");
        mpCharge->AddTexture("PerlinNoise");
        mpCharge->SetUniformPointer("Bb_Size",&mfCurrentSize);
        mpCharge->SetUniformPointer("StarColor",lpSettings->mcFlareColor.Color());

        //mpCharge->SetUniformPointer("CoronaValue",&mfDelay);
        mpCharge->SetUniform("CoronaValue",&mfDelay);

        float lfTemp=1.0f;
        mpCharge->SetUniform("CoronaDensity",&lfTemp);
        lfTemp=8.0f;
        mpCharge->SetUniform("ScaleCore",&lfTemp);
        lfTemp=0.5f;
        mpCharge->SetUniform("CoreDensity",&lfTemp);
        lfTemp=4.0f;
        mpCharge->SetUniform("CoronaSpread",&lfTemp);


        mpCharge->Equals(lpSettings->mpSource);
        mpColl=0;

    };

    void cChaffCharge::Run()
    {
        if(mbChaffBlind) cMissile::spChaffDeployed=0;
        mbChaffBlind=true;
        float lfTemp=RANDOM_NUMBER;
        mpCharge->SetUniform("CoronaValue",&lfTemp);
        //mpCharge->SetUniform("CoronaValue",&lfTemp);
        mpCharge->GAdvance(mvSpeed.v);
        if(mfDelay<CHAFF_DELAY_ACTIVATE)
        {
         if(mfDelay>0.0f)
         {
            mfCurrentSize=(CHAFF_DELAY_ACTIVATE-mfDelay)/(CHAFF_DELAY_ACTIVATE)*mfSize;
            if(!mpColl)
            {
                mpColl=_CREATE(cCollisionObject(mpCharge,this));
            }
            mpColl->SetType(mfCurrentSize);
            mpColl->Delay(0);

            cCollisionList *lpList=_COLLISION_HANDLER->GenerateCollisionList(mpColl,MISSILE_FILTER);
            cProcess *lpProc=lpList->NextCollisionP();
            if(lpProc)
            {
                lpProc->UserSignal(BEAM_COLLISION,0);
            }
         }
         else
         {
            _KILL_THIS();
            return;
         }
        }
        mfDelay-=0.04f;
    };

    void cChaffCharge::Stop()
    {
        _KILL(mpCharge);
        mpCharge=0;
    };

void cChaffCharge::ActivateChaff(cChaffSettings *lpSettings)
{
 for(uint16 liCount=lpSettings->miCharges;liCount;--liCount)
 {
     _CREATE(cChaffCharge(lpSettings));
 }
};

void cMissile::ChaffCheck()
{
    if(spChaffDeployed)
    {
        float lfCheck=mpHull->YawToPoint(spChaffDeployed->mpCharge->Position());
        if(fabs(lfCheck)<WT_PI/2) {if(mbTracking){mf180Delay=MISSILE_CHAFF_DELAY; mbTracking=false;}}

        lfCheck=mpHull->PitchToPoint(spChaffDeployed->mpCharge->Position());
        if(fabs(lfCheck)<WT_PI/2) {if(mbTracking){mf180Delay=MISSILE_CHAFF_DELAY; mbTracking=false;}}
    }
}

cMWMissile::cMWMissile(cMWMissileSettings *lpSettings) : cMissile(lpSettings)
{
    miMunitions=lpSettings->miMunitions;
    mfSpread=lpSettings->mfSpread;
    mpMunitions=lpSettings->mpMunitionSettings;
}

void cMWMissile::Detonate()
{
    //Find Random perpendicular vector
    c3DVf lfX(mpHull->mmCache.XVect());
    c3DVf lfY(mpHull->mmCache.YVect());
    c3DVf lfZ(mpHull->mmCache.ZVect());
    float lfAngle=2*WT_PI/miMunitions;

    mpMunitions->mpTarget=mpTarget;

    cMatrix4 TempMat;

    for(uint8 liCount=0;liCount<miMunitions;++liCount)
    {
        TempMat[0]=lfZ[0];
        TempMat[1]=lfZ[1];
        TempMat[2]=lfZ[2];

        c3DVf TempVect=lfX*cos(lfAngle*liCount)-lfY*sin(lfAngle*liCount);
        TempMat[4]=TempVect[0];
        TempMat[5]=TempVect[1];
        TempMat[6]=TempVect[2];

        TempVect=lfY*cos(lfAngle*liCount)+lfX*sin(lfAngle*liCount);
        TempMat[8]=TempVect[0];
        TempMat[9]=TempVect[1];
        TempMat[10]=TempVect[2];

        TempMat[12]=mpHull->mmCache[12];
        TempMat[13]=mpHull->mmCache[13];
        TempMat[14]=mpHull->mmCache[14];

        TempMat.RotateY(WT_PI/2-mfSpread);

        mpMunitions->mpMatrix=&TempMat;
         switch(mpMunitions->Type())
            {
                case MISSILE_TYPE_EXPLOSIVE:
                {
                        _CREATE(cExplosiveMissile(dynamic_cast<cExplosiveMissileSettings*>(mpMunitions)));
                }break;
                case MISSILE_TYPE_LASER:
                {
                        _CREATE(cLaserMissile(dynamic_cast<cLaserMissileSettings*>(mpMunitions)));

                }break;
                case MISSILE_TYPE_EMP:
                {
                        _CREATE(cEMPMissile(dynamic_cast<cEMPMissileSettings*>(mpMunitions)));
                }break;
                case MISSILE_TYPE_CHAFF:
                {
                        cChaffCharge::ActivateChaff(dynamic_cast<cChaffSettings*>(mpMunitions));
                }break;
                case MISSILE_TYPE_MW:
                {
                        _CREATE(cMWMissile(dynamic_cast<cMWMissileSettings*>(mpMunitions)));
                }break;
            };
            TargetMunition();
    }
};

void cMWMissile::TargetMunition()
{

};

cMWMissileScatter::cMWMissileScatter(cMWMissileSettings *lpSettings) : cMWMissile(lpSettings)
{

}

void cMWMissileScatter::TargetMunition()
{
    mpMunitions->mpTarget.SetTarget(_KERNEL->FindProcess<cLeviathanComponent>(mpMunitions->mpTarget.mpComponent));
};
