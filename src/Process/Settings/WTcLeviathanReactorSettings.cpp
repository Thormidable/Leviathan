
#include "../../main.h"

cLeviathanReactorSettings::cLeviathanReactorSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfBaseHeat, float lfMaxPower,float lfDamageHeatFactor,double lfOverload) : cLeviathanComponentSettings(lpSettings)
{
		 mpReactor=_GET_MESH_FILE(lsMesh.c_str());
 		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfBaseHeat=lfBaseHeat;
         mfDamageHeatFactor=lfDamageHeatFactor;
         mfInvMaxHealth=1.0f/mfHealth;
         mfOverload=lfOverload;
         mfMaxPower=lfMaxPower;
         mpReactorComp=0;

         if(mfBaseHeat>0.0f) {mfMaxPowerRequired=mfBaseHeat; mfMaxVent=mfBaseVent=0.0f;}
        else {mfMaxVent=mfBaseVent=-mfBaseHeat; mfMaxPowerRequired=0.0f;}
        mfPowerArmour=0.0f;

};

cLeviathanReactorSettings::cLeviathanReactorSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfBaseHeat, float lfMaxPower,float lfDamageHeatFactor,double lfOverload) : cLeviathanComponentSettings(lpSettings)
{
		 mpReactor=_GET_MESH_FILE(lsMesh.c_str());
 		 mpColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());


		 mfBaseHeat=lfBaseHeat;
		 mfDamageHeatFactor=lfDamageHeatFactor;
         mfInvMaxHealth=1.0f/mfHealth;
         mfOverload=lfOverload;
         mfMaxPower=lfMaxPower;
         mpReactorComp=0;

         if(mfBaseHeat>0.0f) {mfMaxPowerRequired=mfBaseHeat; mfMaxVent=mfBaseVent=0.0f;}
        else {mfMaxVent=mfBaseVent=-mfBaseHeat; mfMaxPowerRequired=0.0f;}
        mfPowerArmour=0.0f;
};

void cLeviathanReactorSettings::AddPowerUse(float lfHeat){mfMaxPowerRequired+=lfHeat;};
void cLeviathanReactorSettings::AddBaseCooling(float lfCool){mfBaseVent+=lfCool;};
void cLeviathanReactorSettings::AddMaxCooling(float lfCool){mfMaxVent+=lfCool;};
void cLeviathanReactorSettings::AddPowerArmour(float lfEnergy){mfPowerArmour+=lfEnergy;};
