#include "stdafx.h"
#include "../../main.h"

cPlanningProjectileTurret::cPlanningProjectileTurret(cLeviathanProjectileTurretSettings *lpSettings) : cPlanningTurret(lpSettings)
{

    mcROF.String("ROF: ");
    mcROF.Data(lpSettings->DisplayROF());
    mcSpeed.String("Speed: ");
    mcSpeed.Data(lpSettings->DisplayProjSpeed());
    mcDamage.String("Damage: ");
    mcDamage.Data(lpSettings->DisplayDamage());

    miDataItems+=3;
    mcBox.DataItems(miDataItems);
}

void cPlanningProjectileTurret::Run()
{
    cPlanningTurret::Run();

}

void cPlanningProjectileTurret::Stop()
{
	cPlanningTurret::Stop();
}

void cPlanningProjectileTurret::DisplayOthers(c3DVf &lfPos)
{
  mcROF.Display();
  cPlanningTurret::DisplayOthers(lfPos);
  mcSpeed.Display();
  mcDamage.Display();
};

void cPlanningProjectileTurret::CreateOthers()
{
  mcROF.Create();
  mcSpeed.Create();
  mcDamage.Create();
  cPlanningTurret::CreateOthers();
};
void cPlanningProjectileTurret::DestroyOthers()
{
    mcROF.Destroy();
    mcSpeed.Destroy();
  mcDamage.Destroy();
  cPlanningTurret::DestroyOthers();
};

cTexture *cPlanningProjectileTurret::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("ProjectileTurretPVE");
    else return _GET_TEXTURE_FILE("ProjectileTurretNVE");
};
