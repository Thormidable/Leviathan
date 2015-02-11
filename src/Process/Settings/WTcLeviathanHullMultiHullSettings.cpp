
#include "../../main.h"



cLeviathanMultiHullSettings::cLeviathanMultiHullSettings(cLeviathanComponentSettings *lpSettings,uint32 liComponents,string CoreMesh) : cLeviathanComponentSettings(lpSettings)
{
    mpCoreMesh=_GET_MESH_FILE(CoreMesh.c_str());
    miComponents=0;
    mpList=new cLeviathanMultiHullComponentSettings[liComponents];
}

cLeviathanMultiHullSettings::cLeviathanMultiHullSettings(const cLeviathanComponentSettings &lpSettings,uint32 liComponents,string CoreMesh) : cLeviathanComponentSettings(lpSettings)
{
    mpCoreMesh=_GET_MESH_FILE(CoreMesh.c_str());
    miComponents=0;
    mpList=new cLeviathanMultiHullComponentSettings[liComponents];
}


void cLeviathanMultiHullSettings::AddComponent(string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos)
{
    mpList[miComponents].mpMesh=_GET_MESH_FILE(Mesh.c_str());
    mpList[miComponents].mmPos.Equals(lpPos);
    mpList[miComponents].mpCollMesh=_GET_COLLISION_MESH_FILE(CollMesh.c_str());
    mpList[miComponents].mfStartHealth=lfHealth;
    ++miComponents;
};

void cLeviathanMultiHullSettings::SetComponent(uint32 liSlot,string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos)
{
    mpList[liSlot].mpMesh=_GET_MESH_FILE(Mesh.c_str());
    mpList[liSlot].mmPos.Equals(lpPos);
    mpList[liSlot].mpCollMesh=_GET_COLLISION_MESH_FILE(CollMesh.c_str());
    mpList[liSlot].mfStartHealth=lfHealth;
};


uint8 cLeviathanMultiHullSettings::Type(){return LV_MULTIHULL;};
cLeviathanMultiHullSettings *cLeviathanMultiHullSettings::MultiHull(){return this;};















