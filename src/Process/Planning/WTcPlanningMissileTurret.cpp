
#include "../../main.h"

cPlanningMissileTurret::cPlanningMissileTurret(cLeviathanMissileTurretSettings *lpSettings) : cPlanningTurret(lpSettings)
{

    mcROF.String("ROF: ");
    mcROF.Data(lpSettings->DisplayROF());
    mcMissileType.String("Type: ");
    mcMissileType.Data(lpSettings->mpMissileSettings->TypeString());
    mcMobility.String("Mobility: ");
    mcMobility.Data(lpSettings->mpMissileSettings->mfSideThrust);
    mcDamage.String("Damage: ");
    mcDamage.Data(lpSettings->DisplayDamage());

    miDataItems+=4;
    mcBox.DataItems(miDataItems);
}

void cPlanningMissileTurret::Run()
{
    cPlanningTurret::Run();
}

void cPlanningMissileTurret::Stop()
{
	cPlanningTurret::Stop();
}

void cPlanningMissileTurret::DisplayOthers(c3DVf &lfPos)
{
  mcROF.Display();
  cPlanningTurret::DisplayOthers(lfPos);
  mcMissileType.Display();
  mcMobility.Display();
  mcDamage.Display();
};

void cPlanningMissileTurret::CreateOthers()
{
  mcROF.Create();
  mcMissileType.Create();
  mcMobility.Create();
  mcDamage.Create();
  cPlanningTurret::CreateOthers();
};
void cPlanningMissileTurret::DestroyOthers()
{
  mcROF.Destroy();
  mcMissileType.Destroy();
  mcMobility.Destroy();
  mcDamage.Destroy();
  cPlanningTurret::DestroyOthers();
};

cTexture *cPlanningMissileTurret::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("MissileTurretPVE");
    else return _GET_TEXTURE_FILE("MissileTurretNVE");
};

