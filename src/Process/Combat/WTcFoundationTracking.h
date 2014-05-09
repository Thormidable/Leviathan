#ifndef __WTCFOUNDATIONTRACKING_H__
#define __WTCFOUNDATIONTRACKING_H__

class cFoundationTracking;

class cFoundation
{
 friend class cFoundationTracking;
    vRenderNode *mpComponent;
    cMatrix4 mmMatrix;
public:
    cFoundation();

};

class cFoundationTracking
{
protected:
    vRenderNode *mpCurrentFoundation;
    cFoundation *mpFoundations;
    uint8 miFoundations;
    vRenderNode *mpComponentNode;

public:
    cFoundationTracking(cFoundationSettingsList *lpFoundSet);
    ~cFoundationTracking();

    cFoundation &operator[](uint8 liFoundation);
    vRenderNode *ComponentNode();

    //This returns 1 if the owner is now free.
    bool FoundationDeath(vRenderNode *lpComponent);

};

#endif
