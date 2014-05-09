#ifndef __WTCLEVIATHANCOOLINGVENT_H__
#define __WTCLEVIATHANCOOLINGVENT_H__

class cLeviathanVent : public cLeviathanComponent
{

 cModel *mpVent;
 float mfOpenAngle;
 float mfOpeningRate;
 uint8 miState;
 float mfBaseCool,mfMaxCool;
 vArmour *mpClosedArmour;
 static vArmour mcOpenArmour;
public:
	cLeviathanVent(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool);
	cLeviathanVent(cLeviathanVentSettings *lpSettings);
	void Run();
	void Stop();
	void Open();
	void Close();
	float Cooling();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

	void ReduceHealth();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);

};



#endif
