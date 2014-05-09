#include "stdafx.h"
#include "../main.h"


cAsteroidObject::cAsteroidObject(uint32 liObjects)
{

	printf("Generating a Random Asteroid\n");

    //cAsteroid *lpMesh=new cAsteroid(60.0f,3,100.0f);
    float lfTemp=RANDOM_NUMBER;
    cAsteroid *lpMesh=new cAsteroid(6.0f+lfTemp*24.0f,3,20.0f+lfTemp*80.0f);
    //cAsteroid *lpMesh=new cAsteroid(60.0f,3,100.0f);
    cTBNVectors *lpTBN=new cTBNVectors(lpMesh);

    mpMapDisplays=new cMapDisplayObject*[liObjects];
    mpModel=new cModel*[liObjects];
    mpMomentum=new cMomentum*[liObjects];


miObjects=liObjects;
for(liObjects=0;liObjects<miObjects;++liObjects)
{
    mpModel[liObjects]=_CREATE(cModel);
    mpModel[liObjects]->Mesh(lpMesh);

    mpModel[liObjects]->Shader("NormalMappingProgram");
    mpModel[liObjects]->AddTexture("BricksNormalMap");
    mpModel[liObjects]->AddTexture("BricksColorMap");

    mpModel[liObjects]->SetVariable("Material_diffuse",cRGBA(1.0f,1.0f,1.0f,1.0f).Color());
 	mpModel[liObjects]->SetVariable("Material_ambient",cRGBA(0.2f,0.2f,0.2f,1.0f).Color());

 	lpTBN->LinkToShader(mpModel[liObjects]);

    mpModel[liObjects]->Position(ZEROED_RANDOM_NUMBER*4000.0f,ZEROED_RANDOM_NUMBER*4000.0f,8000.0f+ZEROED_RANDOM_NUMBER*4000.0f);
    mpModel[liObjects]->RotateX(ZEROED_RANDOM_NUMBER*WT_PI);
    mpModel[liObjects]->RotateY(ZEROED_RANDOM_NUMBER*WT_PI);
    mpModel[liObjects]->RotateZ(ZEROED_RANDOM_NUMBER*WT_PI);

    mpMomentum[liObjects]=new cMomentum(mpModel[liObjects]);
    mpMomentum[liObjects]->Thrust(ZEROED_RANDOM_NUMBER*100.0f,ZEROED_RANDOM_NUMBER*100.0f,ZEROED_RANDOM_NUMBER*100.0f);
    mpMomentum[liObjects]->ThrustAngle(150.0*ZEROED_RANDOM_NUMBER,150.0*ZEROED_RANDOM_NUMBER,150.0*ZEROED_RANDOM_NUMBER);

    mpMapDisplays[liObjects]=new cMapDisplayObject(mpModel[liObjects],cRGBA(0.5f,0.5f,0.5,0.5f),"AsteroidIcon");
}

};

void cAsteroidObject::Run()
{
    for(uint32 liObjects=0;liObjects<miObjects;++liObjects)
    {
     mpMomentum[liObjects]->Update();

    cMapDisplay::mpStaticThis->MapObject(mpMapDisplays[liObjects]);

    }
}


void cAsteroidObject::Stop()
{
    for(uint32 liObjects=0;liObjects<miObjects;++liObjects)
    {
     _KILL(mpModel[liObjects]);
     mpModel[liObjects]=0;
    }

    delete []mpModel;
    delete []mpMomentum;

}
