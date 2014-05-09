#ifndef __WTCLEVIATHANMULTIHULLSETTINGS_H__
#define __WTCLEVIATHANMULTIHULLSETTINGS_H__

class cLeviathanMultiHullComponentSettings
{
  public:
        cMesh *mpMesh;
        float mfStartHealth;
        cMeshFileCollision *mpCollMesh;
        cMatrix4 mmPos;
};

class cLeviathanMultiHullSettings : public cLeviathanComponentSettings
{
  public:
  cLeviathanMultiHullSettings(cLeviathanComponentSettings *lpSettings,uint32 liComponents,string CoreMesh="");
  cLeviathanMultiHullSettings(const cLeviathanComponentSettings &lpSettings,uint32 liComponents,string CoreMesh="");
        uint32 miComponents;
        cMesh *mpCoreMesh;
        cLeviathanMultiHullComponentSettings *mpList;

    void AddComponent(string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos);
    void SetComponent(uint32 liSlot,string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos);

    uint8 Type();
    cLeviathanMultiHullSettings *MultiHull();

};



#endif
