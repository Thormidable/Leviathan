
#include "../../main.h"

#define STAR_SIZE_BASE 200.0f
#define STAR_SIZE_VARIABLE 200.0f

#define PLANET_ORBIT_START 500.0f
#define PLANET_ORBIT_BASE 800.0f
#define PLANET_ORBIT_VARIANCE 800.0f

#define PLANET_SIZE_BASE 120.0f
#define PLANET_SIZE_VARIANCE 120.0f

#define MOON_ORBIT_START 150.0f
#define MOON_ORBIT_BASE 150.0f
#define MOON_ORBIT_VARIANCE 150.0f

#define MOON_SIZE_BASE 40.0f
#define MOON_SIZE_VARIANCE 40.0f


void cLeviathanArray::ResetForCombat()
{
	mpInstance=0;
	for(uint8 liCount=0;liCount<LEVIATHAN_SELECTION_ROWS;++liCount)
    {
        for(uint8 liLoop=0;liLoop<LEVIATHAN_SELECTION_COLUMNS;++liLoop)
        {
		 if(liCount!=miStarSystem && liLoop!=miPlanet) delete mpLeviathanArray[liCount][liLoop];
		 	//mpLeviathanArray[liCount][liLoop]=0;
        }
    }

    delete this;
};



void cLeviathanArray::GenerateGame()
{
    mpLeviathanArray[miStarSystem][miPlanet]->CreateData();
    _CREATE(cPlanningScreen(mpLeviathanArray[miStarSystem][miPlanet]));
};

uint8 cLeviathanArray::Planets(uint8 liType)
{
 uint8 liPlanets=0;
for(uint32 liCount=0;liCount<LEVIATHAN_SELECTION_COLUMNS;++liCount)
{
    if(mpLeviathanArray[liType][liCount]) ++liPlanets;
}
return liPlanets;
};


void cLeviathanArray::AddLeviathan(cLeviathanSettings *lpSettings)
{
    mpLeviathanArray[lpSettings->LeviathanType()][lpSettings->LeviathanLevel()]=lpSettings;
}

cLeviathanArray *cLeviathanArray::mpInstance=0;

cLeviathanArray *cLeviathanArray::Instance()
{
    if(!mpInstance) mpInstance=new cLeviathanArray;
    return mpInstance;
};

//void cLeviathanArray::(*mpFunctionPointer[LEVIATHAN_SELECTION_ROWS][LEVIATHAN_SELECTION_COLUMNS])();

cLeviathanArray::cLeviathanArray()
{
    _CAMERA->Far(10000.0f);
    _CAMERA->UpdateProjectionMatrix();
    miStarSystem=0;

     //Create a randomised Starmap for a background.
	gpStarMap=_CREATE(cStarMap(2500,_CAMERA));
    gpStarMap->Shader("StarCoronaProgram");

    float lfValue=0.7;
    gpStarMap->SetUniform("CoreScale",&lfValue);
    lfValue=0.5;
    gpStarMap->SetUniform("CameraMoveScale",&lfValue);
    lfValue=0.4;
    gpStarMap->SetUniform("CoronaScale",&lfValue);
    lfValue=2;
    gpStarMap->SetUniform("AlphaScale",&lfValue);
    lfValue=12;
    gpStarMap->SetUniform("CoronaDensity",&lfValue);
    gpStarMap->AddTexture("PerlinNoise");
    gpStarMap->Transparency(1);

    mpInstance=this;
    mpStarControl=0;
    Clear();
    Embody();
    StarMap();

    cCore::mpIcoSphereBase=new cIcoSphere(3,1.0f,1,0);
    cCore::mpCircleBase=new cCircleLineData(1.0f,100);
};


void cLeviathanArray::Clear()
{
    for(uint8 liCount=0;liCount<LEVIATHAN_SELECTION_ROWS;++liCount)
    {
        for(uint8 liLoop=0;liLoop<LEVIATHAN_SELECTION_COLUMNS;++liLoop)
        {
        mpLeviathanArray[liCount][liLoop]=0;
        }
    }
}

bool cLeviathanArray::Star(uint8 liStar)
{
        for(uint8 liLoop=0;liLoop<LEVIATHAN_SELECTION_COLUMNS;++liLoop)
        {
            if(mpLeviathanArray[liStar][liLoop]) return 1;
        }
        return 0;
};

