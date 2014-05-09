cmake_minimum_required(VERSION 2.6)
project (Leviathon)
#This is release mode only.
#add_definitions (-W -Wall -O3)

#this is debug mode only.
add_definitions (-W -Wall -g -ggdb -O0 -m32)


set( Sources main.cpp )
set( Sources ${Sources} ./Settings/WTcUserSettings.cpp )

set( Sources ${Sources} ./Process/WTcMapDisplay.cpp )

set( Sources ${Sources} ./Process/WTcShield.cpp )
set( Sources ${Sources} ./Process/WTcBullet.cpp )

set( Sources ${Sources} ./Process/Settings/WTcDamageSettings.cpp )
set( Sources ${Sources} ./Process/Combat/WTcDamage.cpp )

set( Sources ${Sources} ./Process/WTcFighter.cpp )
set( Sources ${Sources} ./Process/WTcPlayer.cpp )
set( Sources ${Sources} ./Process/WTcCore.cpp )
set( Sources ${Sources} ./Process/WTcPlannedSettings.cpp )
set( Sources ${Sources} ./Process/SelectionScreen/WTcLeviathanSelectionMenu.cpp )

set( Sources ${Sources} ./Process/WTcMessageFeed.cpp )

set( Sources ${Sources} ./Process/Settings/WTcMissileSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanGeneralSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanHullSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanShieldSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanTurretSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanProjectileTurretSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanBeamTurretSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanMissileTurretSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanTractorTurretSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanSensorSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanThrusterSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanReactorSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanCoolingVentsSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanHullMultiHullSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanRepairSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcLeviathanSettings.cpp )
set( Sources ${Sources} ./Process/Settings/WTcFoundationClassSettings.cpp )


set( Sources ${Sources} ./Process/Combat/WTcFoundationTracking.cpp )
set( Sources ${Sources} ./Process/Combat/WTcCombatScreen.cpp )
set( Sources ${Sources} ./Process/Combat/WTcCombatStatusBox.cpp )
set( Sources ${Sources} ./Process/Combat/WTcMissile.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanGeneral.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanHull.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanShield.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanTurret.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanProjectileTurret.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanBeamTurret.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanMissileTurret.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanTractorTurret.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanSensor.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanThruster.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanReactor.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanCoolingVents.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanHullMultiHull.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathanRepair.cpp )
set( Sources ${Sources} ./Process/Combat/WTcLeviathan.cpp )



set( Sources ${Sources} ./Process/Leviathans/WTcTrainingLeviathan.cpp )
set( Sources ${Sources} ./Process/Leviathans/WTcGunLeviathanMk1.cpp )
set( Sources ${Sources} ./Process/Leviathans/WTcBeamLeviathanMk1.cpp )
set( Sources ${Sources} ./Process/Leviathans/WTcMissileLeviathanMk1.cpp )

set( Sources ${Sources} ./Process/Planning/WTcPlanningPlayerGun.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningComponentBox.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningComponentTextField.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningComponent.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningLeviathan.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningScreen.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningHull.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningReactor.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningThruster.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningSensor.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningShield.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningVent.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningArcs.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningTurret.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningProjectileTurret.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningBeamTurret.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningTractorTurret.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningMissileTurret.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningMissileRack.cpp )
set( Sources ${Sources} ./Process/Planning/WTcPlanningRepair.cpp )


set( Sources ${Sources} ./Process/WTcAsteroidObject.cpp )
set( Sources ${Sources} ./Process/WTcExitScreen.cpp )



add_executable (Leviathon ${Sources})
target_link_libraries (Leviathon Bamboo GLEW GL openal )

