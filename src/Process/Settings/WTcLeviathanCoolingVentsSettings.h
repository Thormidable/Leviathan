#ifndef __WTCLEVIATHANCOOLINGVENTSETTINGS_H__
#define __WTCLEVIATHANCOOLINGVENTSETTINGS_H__

class cLeviathanVentSettings : public cLeviathanComponentSettings
{
  public:
        cLeviathanVentSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool);
        cLeviathanVentSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool);

    cMesh *mpVent;
    cMeshFileCollision *mpVentColl;
    float mfOpenAngle;
    float mfOpeningRate;
    float mfBaseCool,mfMaxCool;
    uint8 Type();
    cLeviathanVentSettings *Vent();
};
#endif
