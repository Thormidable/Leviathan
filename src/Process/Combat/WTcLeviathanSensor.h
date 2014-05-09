#ifndef __WTCLEVIATHANSENSOR_H__
#define __WTCLEVIATHANSENSOR_H__

class cLeviathanSensor : public cLeviathanComponent
{

 float mfMaxSensorDegredation;
 float mfSensorDegredation;
 float mfSensorBaseDegredation;
 cModel *mpHull;

 float mfDegredation;
public:
	cLeviathanSensor(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseDegredation,float lfSensorMaxDegredation);
	cLeviathanSensor(cLeviathanSensorSettings *lpSettings);

	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

    void ReduceHealth();

};



#endif
