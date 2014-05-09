#include "stdafx.h"
#include "../main.h"



float cUserSettings::mfMouseThrustSensitivity=0.0f;
float cUserSettings::mfMouseXAngleSensitivity=1.0f;
float cUserSettings::mfMouseYAngleSensitivity=-1.0f;
float cUserSettings::mfPlanningLeviathanRotationSensitivity=0.06f;
bool cUserSettings::mbYawPitchControls=1;
bool cUserSettings::mbKeyThrustControl=1;


void cUserSettings::Settings()
{
WT_PAINTER_STARTING_SIZE=30;
_MATRIX_STACK_DEPTH=30;

WT_USE_PARENT_STACK=0;
WT_ALLOW_DYNAMIC_TEXTURES=1;
WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS=1;

WT_OPENGL_LIGHTS=8;

WT_COLLISION_HANDLER_TYPE=WT_COLLISION_HANDLER_TYPE_TYPE;
//WT_COLLISION_HANDLER_TYPE=WT_COLLISION_HANDLER_TYPE_BSP;
WT_COLLISION_DEFAULT_TYPE=WT_COLLISION_RADIUS;

WT_RAY_ANGLE_RANGE=0.05f;

WT_COLLISION_HANDLER_SIZE=8;

WT_COLLISION_HANDLER_DIMENSIONS=WT_COLLISION_HANDLER_DIMENSIONS_3D;
WT_COLLISION_SPACE_SIZE=1000.0f;
WT_COLLISION_DEPTH=10;

WT_MAX_PARTICLES=100;

WT_VERTEX_RANGE_CHECK_SIMILAR=0.1f;

WT_LANDSCAPE_TEXTURE_PERCENTAGE_SIZE=0.25f;
WT_STARTING_FRAMES_PER_SECOND=60;
WT_STARTING_PROCESSES_PER_FRAME=4;

WT_ENABLE_LOGGING=true;


};

void cUserSettings::UserWindowSizeUpdate()
{
  cPlanningScreen::UpdateWindow();
  if(gpPlayer) gpPlayer->mpTargetStatus->ResetPosition();
};

void cUserSettings::FileSettings()
{
    mfMouseThrustSensitivity=_GET_SETTINGS_FLOAT("MouseThrustControlFactor");
    mfMouseXAngleSensitivity=_GET_SETTINGS_FLOAT("MouseXAngleSensitivity");
    mfMouseYAngleSensitivity=_GET_SETTINGS_FLOAT("MouseYAngleSensitivity");
    mfPlanningLeviathanRotationSensitivity=_GET_SETTINGS_FLOAT("PlanningLeviathanRotationSensitivity");
    mbYawPitchControls=_GET_SETTINGS_INTEGER("YawPitchControls");
    mbKeyThrustControl=_GET_SETTINGS_INTEGER("KeyThrustControl");

};
