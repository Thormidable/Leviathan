#ifndef __WTCLEVIATHANGENERALSETTINGS_H__
#define __WTCLEVIATHANGENERALSETTINGS_H__

class cLeviathanHullSettings;
class cLeviathanVentSettings;
class cLeviathanMultiHullSettings;
class cLeviathanProjectileTurretSettings;
class cLeviathanMissileTurretSettings;
class cLeviathanBeamTurretSettings;
class cLeviathanSensorSettings;
class cLeviathanShieldSettings;
class cLeviathanThrusterSettings;
class cLeviathanReactorSettings;
class cLeviathanTurretSettings;
class cLeviathanTractorTurretSettings;
class cLeviathanRepairSettings;
class cFoundationSettingsList;

class cLeviathanComponentSettings
{
public:
    cLeviathanReactorSettings *mpReactor;

    cFoundationSettingsList *mpFoundations;

    float mfEnergyCost;
    float mfHealth;

    virtual uint8 Type();
    vRenderNode *mpNode;
    vArmourSettings *mpArmour;
    vRenderNode *Node();

virtual cLeviathanHullSettings* Hull(){return 0;};
virtual cLeviathanVentSettings* Vent(){return 0;};
virtual cLeviathanMultiHullSettings* MultiHull(){return 0;};
virtual cLeviathanProjectileTurretSettings* ProjectileTurret(){return 0;};
virtual cLeviathanMissileTurretSettings* MissileTurret(){return 0;};
virtual cLeviathanBeamTurretSettings* BeamTurret(){return 0;};
virtual cLeviathanSensorSettings* Sensor(){return 0;};
virtual cLeviathanShieldSettings* Shield(){return 0;};
virtual cLeviathanThrusterSettings* Thruster(){return 0;};
virtual cLeviathanReactorSettings* Reactor(){return 0;};
virtual cLeviathanTurretSettings* Turret(){return 0;};
virtual cLeviathanRepairSettings* Repair(){return 0;};
virtual cLeviathanTractorTurretSettings* TractorTurret(){return 0;};

    cLeviathanComponentSettings(float lfHealth,cFoundationSettingsList *lpList,vArmourSettings *lpArmour=0,cLeviathanReactorSettings *lpReactor=0,float mfEnergyCost=0.0f);
    cLeviathanComponentSettings(cLeviathanComponentSettings *lpSettings);
    cLeviathanComponentSettings(const cLeviathanComponentSettings &lpSettings);
    ~cLeviathanComponentSettings();
};

#endif
