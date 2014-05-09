#ifndef __WTCLEVIATHANREPAIR_H__
#define __WTCLEVIATHANREPAIR_H__

class cLeviathanRepair : public cLeviathanComponent
{

 cModel *mpRepair;
 float mfRepairRate;
 float mfCurrentRepairRate;
 float mfRepairLimit;
 float mfInvLimit;

public:
	cLeviathanRepair(cLeviathanRepairSettings *lpSettings);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void *lpData);

	void ReduceHealth();

    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);

	void Repair(cLeviathanComponent *lpComp);

};



#endif
