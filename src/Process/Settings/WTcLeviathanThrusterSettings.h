#ifndef __WTCLEVIATHANTHRUSTERSETTINGS_H__
#define __WTCLEVIATHANTHRUSTERSETTINGS_H__

class cLeviathanThrusterSettings : public cLeviathanComponentSettings
{
  public:
    cLeviathanThrusterSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit);
    cLeviathanThrusterSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit);

     cMesh *mpThruster;
     cMeshFileCollision *mpThrusterColl;
    float mfThrustLimit;

    float mfStartMaxThrust;
    float mfInvMaxHealth;

    uint8 Type();
    cLeviathanThrusterSettings *Thruster();
};

#endif