bool cLeviathanArray::System(uint8 liType,uint8 liMk)
{
    return mpLeviathanArray[liType][liMk];
};

void cLeviathanArray::StarMap()
{
    mpStarControl=_CREATE(cLeviathanStarControl);
}

void cLeviathanArray::SolarSystemMap()
{
    mpSolarSystemControl=_CREATE(cLeviathanSolarSystemControl(mcStarColor,mcCoronaColor));
}

cLeviathanArray::~cLeviathanArray()
{


}

void cLeviathanArray::Embody()
{
    AddLeviathan(new cLeviathanSettingsTrainer);
    AddLeviathan(new cGunLeviathanMk1);
    AddLeviathan(new cBeamLeviathanMk1);
    AddLeviathan(new cMissileLeviathanMk1);
}

cLeviathanSettings *cLeviathanArray::Access(uint8 liSystem)
{
    uint8 liCount=0;
    while(liCount<LEVIATHAN_SELECTION_COLUMNS)
    {
        if(mpLeviathanArray[liSystem][liCount]) return mpLeviathanArray[liSystem][liCount];

        ++liCount;
    };
    return 0;
};
cLeviathanSettings *cLeviathanArray::Access(uint8 liSystem,uint8 liStar)
{
    return mpLeviathanArray[liSystem][liStar];
};

cLeviathanStarControl::cLeviathanStarControl()
{
    _CAMERA->Width(40.0f);
    _CAMERA->Height(30.0f);
    _CAMERA->UpdateProjectionMatrix();

    for(uint8 liCount=0;liCount<LEVIATHAN_SELECTION_ROWS;++liCount)
    {
        if(cLeviathanArray::Instance()->Star(liCount))
        {
            mpLeviathanStar[liCount]=_CREATE(cLeviathanStar(cLeviathanArray::Instance()->Access(liCount)->LeviathanTypeIcon()));
        }
        else mpLeviathanStar[liCount]=0;
    }
    miSelected=0;
    SelectUp();
};

void cLeviathanStarControl::SelectUp()
{
    mpLeviathanStar[miSelected]->mbSelected=false;
    bool lbLoop=false;
    do
    {
        ++miSelected;
        if(miSelected>=LEVIATHAN_SELECTION_ROWS)
        {
            miSelected=0;
            if(lbLoop) return;
            lbLoop=true;
        }
    }while(!mpLeviathanStar[miSelected]);

    mpLeviathanStar[miSelected]->mbSelected=true;
	_CAMERA->PointAt(mpLeviathanStar[miSelected]->mpStar->Position());
};

void cLeviathanStarControl::SelectDown()
{
    mpLeviathanStar[miSelected]->mbSelected=false;
  bool lbLoop=false;
    do
    {
        --miSelected;
        if(miSelected<0)
        {
            miSelected=LEVIATHAN_SELECTION_ROWS-1;
            if(lbLoop) return;
            lbLoop=true;
        }
    }while(!mpLeviathanStar[miSelected]);

    mpLeviathanStar[miSelected]->mbSelected=true;
	_CAMERA->PointAt(mpLeviathanStar[miSelected]->mpStar->Position());
};

void cLeviathanStarControl::Run()
{
    if(mpToggles[0].UpdateOnToggle(KEY_RIGHT)) SelectUp();
    if(mpToggles[1].UpdateOnToggle(KEY_LEFT)) SelectDown();
    _CAMERA->RotateY(_MOUSE->XSpeed()*0.06f);
    _CAMERA->RotateX(_MOUSE->YSpeed()*0.06f);

    if(KEY_ENTER)
    {
		cLeviathanArray::Instance()->mcStarColor=mpLeviathanStar[miSelected]->mcStarColor;
		cLeviathanArray::Instance()->mcCoronaColor=mpLeviathanStar[miSelected]->mcCoronaColor;
        _KILL(this);
        cLeviathanArray::Instance()->miStarSystem=miSelected;
        cLeviathanArray::Instance()->SolarSystemMap();
    }


};

