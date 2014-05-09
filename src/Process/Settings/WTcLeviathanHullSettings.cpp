#include "stdafx.h"
#include "../../main.h"

cLeviathanHullSettings::cLeviathanHullSettings(cLeviathanComponentSettings *lpSettings,string lsMesh, string lsCollision) : cLeviathanComponentSettings(lpSettings)
{
    mpMesh=_GET_MESH_FILE(lsMesh.c_str());
    mpCollision=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
};

cLeviathanHullSettings::cLeviathanHullSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh, string lsCollision) : cLeviathanComponentSettings(lpSettings)
{
    mpMesh=_GET_MESH_FILE(lsMesh.c_str());
    mpCollision=_GET_COLLISION_MESH_FILE(lsCollision.c_str());
};

uint8 cLeviathanHullSettings::Type(){return LV_HULL;};
cLeviathanHullSettings *cLeviathanHullSettings::Hull(){return this;};

