
#include "../../main.h"

cPlanningSensor::cPlanningSensor(cLeviathanSensorSettings *lpSettings) : cPlanningComponent(lpSettings)
{
    mpSensor=_CREATE(cModel(mpComponentNode));
    mpSensor->Mesh(lpSettings->mpHull);
    SetProgram(mpSensor);

    mpFollowing=mpSensor;

    mpColl=_CREATE(cCollisionObject(mpSensor,this));
    mpColl->CollisionFilter(PLANNING_COMPONENT_FILTER);
    mpColl->SetType(lpSettings->mpColl);

    mcSensor.String("Scan: ");
    mcSensor.Data(lpSettings->mfSensorBaseDegredation);
    mcDegredationFactor.String("Base Scan: ");
    mcDegredationFactor.Data(lpSettings->mfMaxSensorDegredation+lpSettings->mfSensorBaseDegredation);

    miDataItems+=2;
    mcBox.DataItems(miDataItems);
}

void cPlanningSensor::Run()
{
    cPlanningComponent::Run();

}

void cPlanningSensor::Stop()
{
	cPlanningComponent::Stop();
  _KILL(mpSensor);
  mpSensor=0;
}

void cPlanningSensor::DisplayOthers(c3DVf &lfPos)
{
    mcSensor.Display();
    mcDegredationFactor.Display();
};

void cPlanningSensor::CreateOthers()
{
    mcSensor.Create();
    mcDegredationFactor.Create();
};
void cPlanningSensor::DestroyOthers()
{
  mcSensor.Destroy();
  mcDegredationFactor.Destroy();
};

cTexture *cPlanningSensor::GetIcon()
{
    if(mbSelected) return _GET_TEXTURE_FILE("SensorPVE");
    else return _GET_TEXTURE_FILE("SensorNVE");
};
