#ifndef __WTCCOMBATSCREEN_H__
#define __WTCCOMBATSCREEN_H__

class cPlanningScreen;

extern cCamera *gp2DCamera;
extern cCamera *gpClearCamera;


class cCombatScreen : public cProcess
{

    bool mbSoundKey;

public:

 cCombatScreen(cLeviathanSettings *mpLevSettings);
 void Run();
 void Stop();

};



#endif
