
#include "../../main.h"

  cLeviathanTurret::cLeviathanTurret(cLeviathanTurretSettings *lpSettings) : cLeviathanComponent(lpSettings)
{
	mpHull=_CREATE(cNodeList(lpSettings->mpMesh,mpComponentNode));

	cCollisionObject *lpColl;
	lpColl=_CREATE(cCollisionObject(mpHull,this));
	lpColl->CollisionFilter(LEVIATHAN_COMPONENT_FILTER);
	lpColl->SetTypeBox(-10.0f,10.0f,-20.0f,20.0f,-10.0f,10.0f);

    lpLOSBeam=_CREATE(cBeam(0.3f,1000.0f,4));
    lpLOSBeam->Equals(mpHull->GetListItem(1));
    lpLOSBeam->Shader("DiscardProgram");
    lpLOSBeam->Transparency(1);
    lpLOSColl=_CREATE(cCollisionObject(lpLOSBeam,this));
    lpLOSColl->CollisionFilter(0);
    lpLOSColl->SetType(lpLOSBeam);

	mfTrackSpeed=lpSettings->mfTrackSpeed;
 	mfLowYaw=lpSettings->mfLowYaw;
 	mfHighYaw=lpSettings->mfHighYaw;
 	mfLowPitch=lpSettings->mfLowPitch;
 	mfHighPitch=lpSettings->mfHighPitch;
 	mfReloadRate=lpSettings->mfReloadRate;
};

  bool cLeviathanTurret::TrackPoint(float *lpPoint)
  {
     bool lbTracking=true;
     float lfAngles=ClampValue(mpHull->GetListItem(0)->mmCache.YawToPoint(lpPoint),mfTrackSpeed*_TIME_PER_FRAME);
     float lfTotAngle=LoopingValue(mpHull->GetListItem(0)->Yaw()+lfAngles,3.14159265f);
     if(lfTotAngle>mfLowYaw && lfTotAngle<mfHighYaw) mpHull->GetListItem(0)->RotateY(lfAngles);
     else lbTracking=false;

     lfAngles=ClampValue(mpHull->GetListItem(1)->mmCache.PitchToPoint(lpPoint),mfTrackSpeed*_TIME_PER_FRAME);
     lfTotAngle=LoopingValue(mpHull->GetListItem(1)->Pitch()-lfAngles,3.14159265f);
     if(lfTotAngle>mfLowPitch && lfTotAngle<mfHighPitch) mpHull->GetListItem(1)->RotateX(lfAngles);
     else lbTracking=false;
     return lbTracking;
  };
  bool cLeviathanTurret::TrackVector(float *lpVector)
  {
     bool lbTracking=true;
     float lfAngles=ClampValue(mpHull->GetListItem(0)->mmCache.YawToVector(lpVector),mfTrackSpeed*_TIME_PER_FRAME);
     float lfTotAngle=LoopingValue(mpHull->GetListItem(0)->Yaw()+lfAngles,3.14159265f);
     if(lfTotAngle>mfLowYaw && lfTotAngle<mfHighYaw) mpHull->GetListItem(0)->RotateY(lfAngles);
     else lbTracking=false;

     lfAngles=ClampValue(mpHull->GetListItem(1)->mmCache.PitchToVector(lpVector),mfTrackSpeed*_TIME_PER_FRAME);
     lfTotAngle=LoopingValue(mpHull->GetListItem(1)->Pitch()-lfAngles,3.14159265f);
     if(lfTotAngle>mfLowPitch && lfTotAngle<mfHighPitch) mpHull->GetListItem(1)->RotateX(lfAngles);
     else lbTracking=false;
     return lbTracking;
  };

  void cLeviathanTurret::UpdateHitSelf()
  {
      lpLOSBeam->Equals(mpHull->GetListItem(1)->mmCache);
    lpLOSBeam->Advance(40.0f);
  };

  bool cLeviathanTurret::WillHitSelf()
  {
      bool lbReturn;
        cCollisionList *lpList=_COLLISION_HANDLER->GenerateCollisionList(lpLOSColl,ENEMY_SHIP_FILTER);
        lbReturn=lpList->NextCollisionP();
        delete lpList;
        return lbReturn;
  };
  bool cLeviathanTurret::InRange(float lfRange)
  {
    return (mpHull->GetListItem(1)->mmCache.DistanceSq(cPlayer::HullMatrix)<lfRange*lfRange);
  };

  void cLeviathanTurret::Stop()
  {
      _KILL(mpHull);
      _KILL(lpLOSBeam);
      cLeviathanComponent::Stop();
  }
