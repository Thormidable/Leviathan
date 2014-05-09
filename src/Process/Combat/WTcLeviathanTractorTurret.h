#ifndef __WTCLEVIATHANTRACTORTURRET_H__
#define __WTCLEVIATHANTRACTORTURRET_H__

class cLeviathanTractorBeam : public cLeviathanBeamTurret
{
public:
    cLeviathanTractorBeam(cLeviathanTurretSettings *lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor,float lfDampeningFactor);
    cLeviathanTractorBeam(const cLeviathanTurretSettings &lpSettings,float lfRange,float lfBeamRadius,float lfFireDelay,float lfRechargeRate,float lfDischargeRate,float lfFullRecharge,cRGBA lcBeamColor,float lfDampeningFactor);
    cLeviathanTractorBeam(cLeviathanTractorTurretSettings *lpSettings);
    void Run();


    void UpdateFieldColors(cCombatStatusBox *lpPoint);
	void Display(cCombatStatusBox *lpPoint);
};



#endif
