#ifndef __WTCPLANNINGPROJECTILETURRET_H__
#define __WTCPLANNINGPROJECTILETURRET_H__

class cPlanningProjectileTurret : public cPlanningTurret
{
    cComponentTextField<float> mcROF;
    cComponentTextField<float> mcSpeed;
    cComponentTextField<float> mcDamage;

public:
    cPlanningProjectileTurret(cLeviathanProjectileTurretSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();
};

#endif
