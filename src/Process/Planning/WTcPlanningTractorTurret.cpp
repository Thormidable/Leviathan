
#include "../../main.h"

cPlanningTractorTurret::cPlanningTractorTurret(cLeviathanTractorTurretSettings *lpSettings) : cPlanningTurret(lpSettings)
{

    mcDelay.String("ROF: ");
    mcDelay.Data(lpSettings->DisplayROF());
    mcDamage.String("Slowing: ");
    mcDamage.Data(lpSettings->DisplayDamage());

    miDataItems+=2;
    mcBox.DataItems(miDataItems);
}

void cPlanningTractorTurret::Run()
{
    cPlanningTurret::Run();

}

void cPlanningTractorTurret::Stop()
{
cPlanningTurret::Stop();
}

void cPlanningTractorTurret::DisplayOthers(c3DVf &lfPos)
{
  mcDelay.Display();
  cPlanningTurret::DisplayOthers(lfPos);
  mcDamage.Display();
};

void cPlanningTractorTurret::CreateOthers()
{
  mcDelay.Create();
  cPlanningTurret::CreateOthers();
  mcDamage.Create();
};
void cPlanningTractorTurret::DestroyOthers()
{
  mcDelay.Destroy();
  cPlanningTurret::DestroyOthers();
  mcDamage.Destroy();
};

cTexture *cPlanningTractorTurret::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("TractorTurretPVE");
    else return _GET_TEXTURE_FILE("TractorTurretNVE");
};
