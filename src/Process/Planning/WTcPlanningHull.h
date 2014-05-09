#ifndef __WTCPLANNINGHULL_H__
#define __WTCPLANNINGHULL_H__

class cPlanningHull : public cPlanningComponent
{
    cModel *mpModel;
    cCollisionObject *mpColl;

public:
    cPlanningHull(cLeviathanHullSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();

    bool Hull();
};

#endif
