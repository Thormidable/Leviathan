#ifndef __WTCLEVIATHANHULLSETTINGS_H__
#define __WTCLEVIATHANHULLSETTINGS_H__

class cLeviathanHullSettings : public cLeviathanComponentSettings
{
  public:
        cLeviathanHullSettings(cLeviathanComponentSettings *lpSettings,string lsMesh, string lsCollision);
        cLeviathanHullSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh, string lsCollision);
        cMesh *mpMesh;
        cMeshCollision *mpCollision;
        uint8 Type();
        cLeviathanHullSettings *Hull();
};
#endif
