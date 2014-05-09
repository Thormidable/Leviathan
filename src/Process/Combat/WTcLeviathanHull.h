#ifndef __WTCLEVIATHANHULL_H__
#define __WTCLEVIATHANHULL_H__


class cLeviathanHull : public cLeviathanComponent
{
 cModel *mpHull;

public:
	cLeviathanHull(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision);
	cLeviathanHull(cLeviathanHullSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();

};



#endif
