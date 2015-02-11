
#include "../../main.h"
cKeyToggle cPlanningLeviathan::mcKeyToggles[28];

cPlanningComponent *cPlanningLeviathan::mpSelection=0;
float cPlanningLeviathan::mfSelectionDistance=-1.0f;
bool cPlanningLeviathan::sbSelectionOn=false;

cRGBA cPlanningLeviathan::scSelectionColors[7];
uint8 cPlanningLeviathan::siColor=0;

cPlanningLeviathan *gpPlanningLeviathan=0;

vRenderNode *cPlanningLeviathan::spLast;

cPlanningLeviathan::cPlanningLeviathan(cLeviathanSettings *lpSettings)
{
    miSelectedComp=0;

    gpPlanningLeviathan=this;


    scSelectionColors[0]=cRGBA(1.0f,1.0f,1.0f,1.0f);
    scSelectionColors[1]=cRGBA(1.0f,0.0f,0.0f,1.0f);
    scSelectionColors[2]=cRGBA(0.0f,1.0f,0.0f,1.0f);
    scSelectionColors[3]=cRGBA(0.0f,0.0f,1.0f,1.0f);
    scSelectionColors[4]=cRGBA(1.0f,1.0f,0.0f,1.0f);
    scSelectionColors[5]=cRGBA(1.0f,0.0f,1.0f,1.0f);
    scSelectionColors[6]=cRGBA(0.0f,1.0f,1.0f,1.0f);

    mcKeyToggles[0].SetState(PLANNING_SHOW_HULL_ICONS_START);
    mcKeyToggles[1].SetState(PLANNING_SHOW_UNSELECTED_ICONS_START);


spLast=_CAMERA->RenderList();
//lpSettings->mpComponents[0]->mpNode=_CAMERA->RenderList();

mpComponents=new cPlanningComponent*[lpSettings->miComponents];
miComponents=lpSettings->miComponents;
for(uint32 liCount=0;liCount<lpSettings->miComponents;++liCount)
{

    switch(lpSettings->mpComponents[liCount]->Type())
    {


        //case LV_MULTIHULL : {mpComponents[liCount]=_CREATE(cPlanningMultiHull(lpSettings->mpComponents[liCount]->MultiHull()));}break;

        case LV_TURRET_MISSILE : {mpComponents[liCount]=_CREATE(cPlanningMissileTurret(lpSettings->mpComponents[liCount]->MissileTurret()));}break;
        case LV_TURRET_TRACTOR : {mpComponents[liCount]=_CREATE(cPlanningTractorTurret(lpSettings->mpComponents[liCount]->TractorTurret()));}break;
        case LV_TURRET_BEAM : {mpComponents[liCount]=_CREATE(cPlanningBeamTurret(lpSettings->mpComponents[liCount]->BeamTurret()));}break;
        case LV_TURRET_PROJECTILE : {mpComponents[liCount]=_CREATE(cPlanningProjectileTurret(lpSettings->mpComponents[liCount]->ProjectileTurret()));}break;
        case LV_VENT : {mpComponents[liCount]=_CREATE(cPlanningVent(lpSettings->mpComponents[liCount]->Vent()));}break;
        case LV_SHIELD : {mpComponents[liCount]=_CREATE(cPlanningShield(lpSettings->mpComponents[liCount]->Shield()));}break;
        case LV_THRUSTERS : {mpComponents[liCount]=_CREATE(cPlanningThruster(lpSettings->mpComponents[liCount]->Thruster()));}break;
        case LV_SENSORS : {mpComponents[liCount]=_CREATE(cPlanningSensor(lpSettings->mpComponents[liCount]->Sensor()));}break;
        case LV_REACTOR : {mpComponents[liCount]=_CREATE(cPlanningReactor(lpSettings->mpComponents[liCount]->Reactor()));}break;
        case LV_HULL : {mpComponents[liCount]=_CREATE(cPlanningHull(lpSettings->mpComponents[liCount]->Hull()));}break;
		case LV_REPAIR : {mpComponents[liCount]=_CREATE(cPlanningRepair(lpSettings->mpComponents[liCount]->Repair()));}break;
        default : {mpComponents[liCount]=0;}break;

    };

    if(mpComponents[liCount])
    {
      spLast=mpComponents[liCount]->ComponentNode();
      lpSettings->mpComponents[liCount]->mpNode=spLast;
    }
    if(!liCount)
    {
        mpBaseNode=mpComponents[liCount]->ComponentNode();
    }
}


    for(uint32 liCount=0;liCount<miComponents;++liCount)
    {
        if(mpComponents[liCount]) mpComponents[liCount]->Selected(0);
    }


}

