#ifndef __WTCPLANNINGCOMPONENT_H__
#define __WTCPLANNINGCOMPONENT_H__

class cPlanningLeviathan;

class cPlanningComponent : public cProcess
{
    template <class T> friend class cComponentTextField;
    friend class cPlanningLeviathan;
protected:
    bool mbSelected;
    cPlanningComponentBox mcBox;
    cComponentTextField<string> mcType;
    cComponentTextField<float> mcHealth;
    cComponentTextField<float> mcEnergyCost;
    cComponentTextField<string> mcArmourType;
    cComponentTextField<float> mcArmourValue;
    vRenderObject *mpFollowing;
    vRenderNode *mpComponentNode;
    cLeviathanReactorSettings *mpReactor;
    cImage *mpIcon;

    bool mbArmour;

    uint8 miDataItems;

  public:
    cPlanningComponent(cLeviathanComponentSettings *lpSettings);
    void Run();
    void Stop();
    void DisplayBox();
    virtual void DisplayOthers(c3DVf &lfPos)=0;

    void CreateBox();
    virtual void CreateOthers()=0;

    void DestroyBox();
    virtual void DestroyOthers()=0;
    string TypeString(uint8 liType);

    void SetProgram(cRenderObject *lpObj);
    void Selected(bool lbState);

    virtual void OtherSelected(bool lbState);

    virtual cTexture *GetIcon();

    vRenderNode *ComponentNode();

    virtual bool Hull();


};


#endif
