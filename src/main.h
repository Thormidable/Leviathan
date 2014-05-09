#ifndef __MAIN_H__
#define __MAIN_H__

#include "../../Bamboo/src/WTBamboo.h"

#include "./Settings/WTGameSettings.h"
#include "./Settings/WTcUserSettings.h"
#include "./Process/WTcPlannedSettings.h"

#include "./Process/WTcMapDisplay.h"

#include "./Process/Settings/WTcDamageSettings.h"
#include "./Process/Combat/WTcDamage.h"

#include "./Process/WTcShield.h"
#include "./Process/WTcBullet.h"
//#include "./Process/WTcMissile.h"
#include "./Process/WTcFighter.h"




//#include "./Process/WTcMessageFeed.h"


#include "./Process/Settings/WTcMissileSettings.h"
#include "./Process/Settings/WTcLeviathanGeneralSettings.h"
#include "./Process/Settings/WTcFoundationClassSettings.h"
#include "./Process/Settings/WTcLeviathanHullSettings.h"
#include "./Process/Settings/WTcLeviathanShieldSettings.h"
#include "./Process/Settings/WTcLeviathanTurretSettings.h"
#include "./Process/Settings/WTcLeviathanProjectileTurretSettings.h"
#include "./Process/Settings/WTcLeviathanBeamTurretSettings.h"
#include "./Process/Settings/WTcLeviathanMissileTurretSettings.h"
#include "./Process/Settings/WTcLeviathanTractorTurretSettings.h"
#include "./Process/Settings/WTcLeviathanSensorSettings.h"
#include "./Process/Settings/WTcLeviathanThrusterSettings.h"
#include "./Process/Settings/WTcLeviathanReactorSettings.h"
#include "./Process/Settings/WTcLeviathanCoolingVentsSettings.h"
#include "./Process/Settings/WTcLeviathanHullMultiHullSettings.h"
#include "./Process/Settings/WTcLeviathanRepairSettings.h"
#include "./Process/Settings/WTcLeviathanSettings.h"

#include "./Process/WTcPlayer.h"
#include "./Process/WTcCore.h"

#include "./Process/Combat/WTcFoundationTracking.h"
#include "./Process/Combat/WTcCombatScreen.h"
#include "./Process/Combat/WTcCombatStatusBox.h"
#include "./Process/Combat/WTcMissile.h"
#include "./Process/Combat/WTcLeviathanGeneral.h"
#include "./Process/Combat/WTcLeviathanHull.h"
#include "./Process/Combat/WTcLeviathanShield.h"
#include "./Process/Combat/WTcLeviathanTurret.h"
#include "./Process/Combat/WTcLeviathanProjectileTurret.h"
#include "./Process/Combat/WTcLeviathanBeamTurret.h"
#include "./Process/Combat/WTcLeviathanMissileTurret.h"
#include "./Process/Combat/WTcLeviathanTractorTurret.h"
#include "./Process/Combat/WTcLeviathanSensor.h"
#include "./Process/Combat/WTcLeviathanThruster.h"
#include "./Process/Combat/WTcLeviathanReactor.h"
#include "./Process/Combat/WTcLeviathanCoolingVents.h"
#include "./Process/Combat/WTcLeviathanHullMultiHull.h"
#include "./Process/Combat/WTcLeviathanRepair.h"
#include "./Process/Combat/WTcLeviathan.h"


#include "./Process/Leviathans/WTcTrainingLeviathan.h"
#include "./Process/Leviathans/WTcGunLeviathanMk1.h"
#include "./Process/Leviathans/WTcBeamLeviathanMk1.h"
#include "./Process/Leviathans/WTcMissileLeviathanMk1.h"
#include "./Process/SelectionScreen/WTcLeviathanSelectionMenu.h"


#include "./Process/Planning/WTcPlanningPlayerGun.h"
#include "./Process/Planning/WTcPlanningMissileRack.h"
#include "./Process/Planning/WTcPlanningComponentBox.h"
#include "./Process/Planning/WTcPlanningComponentTextField.h"
#include "./Process/Planning/WTcPlanningComponent.h"
#include "./Process/Planning/WTcPlanningLeviathan.h"
#include "./Process/Planning/WTcPlanningScreen.h"
#include "./Process/Planning/WTcPlanningHull.h"
#include "./Process/Planning/WTcPlanningReactor.h"
#include "./Process/Planning/WTcPlanningThruster.h"
#include "./Process/Planning/WTcPlanningSensor.h"
#include "./Process/Planning/WTcPlanningShield.h"
#include "./Process/Planning/WTcPlanningVent.h"
#include "./Process/Planning/WTcPlanningArcs.h"
#include "./Process/Planning/WTcPlanningTurret.h"
#include "./Process/Planning/WTcPlanningProjectileTurret.h"
#include "./Process/Planning/WTcPlanningBeamTurret.h"
#include "./Process/Planning/WTcPlanningTractorTurret.h"
#include "./Process/Planning/WTcPlanningMissileTurret.h"
#include "./Process/Planning/WTcPlanningRepair.h"


#include "./Process/WTcAsteroidObject.h"
#include "./Process/WTcExitScreen.h"

extern bool gbQuit;
extern cRenderObject *gpRenderCollision;
extern bool gbSoundOn;
#endif