void cPlanningLeviathan::Run()
{
    if(PLANNING_LEVIATHAN_ROTATE)
    {
        if(!_MOUSE->Locked()) {_MOUSE->Lock(); _MOUSE->Hide();}
        mpBaseNode->GRotateX(_MOUSE->YSpeed()*cUserSettings::mfPlanningLeviathanRotationSensitivity);
        mpBaseNode->GRotateY(_MOUSE->XSpeed()*cUserSettings::mfPlanningLeviathanRotationSensitivity);
    }
    else
    {
        if(_MOUSE->Locked()) {_MOUSE->UnlockPosition(); _MOUSE->Show();}
    }

    if(PLANNING_CAMERA_ADVANCE) _CAMERA->GAdvanceZ(5.0f);
    if(PLANNING_CAMERA_RETREAT) _CAMERA->GAdvanceZ(-5.0f);

    if(mcKeyToggles[0].UpdateOnToggle(PLANNING_TOGGLE_HULL_ICONS))
    {
        if(mcKeyToggles[0].On()) cPlanningScreen::mpFeed->AddMessage("Show Hull",PLANNING_MESSAGE_DURATION);
        else cPlanningScreen::mpFeed->AddMessage("Hide Hull",PLANNING_MESSAGE_DURATION);
    };
    if(mcKeyToggles[1].UpdateOnToggle(PLANNING_TOGGLE_UNSELECTED_ICONS))
    {
        if(mcKeyToggles[1].On()) cPlanningScreen::mpFeed->AddMessage("Show Off",PLANNING_MESSAGE_DURATION);
        else cPlanningScreen::mpFeed->AddMessage("Hide Off",PLANNING_MESSAGE_DURATION);
    };
    if(mcKeyToggles[2].UpdateOnToggle(PLANNING_TOGGLE_UNSELECTED_SHIELD))
    {
        if(mcKeyToggles[2].On()) cPlanningScreen::mpFeed->AddMessage("Show Shield",PLANNING_MESSAGE_DURATION);
        else cPlanningScreen::mpFeed->AddMessage("Hide Shield",PLANNING_MESSAGE_DURATION);
    };

    if(mcKeyToggles[3].UpdateOnToggle(KEY_1))
        {
            UnselectAll();
            SelectByType<cPlanningReactor>();
            cPlanningScreen::mpFeed->AddMessage("Reactors Selected",PLANNING_MESSAGE_DURATION);
    }
    if(mcKeyToggles[4].UpdateOnToggle(KEY_2)){UnselectAll(); SelectByType<cPlanningThruster>(); cPlanningScreen::mpFeed->AddMessage("Thrusters Selected",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[5].UpdateOnToggle(KEY_3)){UnselectAll(); SelectByType<cPlanningSensor>(); cPlanningScreen::mpFeed->AddMessage("Sensors Selected",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[6].UpdateOnToggle(KEY_4)){UnselectAll(); SelectByType<cPlanningShield>(); cPlanningScreen::mpFeed->AddMessage("Shield Gens Selected",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[7].UpdateOnToggle(KEY_5)){UnselectAll(); SelectByType<cPlanningVent>(); cPlanningScreen::mpFeed->AddMessage("Vents Selected",PLANNING_MESSAGE_DURATION);}

    if(mcKeyToggles[8].UpdateOnToggle(KEY_6)){UnselectAll(); SelectByType<cPlanningProjectileTurret>(); cPlanningScreen::mpFeed->AddMessage("Projectile Turrets",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[9].UpdateOnToggle(KEY_8)){UnselectAll(); SelectByType<cPlanningTractorTurret>(); cPlanningScreen::mpFeed->AddMessage("Tractor Beams",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[10].UpdateOnToggle(KEY_7)){UnselectAll(); SelectByType<cPlanningBeamTurret>(); cPlanningScreen::mpFeed->AddMessage("Beam Turrets",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[11].UpdateOnToggle(KEY_9)){UnselectAll(); SelectByType<cPlanningMissileTurret>(); cPlanningScreen::mpFeed->AddMessage("Missile Launchers",PLANNING_MESSAGE_DURATION);}

    if(mcKeyToggles[12].UpdateOnToggle(KEY_0)){UnselectAll(); SelectByType<cPlanningProjectileTurret>(); SelectByType<cPlanningBeamTurret>(); SelectByType<cPlanningTractorTurret>(); SelectByType<cPlanningMissileTurret>(); cPlanningScreen::mpFeed->AddMessage("Turrets Selected",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[13].UpdateOnToggle(KEY_SLASH)){UnselectAll(); SelectByType<cPlanningHull>(); cPlanningScreen::mpFeed->AddMessage("Sub Struct",PLANNING_MESSAGE_DURATION);}

    if(mcKeyToggles[14].UpdateOnToggle(KEY_ENTER))
    {
            UnselectAll();
            bool lbRepeat=false;

            do
            {
                ++miSelectedComp;
                if(miSelectedComp==miComponents)
                {
                  miSelectedComp=0;
                  if(lbRepeat) break;
                  lbRepeat=true;
                }
            }while(mpComponents[miSelectedComp]->Hull());
            mpComponents[miSelectedComp]->Selected(1);
            cPlanningScreen::mpFeed->AddMessage("Next System",PLANNING_MESSAGE_DURATION);
    }

    if(mcKeyToggles[15].UpdateOnToggle(PLANNING_TOGGLE_ARC_RANGE))
    {
        if(mcKeyToggles[15].On()) cPlanningScreen::mpFeed->AddMessage("Full Arcs",PLANNING_MESSAGE_DURATION);
        else cPlanningScreen::mpFeed->AddMessage("Local Arcs",PLANNING_MESSAGE_DURATION);
    }

    if(mcKeyToggles[16].UpdateOnToggle(KEY_F1)) {gcPlannedSettings.mfTargets[0].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F1 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[17].UpdateOnToggle(KEY_F2)) {gcPlannedSettings.mfTargets[1].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F2 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[18].UpdateOnToggle(KEY_F3)) {gcPlannedSettings.mfTargets[2].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F3 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[19].UpdateOnToggle(KEY_F4)) {gcPlannedSettings.mfTargets[3].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F4 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[20].UpdateOnToggle(KEY_F5)) {gcPlannedSettings.mfTargets[4].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F5 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[21].UpdateOnToggle(KEY_F6)) {gcPlannedSettings.mfTargets[5].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F6 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[22].UpdateOnToggle(KEY_F7)) {gcPlannedSettings.mfTargets[6].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F7 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[23].UpdateOnToggle(KEY_F8)) {gcPlannedSettings.mfTargets[7].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F8 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[24].UpdateOnToggle(KEY_F9)) {gcPlannedSettings.mfTargets[8].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F9 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[25].UpdateOnToggle(KEY_F10)) {gcPlannedSettings.mfTargets[9].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F10 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[26].UpdateOnToggle(KEY_F11)) {gcPlannedSettings.mfTargets[10].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F11 Targeted",PLANNING_MESSAGE_DURATION);}
    if(mcKeyToggles[27].UpdateOnToggle(KEY_F12)) {gcPlannedSettings.mfTargets[11].SetID(GetTargeted()); cPlanningScreen::mpFeed->AddMessage("F12 Targeted",PLANNING_MESSAGE_DURATION);}


   if(PLANNING_CAMERA_ROTATE)
    {
        _CAMERA->RotateY(_MOUSE->XSpeed()*PLANNING_CAMERA_ROTATE_SPEED);
        _CAMERA->RotateX(_MOUSE->YSpeed()*PLANNING_CAMERA_ROTATE_SPEED);
    }

 if(_MOUSE->Right())
  {
      if(mpSelection)
      {
          UnselectAll();
          mpSelection->Selected(1);
      }
      mpSelection=0;
	  mfSelectionDistance=10000.0f;
	  sbSelectionOn=true;
  }
  else
  {
      mpSelection=0;
	  sbSelectionOn=false;
  }


    ResetColor();
    Reselect();


    cPlanningComponentBox::ResetPosition();

}

void cPlanningLeviathan::Stop()
{
	for(uint32 liCount=0;liCount<miComponents;++liCount)
    {
       if(mpComponents[liCount])
	   {
		   _KILL(mpComponents[liCount]);
		   mpComponents[liCount]=0;
	   }
    }
 delete []mpComponents;
 mpComponents=0;

 gcPlannedSettings.mmOrientation.Equals(mpBaseNode);
 //gcPlannedSettings.mmOrientation.RotateY(WT_PI);
 //gcPlannedSettings.mmOrientation.RotateZ(WT_PI);
 //gcPlannedSettings.mmOrientation.RotateX(WT_PI);
}

void cPlanningLeviathan::UnselectAll()
{
    for(uint32 liCount=0;liCount<miComponents;++liCount)
        {
            if(mpComponents[liCount]) mpComponents[liCount]->Selected(0);
        }
}

void cPlanningLeviathan::Reselect()
{
        for(uint32 liCount=0;liCount<miComponents;++liCount)
        {
            if(mpComponents[liCount]) mpComponents[liCount]->Selected(mpComponents[liCount]->mbSelected);
        }
};

void cPlanningLeviathan::ResetColor()
{
    siColor=6;
};

cRGBA cPlanningLeviathan::GetNextColor()
{
    ++siColor;
    return scSelectionColors[siColor%7]*7/siColor;
};

uint32 cPlanningLeviathan::GetTargeted()
{
   for(uint32 liCount=0;liCount<miComponents;++liCount)
   {
       if(mpComponents[liCount] && mpComponents[liCount]->mbSelected) return liCount;
   }
   return miComponents;
}

