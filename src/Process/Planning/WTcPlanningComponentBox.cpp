#include "stdafx.h"
#include "../../main.h"

cTexture *cPlanningComponentBox::mpBoxTexture=0;
cFont *cPlanningComponentBox::mpPlanningFont=0;
cRGBA cPlanningComponentBox::scTextColor(0.0f,0.0f,0.0f,1.0f);
cPerspectiveControl *cPlanningComponentBox::mpControl=0;
c3DVf cPlanningComponentBox::sfPosition=c3DVf(0.0f,0.0f,0.0f);

cPlanningComponentBox::cPlanningComponentBox()
    {
        mpBox=0;
        if(!mpControl) mpControl=_CAMERA;
        if(!mpBoxTexture) mpBoxTexture=_GET_TEXTURE_FILE("DataDisplayBox");
        if(!mpPlanningFont) mpPlanningFont=_GET_FONT_FILE("Pirulen");

    }

    void cPlanningComponentBox::DataItems(uint8 liItems)
    {
        miDataItems=liItems;
        if(mpBox)
        {
            mpBox->Height(DATA_ITEM_HEIGHT*(miDataItems+1));
        }
    };

    void cPlanningComponentBox::Width(uint16 liWidth)
    {
        miWidth=liWidth;
        if(mpBox)
        {
            mpBox->Width(miWidth);
        }
    }

    bool cPlanningComponentBox::Created()
    {
        return mpBox;
    }

    void cPlanningComponentBox::Create()
    {

        mpBox=_CREATE(cImage(gp2DCamera));
        mpBox->Shader("Image2DUniformColorProgram");
        mpBox->AddTexture(mpBoxTexture);
        mpBox->SetVariable("UniformColor",cRGBA(0.0f,1.0f,0.0f,0.9f).Color());
        mpBox->Width(miWidth);
        mpBox->Height(DATA_ITEM_HEIGHT*(miDataItems+1));
		mpBox->Transparency(1);

    };

    void cPlanningComponentBox::Destroy()
    {

        _KILL(mpBox);
        mpBox=0;

    };

    void cPlanningComponentBox::Display()
    {

       mpBox->Position(sfPosition.X()+miWidth/2,sfPosition.Y()-(DATA_ITEM_HEIGHT*(miDataItems+2)/2));
       sfPosition[1]-=1.5*DATA_ITEM_HEIGHT;

    };

    void cPlanningComponentBox::ResetPosition()
    {
        if(mpControl) sfPosition=c3DVf(mpControl->X(),mpControl->Y()+mpControl->ViewportHeight(),0.0f);
    };

void cPlanningComponentBox::Color(cRGBA lsCol)
{
    mpBox->SetVariable("UniformColor",lsCol.Color());
}
