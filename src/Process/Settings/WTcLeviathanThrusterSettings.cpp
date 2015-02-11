
#include "../../main.h"


cLeviathanThrusterSettings::cLeviathanThrusterSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit) : cLeviathanComponentSettings(lpSettings)
{
        mpThruster=_GET_MESH_FILE(lsMesh.c_str());
        mpThrusterColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfInvMaxHealth=1.0f/mfHealth;
		 mfStartMaxThrust=lfMaxThrust;
		 mfThrustLimit=lfThrustLimit;

};

cLeviathanThrusterSettings::cLeviathanThrusterSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit) : cLeviathanComponentSettings(lpSettings)
{
        mpThruster=_GET_MESH_FILE(lsMesh.c_str());
        mpThrusterColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfInvMaxHealth=1.0f/mfHealth;
		 mfStartMaxThrust=lfMaxThrust;
		 mfThrustLimit=lfThrustLimit;

};

uint8 cLeviathanThrusterSettings::Type(){return LV_THRUSTERS;};
cLeviathanThrusterSettings *cLeviathanThrusterSettings::Thruster(){return this;};


