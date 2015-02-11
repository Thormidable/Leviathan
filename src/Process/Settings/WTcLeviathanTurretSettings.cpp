
#include "../../main.h"


cLeviathanTurretSettings::cLeviathanTurretSettings(cLeviathanComponentSettings *lpSettings,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate) : cLeviathanComponentSettings(lpSettings)
 {
    mpMesh=_GET_MODELLIST_FILE(lsMeshTree.c_str());
     mfTrackSpeed=lfTrackSpeed;
     mfLowPitch=lfLowPitch;
     mfLowYaw=lfLowYaw;
     mfHighPitch=lfHighPitch;
     mfHighYaw=lfHighYaw;
     mfReloadRate=lfReloadRate;
 };

  cLeviathanTurretSettings::cLeviathanTurretSettings(cLeviathanTurretSettings *lpSettings) : cLeviathanComponentSettings(lpSettings)
  {
     mpMesh=lpSettings->mpMesh;
     mfTrackSpeed=lpSettings->mfTrackSpeed;
     mfLowPitch=lpSettings->mfLowPitch;
     mfLowYaw=lpSettings->mfLowYaw;
     mfHighPitch=lpSettings->mfHighPitch;
     mfHighYaw=lpSettings->mfHighYaw;
     mfReloadRate=lpSettings->mfReloadRate;
  };

  cLeviathanTurretSettings::cLeviathanTurretSettings(const cLeviathanComponentSettings &lpSettings,
 string lsMeshTree,
 float lfTrackSpeed,
 float lfLowYaw,
 float lfHighYaw,
 float lfLowPitch,
 float lfHighPitch,
 float lfReloadRate) : cLeviathanComponentSettings(lpSettings)
 {
    mpMesh=_GET_MODELLIST_FILE(lsMeshTree.c_str());
     mfTrackSpeed=lfTrackSpeed;
     mfLowPitch=lfLowPitch;
     mfLowYaw=lfLowYaw;
     mfHighPitch=lfHighPitch;
     mfHighYaw=lfHighYaw;
     mfReloadRate=lfReloadRate;
 };

  cLeviathanTurretSettings::cLeviathanTurretSettings(const cLeviathanTurretSettings &lpSettings) : cLeviathanComponentSettings(lpSettings)
  {
     mpMesh=lpSettings.mpMesh;
     mfTrackSpeed=lpSettings.mfTrackSpeed;
     mfLowPitch=lpSettings.mfLowPitch;
     mfLowYaw=lpSettings.mfLowYaw;
     mfHighPitch=lpSettings.mfHighPitch;
     mfHighYaw=lpSettings.mfHighYaw;
     mfReloadRate=lpSettings.mfReloadRate;
  };


uint8 cLeviathanTurretSettings::Type(){return LV_TURRET_VOID;};
cLeviathanTurretSettings *cLeviathanTurretSettings::Turret(){return this;};

float cLeviathanTurretSettings::DisplayTrackSpeed(){return 480.0f*WT_PI*mfTrackSpeed;};
float cLeviathanTurretSettings::DisplayROF(){return 240.0f*mfReloadRate;};
float cLeviathanTurretSettings::DisplayDamage(){return 0.0f;};

float cLeviathanTurretSettings::Range()
{
    return 500.0f;
};
