#ifndef __WTCLEVIATHANSENSORSETTINGS_H__
#define __WTCLEVIATHANSENSORSETTINGS_H__

class cLeviathanSensorSettings : public cLeviathanComponentSettings
{
  public:
        cLeviathanSensorSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorMaxDegredation);
        cLeviathanSensorSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorMaxDegredation);
        float mfMaxHealthInv;
        float mfMaxSensorDegredation;
        float mfSensorBaseDegredation;
        cMesh *mpHull;
        cMeshFileCollision *mpColl;

        uint8 Type();
    cLeviathanSensorSettings *Sensor();
};

#endif
