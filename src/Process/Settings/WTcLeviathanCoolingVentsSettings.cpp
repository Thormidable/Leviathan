
#include "../../main.h"

cLeviathanVentSettings::cLeviathanVentSettings(cLeviathanComponentSettings *lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool) : cLeviathanComponentSettings(lpSettings)
{
 		 mpVent=_GET_MESH_FILE(lsMesh.c_str());
		 mpVentColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfOpenAngle=lfOpenAngle;
		 mfOpeningRate=lfOpenRate;
         mfBaseCool=lfBaseCool;
         mfMaxCool=lfMaxCool;

        if(mpReactor)
        {
            mpReactor->AddBaseCooling(mfBaseCool);
            mpReactor->AddMaxCooling(mfMaxCool);
        }
};

cLeviathanVentSettings::cLeviathanVentSettings(const cLeviathanComponentSettings &lpSettings,string lsMesh,string lsCollision,float lfOpenAngle,float lfOpenRate, float lfBaseCool,float lfMaxCool) : cLeviathanComponentSettings(lpSettings)
{
 		 mpVent=_GET_MESH_FILE(lsMesh.c_str());
		 mpVentColl=_GET_COLLISION_MESH_FILE(lsCollision.c_str());

		 mfOpenAngle=lfOpenAngle;
		 mfOpeningRate=lfOpenRate;
         mfBaseCool=lfBaseCool;
         mfMaxCool=lfMaxCool;

        if(mpReactor)
        {
            mpReactor->AddBaseCooling(mfBaseCool);
            mpReactor->AddMaxCooling(mfMaxCool);
        }

};

uint8 cLeviathanVentSettings::Type(){return LV_VENT;};
cLeviathanVentSettings *cLeviathanVentSettings::Vent(){return this;};
