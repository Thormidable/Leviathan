#ifndef __WTCLEVIATHANTHRUSTER_H__
#define __WTCLEVIATHANTHRUSTER_H__

class cLeviathanThruster : public cLeviathanComponent
{
 cModel *mpThruster;

 float mfThrustLimit;

 float mfMaxThrust;
 float mfStartMaxThrust;

public:
	cLeviathanThruster(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfMaxThrust,float lfThrustLimit);
	cLeviathanThruster(cLeviathanThrusterSettings *lpSettings);
	void Run();
	void Stop();
    void Thrust(float lfDesired);
    void Momentum(cMomentum *lpMomentum);
	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();

};



#endif
