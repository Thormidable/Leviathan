#ifndef __WTCPLANNINGSHIELD_H__
#define __WTCPLANNINGSHIELD_H__



class cPlanningShield : public cPlanningComponent
{
    cRGBA mcShieldColor;
    cModel *mpShieldGen;
    cCollisionObject *mpColl;
    cComponentTextField<float> mcStrength;
    cComponentTextField<float> mcDelay;
    cComponentTextField<float> mcRecharge;

    cModel *mpShieldMesh;

public:
    cPlanningShield(cLeviathanShieldSettings *lpSettings);
    void DisplayOthers(c3DVf &lfPos);
    void CreateOthers();
    void DestroyOthers();
    void Run();
    void Stop();
    void OtherSelected(bool lbState);
    cTexture *GetIcon();
};

#endif
