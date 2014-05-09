#ifndef __WTCPLANNINGTRACTORTURRET_H__
#define __WTCPLANNINGTRACTORTURRET_H__

class cPlanningTractorTurret : public cPlanningTurret
{
    cComponentTextField<float> mcDelay;
    cComponentTextField<float> mcDamage;

public:
    cPlanningTractorTurret(cLeviathanTractorTurretSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();

};

#endif
