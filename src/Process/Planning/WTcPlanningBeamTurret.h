#ifndef __WTCPLANNINGBEAMTURRET_H__
#define __WTCPLANNINGBEAMTURRET_H__

class cPlanningBeamTurret : public cPlanningTurret
{
    cComponentTextField<float> mcDelay;
    cComponentTextField<float> mcDamage;
    cComponentTextField<float> mcROF;

public:
    cPlanningBeamTurret(cLeviathanBeamTurretSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();

};

/*

class cPlanningBeamTurret : public cPlanningComponent
{
    cNodeList *mpBeamTurret;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcDelay;
    cComponentTextField<float> mcTrackingSpeed;
    cComponentTextField<float> mcDamage;
    cComponentTextField<float> mcROF;
    cPlanningArcs mcArc;
    cPlanningArcs mcArcRange;

public:
    cPlanningBeamTurret(cLeviathanBeamTurretSettings *lpSettings);
    void DisplayOthers(c3DVf lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();

};
*/

#endif
