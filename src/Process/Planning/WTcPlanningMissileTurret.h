#ifndef __WTCPLANNINGMISSILETURRET_H__
#define __WTCPLANNINGMISSILETURRET_H__

class cPlanningMissileTurret : public cPlanningTurret
{
    cComponentTextField<float> mcROF;
    cComponentTextField<string> mcMissileType;
    cComponentTextField<float> mcMobility;
    cComponentTextField<float> mcDamage;

public:
    cPlanningMissileTurret(cLeviathanMissileTurretSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();
};

#endif
