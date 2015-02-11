
#include "../../main.h"

cLeviathanSensorSettings::cLeviathanSensorSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorDegredation) : cLeviathanComponentSettings(lpSettings)
{
         mpHull=_GET_MESH_FILE(lsMesh.c_str());
		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;
		 mfMaxSensorDegredation=lfSensorDegredation;
		 mfSensorBaseDegredation=lfBaseDegredation;

};

cLeviathanSensorSettings::cLeviathanSensorSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorDegredation) : cLeviathanComponentSettings(lpSettings)
{
         mpHull=_GET_MESH_FILE(lsMesh.c_str());
		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfMaxHealthInv=1.0f/mfHealth;
		 mfMaxSensorDegredation=lfSensorDegredation;
		 mfSensorBaseDegredation=lfBaseDegredation;

};

uint8 cLeviathanSensorSettings::Type(){return LV_SENSORS;};
cLeviathanSensorSettings *cLeviathanSensorSettings::Sensor(){return this;};
