#ifndef __WTCPLANNINGSCREEN_H__
#define __WTCPLANNINGSCREEN_H__

class cPlanningScreen : public cProcess
{
    cPlanningLeviathan *mpLev;
	cButton *mpButton;
	cPlanningMissileRack *mpRack;
	cPlayerGun *mpPlayerGun;

	cLeviathanSettings *mpLeviathanSettings;


    public:
        static cMessageFeed *mpFeed;
        cPlanningScreen(cLeviathanSettings *lpSettings);
        void Run();
        void Stop();

        static void UpdateWindow();
};

#endif
