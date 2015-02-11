
#include "../../main.h"

void cBeamLeviathanMk1::CreateData()
{
    Initialise(48,6);
    cMatrix4 lpRelative;

    uint32 liCount=0;

    lpRelative.Identity();
    lpRelative.Position(0.0f,0.0f,0.0f);
    mpComponents[liCount++]=new cLeviathanReactorSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,0.0f))),"TLevReactorMesh","TLevReactorColl",0.0f,200.0f,1.0f,1000.0f);
    mpNodes[LV_TRAIN_REACTOR]=mpComponents[liCount-1];
    lpRelative.Identity();
    lpRelative.Position(0.0f,0.0f,10.280f);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(4000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,10.280f))),"TLevCoreBulgeMesh","TLevCoreBulgeColl");
    mpNodes[LV_TRAIN_COREBULGE]=mpComponents[liCount-1];
    mpComponents[liCount++]=new cLeviathanVentSettings(cLeviathanComponentSettings(100.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_COREBULGE],cMatrix4(0.0f,200.0f,0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR])),"TLevVentMesh","TLevVentColl",DEGREES_TO_RADIANS(45),0.1f,0.5f,2.0f);
    mpComponents[liCount++]=new cLeviathanVentSettings(cLeviathanComponentSettings(100.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_COREBULGE],cMatrix4(200.0f,0.0f,0.0f,0.0f,0.0f,DEGREES_TO_RADIANS(90))),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR])),"TLevVentMesh","TLevVentColl",DEGREES_TO_RADIANS(45),0.1f,0.5f,2.0f);
    mpComponents[liCount++]=new cLeviathanVentSettings(cLeviathanComponentSettings(100.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_COREBULGE],cMatrix4(0.0f,-200.0f,0.0f,0.0f,0.0f,DEGREES_TO_RADIANS(180))),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR])),"TLevVentMesh","TLevVentColl",DEGREES_TO_RADIANS(45),0.1f,0.5f,2.0f);
    mpComponents[liCount++]=new cLeviathanVentSettings(cLeviathanComponentSettings(100.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_COREBULGE],cMatrix4(-200.0f,0.0f,0.0f,0.0f,0.0f,DEGREES_TO_RADIANS(270))),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR])),"TLevVentMesh","TLevVentColl",DEGREES_TO_RADIANS(45),0.1f,0.5f,2.0f);


    lpRelative.Identity();
    lpRelative.Position(0.0f,0.0f,-158.91);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(0.0f,0.0f,-158.91))),"TLevRearBeamMesh","TLevRearBeamColl");
    mpNodes[LV_TRAIN_REARBEAM]=mpComponents[liCount-1];
    lpRelative.Identity();
    lpRelative.Position(0.0f,0.0f,-101.249);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-101.249))),"TLevCentralThrusterOutletMesh","TLevCentralThrusterOutletColl");
    lpRelative.Identity();
    lpRelative.Position(0.0f,0.0f,-100.0f);
    lpRelative.RotateY(DEGREES_TO_RADIANS(180));
    mpComponents[liCount++]=new cLeviathanThrusterSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-100.0f,0.0f,DEGREES_TO_RADIANS(180),0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevThrusterMesh","TLevThrusterColl",TRAIN_LEV_MAX_THRUST,TRAIN_LEV_THRUST_LIMIT);

    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REARBEAM],cMatrix4(-70.0f,0.0f,-34.09))),"TLevEngineBaseMesh","TLevEngineBaseColl");
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(0,cMatrix4(-74.78f,0.0f,-40.155))),"TLevEngineOutletMesh","TLevEngineOutletColl");
    mpComponents[liCount++]=new cLeviathanThrusterSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-100.0f,0.0f,DEGREES_TO_RADIANS(180),0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevThrusterMesh","TLevThrusterColl",TRAIN_LEV_MAX_THRUST,TRAIN_LEV_THRUST_LIMIT);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REARBEAM],cMatrix4(0.0f,-70.0f,-34.09,0.0f,0.0f,DEGREES_TO_RADIANS(90)))),"TLevEngineBaseMesh","TLevEngineBaseColl");
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(0,cMatrix4(-74.78f,0.0f,-40.155))),"TLevEngineOutletMesh","TLevEngineOutletColl");
    mpComponents[liCount++]=new cLeviathanThrusterSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-100.0f,0.0f,DEGREES_TO_RADIANS(180),0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevThrusterMesh","TLevThrusterColl",TRAIN_LEV_MAX_THRUST,TRAIN_LEV_THRUST_LIMIT);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REARBEAM],cMatrix4(70.0f,0.0f,-34.09,0.0f,0.0f,DEGREES_TO_RADIANS(180)))),"TLevEngineBaseMesh","TLevEngineBaseColl");
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(0,cMatrix4(-74.78f,0.0f,-40.155))),"TLevEngineOutletMesh","TLevEngineOutletColl");
    mpComponents[liCount++]=new cLeviathanThrusterSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-100.0f,0.0f,DEGREES_TO_RADIANS(180),0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevThrusterMesh","TLevThrusterColl",TRAIN_LEV_MAX_THRUST,TRAIN_LEV_THRUST_LIMIT);
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REARBEAM],cMatrix4(0.0f,70.0f,-34.09,0.0f,0.0f,DEGREES_TO_RADIANS(270)))),"TLevEngineBaseMesh","TLevEngineBaseColl");
    mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(0,cMatrix4(-74.78f,0.0f,-40.155))),"TLevEngineOutletMesh","TLevEngineOutletColl");
    mpComponents[liCount++]=new cLeviathanThrusterSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,-100.0f,0.0f,DEGREES_TO_RADIANS(180),0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevThrusterMesh","TLevThrusterColl",TRAIN_LEV_MAX_THRUST,TRAIN_LEV_THRUST_LIMIT);
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(0.0f,0.0f,116.17f))),"TLevForwardCoreBeamMesh","TLevForwardCoreBeamColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,0.0f,194.081))),"TLevHullVerticalMesh","TLevHullVerticalColl");
     mpNodes[LV_TRAIN_HULL_VERTICAL]=mpComponents[liCount-1];
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_HULL_VERTICAL],cMatrix4(-67.8f,0.0f,-9.531))),"TLevHullHorizontalMesh","TLevHullHorizontalColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_HULL_VERTICAL],cMatrix4(67.8f,0.0f,-9.531,0.0f,0.0f,DEGREES_TO_RADIANS(180)))),"TLevHullHorizontalMesh","TLevHullHorizontalColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(3000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_HULL_VERTICAL],cMatrix4(-4.0f,110.59f,-80.72))),"TLevBridgeBaseMesh","TLevBridgeBaseColl");
     mpNodes[LV_TRAIN_BRIDGE_BASE]=mpComponents[liCount-1];
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_BRIDGE_BASE],cMatrix4(0.0f,28.657f,0.0f))),"TLevBridgeHorizontalMesh","TLevBridgeHorizontalColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,-8.89f,42.125f))),"TLevBridgeFrontMesh","TLevBridgeFrontColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(0.0f,-13.14f,-43.436f))),"TLevBridgeBackMesh","TLevBridgeBackColl");
     mpNodes[LV_TRAIN_RADAR_MOUNT]=mpComponents[liCount-1];
     mpComponents[liCount++]=new cLeviathanSensorSettings(cLeviathanComponentSettings(500.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_BRIDGE_BASE],cMatrix4(0.0f,-47.0f,-46.0f,0.0f,DEGREES_TO_RADIANS(180),DEGREES_TO_RADIANS(-45))),new cReductiveArmourSettings(6.0f,5.0f,50.0f),dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevRadarMesh","TLevRadarColl",0.1f,0.5f);
     mpComponents[liCount++]=new cLeviathanSensorSettings(cLeviathanComponentSettings(500.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_RADAR_MOUNT],cMatrix4(40.0f,0.0f,0.0f,0.0f,DEGREES_TO_RADIANS(45),0.0f)),new cReductiveArmourSettings(6.0f,5.0f,50.0f),dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevRadarMesh","TLevRadarColl",0.1f,0.5f);
     mpComponents[liCount++]=new cLeviathanSensorSettings(cLeviathanComponentSettings(500.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_RADAR_MOUNT],cMatrix4(-40.0f,0.0f,0.0f,0.0f,DEGREES_TO_RADIANS(-45),0.0f)),new cReductiveArmourSettings(6.0f,5.0f,50.0f),dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.1f),"TLevRadarMesh","TLevRadarColl",0.01f,1.0f);
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(1000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_HULL_VERTICAL],cMatrix4(9.8f,0.0f,214.82f))),"TLevShortAntennaMesh","TLevShortAntennaColl");
     mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(1000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_HULL_VERTICAL],cMatrix4(-9.8,0.0f,201.207f))),"TLevLongAntennaMesh","TLevLongAntennaColl");
     mpComponents[liCount++]=new cLeviathanShieldSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(0.0f,-100.0f,-54.720f,DEGREES_TO_RADIANS(-90),0.0f,0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.8f),"TLevShieldGenMesh","TLevShieldGenColl","TLevRearShieldMesh","TLevRearShieldColl",ENEMY_SHIELD_FILTER,1000.0f,0.1f,1000.0f,cRGBA(0.0f,0.8f,0.0f,0.2f));
     mpComponents[liCount++]=new cLeviathanShieldSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_BRIDGE_BASE],cMatrix4(0.0f,0.0f,-100.0f,DEGREES_TO_RADIANS(45),0.0f,0.0f)),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.8f),"TLevShieldGenMesh","TLevShieldGenColl","TLevForwardShieldMesh","TLevForwardShieldColl",ENEMY_SHIELD_FILTER,1000.0f,0.1f,1000.0f,cRGBA(0.0f,0.8f,0.0f,0.2f));


