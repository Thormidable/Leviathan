#ifndef __WTCLEVIATHANREPAIRSETTINGS_H__
#define __WTCLEVIATHANREPAIRSETTINGS_H__

class cLeviathanRepairSettings : public cLeviathanComponentSettings
{
  public:
        cLeviathanRepairSettings(cLeviathanComponentSettings *lpSettings,string lsMesh, string lsCollision,float lfRepairRate,double lfRepairLimit);
        cLeviathanRepairSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh, string lsCollision,float lfRepairRate,double lfRepairLimit);

		cMesh *mpMesh;
        cMeshCollision *mpCollision;

		float mfRepairLimit;
		float mfRepairRate;

        uint8 Type();
        cLeviathanRepairSettings *Repair();
};
#endif