void cLeviathanStarControl::Stop()
{
   for(uint8 liCount=0;liCount<LEVIATHAN_SELECTION_ROWS;++liCount)
    {
        if(mpLeviathanStar[liCount]) _KILL(mpLeviathanStar[liCount]);
    }
};


cLeviathanStar::cLeviathanStar(cTexture *lpLeviathanType)
{
    mpTypeIcon=_CREATE(cImage(gp2DCamera));
    mpTypeIcon->Shader("Image2DProgram");
    mpTypeIcon->AddTexture(lpLeviathanType);
    mpTypeIcon->Width(100.0f);
    mpTypeIcon->Height(100.0f);
    mpTypeIcon->Transparency(2);
    //mpTypeIcon->Priority(3.0f);

    mpOuterReticule=_CREATE(cImage(gp2DCamera));
    mpOuterReticule->Shader("Image2DProgram");
    mpOuterReticule->AddTexture("StarReticuleOuter");
    mpOuterReticule->Width(50.0f);
    mpOuterReticule->Height(50.0f);
    mpOuterReticule->Transparency(3);
    //mpOuterReticule->Priority(2.0f);

    mpInnerReticule=_CREATE(cImage(gp2DCamera));
    mpInnerReticule->Shader("Image2DProgram");
    mpInnerReticule->AddTexture("StarReticuleInner");
    mpInnerReticule->Width(50.0f);
    mpInnerReticule->Height(50.0f);
    mpInnerReticule->Transparency(3);
    //mpInnerReticule->Priority(2.0f);

    mpStar=_CREATE(cPoint);
    mpStar->Shader("SolarShaderProgram");
    mfFrame=30.0f;
    mpStar->SetUniform("Bb_Size",&mfFrame);
    mfFrame=0.0f;
    mpStar->SetUniformPointer("Frame",&mfFrame);
    mpStar->SetUniform("pParam",c4DVf(17,1,34,7).v);
    mcStarColor=cLeviathanArray::StarColor();
    mpStar->SetUniform("Bb_BaseColor",mcStarColor.Color());
    mcCoronaColor=cLeviathanArray::CoronaColor(mcStarColor);
    mpStar->SetUniform("Bb_CoronaColor",mcCoronaColor.Color());
    mpStar->Transparency(2);

    _CAMERA->PointAt(mpStar->Position());



    float lfDist=_CAMERA->Far()*0.9;

		float lfAngle[4];
		lfAngle[0]=RANDOM_NUMBER*2*3.1416;
		lfAngle[1]=RANDOM_NUMBER*2*3.1416;
		lfAngle[2]=sin(lfAngle[0]);
		lfAngle[3]=cos(lfAngle[1]);

		c3DVf lfVect;
		lfVect[0]=sin(lfAngle[0])*sin(lfAngle[1])*lfDist;
		lfVect[1]=cos(lfAngle[1])*lfDist;
		lfVect[2]=cos(lfAngle[0])*sin(lfAngle[1])*lfDist;



    mpStar->Position(lfVect.v);

    mpOuterReticule->Position(mpStar->GetScreenPosition().v);
    mpInnerReticule->Position(mpStar->GetScreenPosition().v);
    mpTypeIcon->Position(mpStar->GetScreenPosition().v);

    mbSelected=false;
};



void cLeviathanStar::Run()
{
    mfFrame+=0.0004f;
    if(mbSelected)
    {
        mpOuterReticule->RotateZ(-0.01f);
        mpInnerReticule->RotateZ(0.01f);
        if(KEY_SPACE)
        {
            _CAMERA->PointAt(mpStar->mmCache.Position());
        }
    }

    c3DVf lfTemp=mpStar->GetScreenPosition();
    if(lfTemp[2]>0.0f)
    {
        _WAKE(mpOuterReticule); mpOuterReticule->Position(lfTemp.v);
        _WAKE(mpInnerReticule); mpInnerReticule->Position(lfTemp.v);
        lfTemp[0]+=50.0f;
        lfTemp[1]+=50.0f;
        _WAKE(mpTypeIcon); mpTypeIcon->Position(lfTemp.v);
    }
    else
    {
        _SLEEP(mpOuterReticule);
        _SLEEP(mpInnerReticule);
        _SLEEP(mpTypeIcon);
    }

};


