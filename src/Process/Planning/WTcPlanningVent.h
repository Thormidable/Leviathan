#ifndef __WTCPLANNINGVENT_H__
#define __WTCPLANNINGVENT_H__



class cPlanningVent : public cPlanningComponent
{
    cModel *mpVent;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcCooling;
    cComponentTextField<float> mcOpen;

public:
    cPlanningVent(cLeviathanVentSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();
};

#endif
