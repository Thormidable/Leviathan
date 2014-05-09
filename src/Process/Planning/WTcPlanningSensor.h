#ifndef __WTCPLANNINGSENSOR_H__
#define __WTCPLANNINGSENSOR_H__

class cPlanningSensor : public cPlanningComponent
{
    cModel *mpSensor;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcSensor;
    cComponentTextField<float> mcDegredationFactor;

public:
    cPlanningSensor(cLeviathanSensorSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();
    cTexture *GetIcon();
};

#endif