void cLeviathanStar::Stop()
{
    _KILL(mpOuterReticule);
    _KILL(mpInnerReticule);
    _KILL(mpStar);
    _KILL(mpTypeIcon);
};























































void cLeviathanSolarSystemControl::SelectUp()
{
    mpPlanets[miSelected]->mbSelected=false;
    bool lbLoop=false;
    do
    {
        ++miSelected;
        if(miSelected>=miPlanets)
        {
            miSelected=0;
            if(lbLoop) return;
            lbLoop=true;
        }
    }while(!mpPlanets[miSelected]);

    mpPlanets[miSelected]->mbSelected=true;
};

void cLeviathanSolarSystemControl::SelectDown()
{
    mpPlanets[miSelected]->mbSelected=false;
  bool lbLoop=false;
    do
    {
        --miSelected;
        if(miSelected<0)
        {
            miSelected=miPlanets-1;
            if(lbLoop) return;
            lbLoop=true;
        }
    }while(!mpPlanets[miSelected]);

    mpPlanets[miSelected]->mbSelected=true;
};


cLeviathanSolarSystemControl::cLeviathanSolarSystemControl(cRGBA lcStarCol,cRGBA lcCoronaCol)
{
    mpCentre=_CREATE(cRenderNode);
    mpCentre->Position(0.0f,0.0f,4000.0f);
	_CAMERA->Proportional(1);
	_CAMERA->Width(40.0f);
    _CAMERA->Height(30.0f);
    _CAMERA->UpdateProjectionMatrix();
	_CAMERA->ViewportProportional(0.0,0.0,1.0,1.0);
	_CAMERA->UpdateProjectionMatrix();

    _CAMERA->Position(0.0f,1000.0f,0.0f);
    _CAMERA->PointAt(mpCentre->Position());


    mpStar=_CREATE(cPoint);
    mpStar->Shader("SolarShaderProgram");
    mfFrame=STAR_SIZE_BASE+STAR_SIZE_VARIABLE*RANDOM_NUMBER;
    mpStar->SetUniform("Bb_Size",&mfFrame);
    mfFrame=0.0f;
    mpStar->SetUniformPointer("Frame",&mfFrame);
    mpStar->SetUniform("pParam",c4DVf(17,1,34,7).v);
	
    mpStar->SetUniform("Bb_BaseColor",lcStarCol.Color());
    lcStarCol=cLeviathanArray::CoronaColor(lcStarCol);
    mpStar->SetUniform("Bb_CoronaColor",lcCoronaCol.Color());
    mpStar->Position(mpCentre->Position());
    mpStar->Transparency(2);
	
    mpLight=_CREATE(cLight);
	mpLight->Ambient(0.2f,0.2f,0.2f,1.0f);
	mpLight->Specular(1.0f,1.0f,1.0f,1.0f);
	mpLight->Diffuse(1.0f,1.0f,1.0f,1.0f);
	mpLight->Position(mpCentre->Position());


    miSystem=cLeviathanArray::Instance()->miStarSystem;
    miPlanets=cLeviathanArray::Instance()->Planets(miSystem);

    mpPlanets=new cLeviathanPlanet*[miPlanets];
    float lfDist=PLANET_ORBIT_START;
    for(uint32 liCount=0;liCount<miPlanets;++liCount)
    {
        lfDist+=PLANET_ORBIT_BASE+RANDOM_NUMBER*PLANET_ORBIT_VARIANCE;
        mpPlanets[liCount]=_CREATE(cLeviathanPlanet(mpCentre,lfDist));

    }




    mbEnterKey=true;
	mbBackKey=true;

    miSelected=0;
    SelectUp();

}


void cLeviathanSolarSystemControl::Run()
{
	
	mfFrame+=0.0004f;

	_CAMERA->RotateY(_MOUSE->XSpeed()*0.6f*_TIME_PER_FRAME);
	_CAMERA->RotateX(_MOUSE->YSpeed()*0.6f*_TIME_PER_FRAME);

	if(KEY_ENTER)
	{
	if(!mbEnterKey)
	{
	_KILL(this);
	cLeviathanArray::Instance()->miPlanet=miSelected;
	cLeviathanArray::Instance()->GenerateGame();
	}
	}
	else{mbEnterKey=false;}

	if(KEY_BACKSPACE)
	{
	if(!mbBackKey)
	{
	_KILL(this);
	cLeviathanArray::Instance()->StarMap();
	}
	}
	else{mbBackKey=false;}

	if(KEY_SPACE)
	{
	_CAMERA->PointAt(mpCentre->Position());
	}

	if(mpToggles[0].UpdateOnToggle(KEY_LEFT)) SelectUp();
	if(mpToggles[1].UpdateOnToggle(KEY_RIGHT)) SelectDown();

}

