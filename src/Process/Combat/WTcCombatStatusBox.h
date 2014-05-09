#ifndef __WTCCOMBATSTATUSBOX_H__
#define __WTCCOMBATSTATUSBOX_H__

class cCombatStatusBox
{
    cImage *mpBox;
    cLeviathanComponent **mpComponent;
    cLeviathanComponent *mpLast;
    static cPerspectiveControl *mpControl;


public:

    static c3DVf sfPosition;

    static cTexture *mpBoxTexture;
    static cTexture *mpDisplayTexture;
    static cFont *mpPlanningFont;
    static cRGBA scTextColor;

    cCombatStatusBox();
    ~cCombatStatusBox();

    void Display();
    void ResetPosition();

    void Color(cRGBA lsCol);

    cText *mpFields[2];
    cImage *mpFieldDisplay[2];

};

#endif
