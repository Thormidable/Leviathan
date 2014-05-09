#ifndef __WTCPLANNINGTHRUSTER_H__
#define __WTCPLANNINGTHRUSTER_H__



class cPlanningThruster : public cPlanningComponent
{
    cModel *mpThruster;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcThrust;

public:
    cPlanningThruster(cLeviathanThrusterSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();
    cTexture *GetIcon();
};

#endif
