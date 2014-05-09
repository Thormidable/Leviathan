#include "stdafx.h"
#include "../../main.h"


cPlanningBeamTurret::cPlanningBeamTurret(cLeviathanBeamTurretSettings *lpSettings) : cPlanningTurret(lpSettings)
{
    mcROF.String("ROF: ");
    mcROF.Data(lpSettings->DisplayROF());
    mcDamage.String("Damage: ");
    mcDamage.Data(lpSettings->DisplayDamage());
    mcDelay.String("Delay: ");
    mcDelay.Data(lpSettings->DisplayDelay());

    miDataItems+=3;
    mcBox.DataItems(miDataItems);
}

void cPlanningBeamTurret::Run()
{
    cPlanningTurret::Run();

}

void cPlanningBeamTurret::Stop()
{
	cPlanningTurret::Stop();
}

void cPlanningBeamTurret::DisplayOthers(c3DVf &lfPos)
{
  mcROF.Display();
  cPlanningTurret::DisplayOthers(lfPos);
  mcDamage.Display();
  mcDelay.Display();

};

void cPlanningBeamTurret::CreateOthers()
{
 cPlanningTurret::CreateOthers();
  mcROF.Create();
  mcDelay.Create();
  mcDamage.Create();
};
void cPlanningBeamTurret::DestroyOthers()
{
 cPlanningTurret::DestroyOthers();
  mcROF.Destroy();
  mcDelay.Destroy();
  mcDamage.Destroy();
};

cTexture *cPlanningBeamTurret::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("BeamTurretPVE");
    else return _GET_TEXTURE_FILE("BeamTurretNVE");
};
