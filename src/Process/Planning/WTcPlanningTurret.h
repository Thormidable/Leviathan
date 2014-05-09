#ifndef __WTCPLANNINGTURRET_H__
#define __WTCPLANNINGTURRET_H__

class cPlanningTurret : public cPlanningComponent
{
    cNodeList *mpTurret;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcTrackingSpeed;

    cPlanningArcs mcArc;
    cPlanningArcs mcArcRange;

public:
    cPlanningTurret(cLeviathanTurretSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

};

#endif
