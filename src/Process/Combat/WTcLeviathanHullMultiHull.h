#ifndef __WTCLEVIATHANMULTIHULL_H__
#define __WTCLEVIATHANMULTIHULL_H__

class cLeviathanMultiHullComponent
{
public:
    cModel *mpHull;
    float mfHealth;

    cLeviathanMultiHullComponent();


};

class cLeviathanMultiHull : public cLeviathanComponent
{
 cLeviathanMultiHullComponent *mpList;
 cModel *mpCoreMesh;
 uint32 miComponents;
public:
	cLeviathanMultiHull(cLeviathanComponentSettings *lpSettings,uint32 liComponents,string CoreMesh="");
	cLeviathanMultiHull(cLeviathanMultiHullSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);
    void AddComponent(string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos);
    void AddComponent(cLeviathanMultiHullComponentSettings &lpSettings);
    void SetComponent(uint32 liSlot,string Mesh, string CollMesh,float lfHealth,cMatrix4 *lpPos);
    void ReduceHealth();

};



#endif
