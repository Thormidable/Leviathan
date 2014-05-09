#ifndef __WTCCORE_H__
#define __WTCCORE_H__

class cPlanningScreen;

extern cCamera *gp2DCamera;
extern cCamera *gpClearCamera;

extern cStarMap *gpStarMap;

class cCore : public cProcess
{
//friend class cKernel;
 cFighter *lpFight[6];
 bool lbFight;
 cLandscape *mpTerrain;
 cLight *mpLight;
 cCamera *mpCamera2;
 cPlayer *mpPlayer;


 static cLeviathanSettings *mpLevSettings;
 static bool sbDead;



 void Run();
public:

 cCore();

 void Stop();

 static void Planning();
 static void Game();
 void Fighters();
 static void Asteroids();

 static cPlanningScreen *mpPlanScreen;
 static cText *mpDead;

 static cIcoSphere *mpIcoSphereBase;
 static cCircleLineData *mpCircleBase;
};



#endif
