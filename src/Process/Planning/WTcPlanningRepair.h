#ifndef __WTCPLANNINGREPAIR_H__
#define __WTCPLANNINGREPAIR_H__

class cPlanningRepair : public cPlanningComponent
{
    cModel *mpModel;
    cCollisionObject *mpColl;

	cComponentTextField<float> mcRepairLimit;
	cComponentTextField<float> mcRepairRate;

public:
    cPlanningRepair(cLeviathanRepairSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();

    cTexture *GetIcon();

};

#endif
