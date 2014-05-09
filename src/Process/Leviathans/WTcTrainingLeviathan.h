#ifndef __WTCTRAININGLEVIATHAN_H__
#define __WTCTRAININGLEVIATHAN_H__

#define TRAIN_LEV_BULLET_SPEED 10.0f
#define TRAIN_LEV_BULLET_DAMAGE 10.0f
#define TRAIN_LEV_TRACK_SPEED 0.006f
#define TRAIN_LEV_BEAM_TRACK_SPEED 0.0004f
#define TRAIN_LEV_RELOAD_SPEED 0.04f
#define TRAIN_LEV_SENSORS 3
#define TRAIN_LEV_SENSORS_WORST 1.0f
#define TRAIN_LEV_MAX_THRUST 0.02f
//#define TRAIN_LEV_MAX_THRUST 0.0f
#define TRAIN_LEV_THRUST_LIMIT 1000.0f
#define ANGLE_THRUST_FACTOR 0.003f
#define REACTOR_MAX 1000.0f
#define REACTOR_VENT REACTOR_MAX*0.5f
#define MAX_ENERGY 1000.0f
#define REACTOR_DEATH_DAMAGE_RATE 0.4f
#define LEVIATHAN_BEAM_DAMAGE_FACTOR 0.4f

#define LV_TRAIN_REACTOR 0
#define LV_TRAIN_COREBULGE 1
#define LV_TRAIN_REARBEAM 2
#define LV_TRAIN_HULL_VERTICAL 3
#define LV_TRAIN_BRIDGE_BASE 4
#define LV_TRAIN_RADAR_MOUNT 5

class cLeviathanSettingsTrainer : public cLeviathanSettings
{
public:
    void CreateData();

  string LeviathanName();
  uint8 LeviathanLevel();
  uint32 LeviathanType();
  cTexture *LeviathanTypeIcon();
};

#endif
