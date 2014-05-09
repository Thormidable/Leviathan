#ifndef __WTCPLANNINGCOMPONENTBOX_H__
#define __WTCPLANNINGCOMPONENTBOX_H__




class cPlanningComponentBox
{
    uint8 miDataItems;
    uint16 miWidth;
    static cPerspectiveControl *mpControl;
public:
    cImage *mpBox;
    static c3DVf sfPosition;

    static cTexture *mpBoxTexture;
    static cFont *mpPlanningFont;
    static cRGBA scTextColor;

    cPlanningComponentBox();

    void DataItems(uint8 liItems);
    void Width(uint16 liWidth);
    bool Created();
    void Create();
    void Destroy();
    void Display();
    static void ResetPosition();

    void Color(cRGBA lsCol);

};

#endif