cLeviathanTurretSettings *mpTurretSettings=new cLeviathanTurretSettings(cLeviathanComponentSettings(4000.0f,new cFoundationSettingsList(0,cMatrix4()),0,dynamic_cast<cLeviathanReactorSettings*>(mpNodes[LV_TRAIN_REACTOR]),0.5f),"TLevTurretCollection",TRAIN_LEV_BEAM_TRACK_SPEED,DEGREES_TO_RADIANS(-135),DEGREES_TO_RADIANS(135),DEGREES_TO_RADIANS(-10),DEGREES_TO_RADIANS(90),TRAIN_LEV_RELOAD_SPEED);

cLeviathanBeamTurretSettings *lpBeamTurret;

 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(84.005f,-84.845,-20.0f))),"TLevFinBaseLLMesh","TLevFinBaseLLColl");
 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(92.595f,-30.905f,-75.896f))),"TLevFinTipLLMesh","TLevFinTipLLColl");
 mpComponents[liCount++]=lpBeamTurret=new cLeviathanBeamTurretSettings(mpTurretSettings,cBeamMesh(5000.0f,2.0f,12),18.0f,0.003f,0.01,13.0f,LEVIATHAN_BEAM_DAMAGE_FACTOR,cRGBA(0.0f,0.5f,1.0f,0.5f));
 mpComponents[liCount-1]->mpFoundations->Matrix(0)->Equals(cMatrix4(30.0f,-20.0f,-50.0f,0.0f,DEGREES_TO_RADIANS(90),DEGREES_TO_RADIANS(180)));

 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(-84.005f,-84.845,-20.0f))),"TLevFinBaseLRMesh","TLevFinBaseLRColl");
 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(-92.595f,-30.905f,-75.896f))),"TLevFinTipLRMesh","TLevFinTipLRColl");
 mpComponents[liCount++]=lpBeamTurret=new cLeviathanBeamTurretSettings(mpTurretSettings,cBeamMesh(5000.0f,2.0f,12),18.0f,0.003f,0.01,13.0f,LEVIATHAN_BEAM_DAMAGE_FACTOR,cRGBA(0.0f,0.5f,1.0f,0.5f));
 mpComponents[liCount-1]->mpFoundations->Matrix(0)->Equals(cMatrix4(-30.0f,-20.0f,-50.0f,0.0f,DEGREES_TO_RADIANS(-90),DEGREES_TO_RADIANS(180)));

 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(-84.0f,63.567,-20.0f))),"TLevFinBaseURMesh","TLevFinBaseURColl");
 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(-82.93f,34.513f,-60.941f))),"TLevFinTipURMesh","TLevFinTipURColl");
  mpComponents[liCount++]=lpBeamTurret=new cLeviathanBeamTurretSettings(mpTurretSettings,cBeamMesh(5000.0f,2.0f,12),18.0f,0.003f,0.01,13.0f,LEVIATHAN_BEAM_DAMAGE_FACTOR,cRGBA(0.0f,0.5f,1.0f,0.5f));
 mpComponents[liCount-1]->mpFoundations->Matrix(0)->Equals(cMatrix4(-30.0f,20.0f,-50.0f,0.0f,DEGREES_TO_RADIANS(-90),0.0f));

 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(mpNodes[LV_TRAIN_REACTOR],cMatrix4(84.0f,63.567f,-20.0f))),"TLevFinBaseULMesh","TLevFinBaseULColl");
 mpComponents[liCount++]=new cLeviathanHullSettings(cLeviathanComponentSettings(2000.0f,new cFoundationSettingsList(0,cMatrix4(82.93f,34.513f,-60.941f))),"TLevFinTipULMesh","TLevFinTipULColl");
 mpComponents[liCount++]=lpBeamTurret=new cLeviathanBeamTurretSettings(mpTurretSettings,cBeamMesh(5000.0f,2.0f,12),18.0f,0.003f,0.01,13.0f,LEVIATHAN_BEAM_DAMAGE_FACTOR,cRGBA(0.0f,0.5f,1.0f,0.5f));
 mpComponents[liCount-1]->mpFoundations->Matrix(0)->Equals(cMatrix4(30.0f,20.0f,-50.0f,0.0f,DEGREES_TO_RADIANS(90),0.0f));


 delete mpTurretSettings;

 miComponents=liCount;
};



  string cBeamLeviathanMk1::LeviathanName(){return "Beam Leviathan";};
  uint8 cBeamLeviathanMk1::LeviathanLevel(){return 0;};
  uint32 cBeamLeviathanMk1::LeviathanType(){return 1;};
  cTexture *cBeamLeviathanMk1::LeviathanTypeIcon(){return _GET_TEXTURE_FILE("TypeIcon1");};
