#include "stdafx.h"
#include "../../main.h"

cLeviathanRepairSettings::cLeviathanRepairSettings(cLeviathanComponentSettings *lpSettings,string lsMesh, string lsCollision,float lfRepairRate,double lfRepairLimit) : cLeviathanComponentSettings(lpSettings)
{
    mpMesh=_GET_MESH_FILE(lsMesh.c_str());
    mpCollision=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
	mfRepairRate=lfRepairRate;
	mfRepairLimit=lfRepairLimit;
};

cLeviathanRepairSettings::cLeviathanRepairSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh, string lsCollision,float lfRepairRate,double lfRepairLimit) : cLeviathanComponentSettings(lpSettings)
{
    mpMesh=_GET_MESH_FILE(lsMesh.c_str());
    mpCollision=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
	mfRepairRate=lfRepairRate;
	mfRepairLimit=lfRepairLimit;
};

uint8 cLeviathanRepairSettings::Type(){return LV_REPAIR;};
cLeviathanRepairSettings *cLeviathanRepairSettings::Repair(){return this;};

