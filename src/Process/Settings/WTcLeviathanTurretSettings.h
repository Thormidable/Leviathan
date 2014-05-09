#ifndef __WTCLEVIATHANTURRETSETTINGS_H__
#define __WTCLEVIATHANTURRETSETTINGS_H__

class cLeviathanTurretSettings : public cLeviathanComponentSettings
{
 public:
 cMeshTree *mpMesh;
 float mfTrackSpeed;
 float mfLowYaw;
 float mfHighYaw;
 float mfLowPitch;
 float mfHighPitch;
 float mfReloadRate;


 cLeviathanTurretSettings(cLeviathanComponentSettings *lpSettings,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate);

  cLeviathanTurretSettings(cLeviathanTurretSettings *lpSettings);
   cLeviathanTurretSettings(const cLeviathanComponentSettings &lpSettings,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate);

  cLeviathanTurretSettings(const cLeviathanTurretSettings &lpSettings);

  uint8 Type();
  cLeviathanTurretSettings *Turret();

  virtual float DisplayROF();
  virtual float DisplayTrackSpeed();
  virtual float DisplayDamage();

  virtual float Range();

};



#endif