void cLeviathanSolarSystemControl::Stop()
{
 _KILL(mpCentre);
 _KILL(mpStar);
 for(uint32 liCount=0;liCount<miPlanets;++liCount) _KILL(mpPlanets[liCount]);
 _KILL(mpLight);
}

cLeviathanPlanet::cLeviathanPlanet(cRenderNode *lpNode,float lfDist)
{
    mpCentre=_CREATE(cRenderNode(lpNode));
    mpCentre->RotateY(RANDOM_NUMBER*WT_PI*2);
	
    mpPlanet=_CREATE(cModel(mpCentre));
    mpPlanet->Shader("NormalMappingProgram");
    mpPlanet->AddTexture("PerlinNoise");
    mpPlanet->AddTexture("PerlinNoise");
    
	cIcoSphere *lpTemp=_CREATE(cIcoSphere(cCore::mpIcoSphereBase));
	mpPlanet->Mesh(lpTemp);  
	lpTemp->Radius(PLANET_SIZE_BASE+PLANET_SIZE_VARIANCE*RANDOM_NUMBER);

    mpPlanet->Position(0.0f,0.0f,lfDist);

    mpPlanet->SetVariable("Material_diffuse",cRGBA(0.8f,0.8f,0.8f,1.0f).Color());
 	mpPlanet->SetVariable("Material_ambient",cRGBA(0.2f,0.2f,0.2f,1.0f).Color());

 	cTBNVectors *lpTBN=new cTBNVectors(lpTemp);
 	lpTBN->LinkToShader(mpPlanet);

    mfPlanetOrbitSpeed=RANDOM_NUMBER*0.01f+0.005f;
    mfPlanetRotateSpeed=RANDOM_NUMBER*0.04f+0.02f;


    cLineArray *lpOrbit=_CREATE(cLineArray(mpCentre));
  //  lpOrbit->Shader("SetUniformColorProgram");
  //  lpOrbit->SetUniform("ModelColor",cRGBA(0.0f,0.6f,0.0f,1.0f).Color());
 //   lpOrbit->Data(_CREATE(cCircleLineData(lfDist)));
	//lpOrbit->Position(0.0f,-400.0f,0.0f);
	//lpOrbit->Width(2.0f);

	//cLine *lpLine=_CREATE(cLine(mpCentre));
	//lpLine->Shader("SetUniformColorProgram");
 //   lpLine->SetUniform("ModelColor",cRGBA(0.0f,0.6f,0.0f,1.0f).Color());
	//lpLine->Position(0.0f,0.0f,lfDist);
	//lpLine->Vector(0.0f,-400.0f,0.0f);
	//lpLine->Width(2.0f);


    mpCursor=_CREATE(cImage(gp2DCamera));
    mpCursor->Shader("Image2DProgram");
    mpCursor->AddTexture("StarReticuleOuter");
    mpCursor->Width(50.0f);
    mpCursor->Height(50.0f);
    mpCursor->Transparency(12);
    //mpCursor->Priority(3.0f);




	miMoons=RANDOM_NUMBER*2;
	++miMoons;
	mpMoons=new cRenderNode*[miMoons];
	mpMoonSpeeds=new float[miMoons];
	mpMoonModels=new cIcoSphere*[miMoons];
	float lfMoonDist=0.0f;
	for(uint8 liCount=0;liCount<miMoons;++liCount)
	{
		mpMoons[liCount]=_CREATE(cRenderNode(mpCentre));

		mpMoons[liCount]->Position(0.0f,0.0f,lfDist);
		mpMoons[liCount]->RotateY(RANDOM_NUMBER*WT_PI*2);

		cModel *lpMoon=_CREATE(cModel(mpMoons[liCount]));
		lpMoon->Shader("NormalMappingProgram");
		lpMoon->AddTexture("PerlinNoise");
		lpMoon->AddTexture("PerlinNoise");
		mpMoonModels[liCount]=_CREATE(cIcoSphere(cCore::mpIcoSphereBase));
		mpMoonModels[liCount]->Radius(MOON_SIZE_BASE+MOON_SIZE_VARIANCE*RANDOM_NUMBER);
		lpMoon->Mesh(mpMoonModels[liCount]);

		lpMoon->SetVariable("Material_diffuse",cRGBA(0.8f,0.8f,0.8f,1.0f).Color());
		lpMoon->SetVariable("Material_ambient",cRGBA(0.2f,0.2f,0.2f,1.0f).Color());

		cTBNVectors *lpTBN=new cTBNVectors(mpMoonModels[liCount]);
		lpTBN->LinkToShader(lpMoon);

		mpMoonSpeeds[liCount]=RANDOM_NUMBER*0.003f+0.003f;

		lfMoonDist+=MOON_ORBIT_BASE+RANDOM_NUMBER*MOON_ORBIT_VARIANCE;
		lpMoon->Position(0.0f,0.0f,lfMoonDist);

		//lpLine=_CREATE(cLine(mpMoons[liCount]));
		//lpLine->Shader("SetUniformColorProgram");
		//lpLine->SetUniform("ModelColor",cRGBA(0.0f,0.6f,0.0f,1.0f).Color());
		//lpLine->Position(0.0f,0.0f,lfMoonDist);
		//lpLine->Vector(0.0f,-400.0f,0.0f);
		//lpLine->Width(2.0f);

		//lpOrbit=_CREATE(cLineArray(mpMoons[liCount]));
		//lpOrbit->Shader("SetUniformColorProgram");
		//lpOrbit->SetUniform("ModelColor",cRGBA(0.0f,0.6f,0.0f,1.0f).Color());
		//lpOrbit->Data(_CREATE(cCircleLineData(lfMoonDist)));
		//lpOrbit->Position(0.0f,-400.0f,0.0f);
		//lpOrbit->Width(2.0f);

	}

   //mbSelected=false;

}



void cLeviathanPlanet::Run()
{

    mpCentre->RotateY(mfPlanetOrbitSpeed*_TIME_PER_FRAME);
    mpPlanet->RotateY(mfPlanetRotateSpeed*_TIME_PER_FRAME);
    for(uint8 liCount=0;liCount<miMoons;++liCount)
    {
        mpMoons[liCount]->RotateY(mpMoonSpeeds[liCount]*_TIME_PER_FRAME);
    }


    if(mbSelected)
    {

        c3DVf lfTemp=mpPlanet->GetScreenPosition();
		//c3DVf lfTemp(0.0,0.0,0.0);
        if(lfTemp[2]>0.0f) 
		{
			_WAKE(mpCursor); mpCursor->Position(lfTemp.v);
		}
        else 
		{
			_SLEEP(mpCursor);
		}
    }
    else {_SLEEP(mpCursor);}
}




void cLeviathanPlanet::Stop()
{
 _KILL(mpCentre);
 delete []mpMoons;
 delete []mpMoonSpeeds;
for(uint8 liCount=0;liCount<miMoons;++liCount)
{
	_KILL(mpMoonModels[liCount]);
	mpMoonModels[liCount]=0;
}

delete []mpMoonModels;

 _KILL(mpCursor);
}


cRGBA cLeviathanArray::StarColor()
{
    cRGBA lfColor;
    lfColor[0]=RANDOM_NUMBER*0.6+0.2;
    lfColor[1]=RANDOM_NUMBER*0.6+0.2;
    lfColor[2]=RANDOM_NUMBER*0.6+0.2;
    lfColor[3]=1.0f;

    return lfColor;
}

cRGBA cLeviathanArray::CoronaColor(cRGBA lcBase)
{
    cRGBA lfColor;
    lfColor[0]=lcBase[0]*RANDOM_NUMBER*0.3+1.0;
    lfColor[1]=lcBase[1]*RANDOM_NUMBER*0.3+1.0;
    lfColor[2]=lcBase[2]*RANDOM_NUMBER*0.3+1.0;
    lfColor[3]=lcBase[3]*1.0;

    return lfColor;
}
