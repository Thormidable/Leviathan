#include "stdafx.h"
#include "../../main.h"

cTexture *cCombatStatusBox::mpBoxTexture=0;
cFont *cCombatStatusBox::mpPlanningFont=0;
cRGBA cCombatStatusBox::scTextColor(0.0f,0.0f,0.0f,1.0f);
cPerspectiveControl *cCombatStatusBox::mpControl=0;
c3DVf cCombatStatusBox::sfPosition=c3DVf(0.0f,0.0f,0.0f);
cTexture *cCombatStatusBox::mpDisplayTexture=0;

cCombatStatusBox::cCombatStatusBox()
    {

        if(!mpControl) mpControl=_CAMERA;
        if(!mpBoxTexture) mpBoxTexture=_GET_TEXTURE_FILE("TargetStatusBox");
        if(!mpPlanningFont) mpPlanningFont=_GET_FONT_FILE("Pirulen");
        if(!mpDisplayTexture) mpDisplayTexture=_GET_TEXTURE_FILE("TargetStatusDisplay");


        mpBox=_CREATE(cImage(gp2DCamera));
        mpBox->Shader("Image2DProgram");
        mpBox->AddTexture(mpBoxTexture);
        mpBox->Width(COMBAT_STATUS_BOX_WIDTH);
        mpBox->Height(COMBAT_STATUS_BOX_HEIGHT);
        mpBox->Transparency(3);
        //mpBox->Priority(5.0f);
        mpBox->Position(COMBAT_STATUS_BOX_X,COMBAT_STATUS_BOX_Y);
        mpComponent=&(gpPlayer->mcTargeting.mpComponent);


        mpFields[0]=_CREATE(cText(gp2DCamera));
        mpFields[0]->Shader("TextProgram");
        mpFields[0]->SetUniform("TextColor",cRGBA(0.0f,0.0f,0.0f,1.0f).Color());
        mpFields[0]->Text("Health:");
        mpFields[0]->AddFont(mpPlanningFont);
        mpFields[0]->Size(DATA_ITEM_HEIGHT);
        mpFields[0]->Transparency(4);
        //mpFields[0]->Priority(3.0f);
        mpFields[0]->Position(COMBAT_STATUS_TEXT_X,COMBAT_STATUS_DISPLAY_Y_START);

        mpFields[1]=_CREATE(cText(gp2DCamera));
        mpFields[1]->Shader("TextProgram");
        mpFields[1]->SetUniform("TextColor",cRGBA(0.0f,0.0f,0.0f,1.0f).Color());
        mpFields[1]->AddFont(mpPlanningFont);
        mpFields[1]->Text("Reload:");
        mpFields[1]->Size(DATA_ITEM_HEIGHT);
        mpFields[1]->Transparency(4);
        //mpFields[1]->Priority(3.0f);
        mpFields[1]->Position(COMBAT_STATUS_TEXT_X,COMBAT_STATUS_DISPLAY_Y_START-COMBAT_STATUS_DISPLAY_Y_STEP);
        _SLEEP(mpFields[1]);

        mpFieldDisplay[0]=_CREATE(cImage(gp2DCamera));
        mpFieldDisplay[0]->Shader("Image2DUniformColorProgram");
        mpFieldDisplay[0]->SetUniform("UniformColor",cRGBA(0.0f,1.0f,0.0f,1.0f).Color());
        mpFieldDisplay[0]->AddTexture(mpDisplayTexture);
        mpFieldDisplay[0]->Width(COMBAT_STATUS_DISPLAY_WIDTH);
        mpFieldDisplay[0]->Height(COMBAT_STATUS_DISPLAY_HEIGHT);
        mpFieldDisplay[0]->Transparency(4);
        //mpFieldDisplay[0]->Priority(3.0f);
        mpFieldDisplay[0]->Position(COMBAT_STATUS_DISPLAY_X,COMBAT_STATUS_DISPLAY_Y_START);


        mpFieldDisplay[1]=_CREATE(cImage(gp2DCamera));
        mpFieldDisplay[1]->Shader("Image2DUniformColorProgram");
        mpFieldDisplay[1]->SetUniform("UniformColor",cRGBA(0.0f,1.0f,0.0f,1.0f).Color());
        mpFieldDisplay[1]->AddTexture(mpDisplayTexture);
        mpFieldDisplay[1]->Width(COMBAT_STATUS_DISPLAY_WIDTH);
        mpFieldDisplay[1]->Height(COMBAT_STATUS_DISPLAY_HEIGHT);
        mpFieldDisplay[1]->Transparency(4);
        //mpFieldDisplay[1]->Priority(3.0f);
        mpFieldDisplay[1]->Position(COMBAT_STATUS_DISPLAY_X,COMBAT_STATUS_DISPLAY_Y_START-COMBAT_STATUS_DISPLAY_Y_STEP);

        _SLEEP(mpFieldDisplay[1]);

        mpLast=0;


        ResetPosition();
    }

    cCombatStatusBox::~cCombatStatusBox()
    {
        _KILL(mpBox);
        mpBox=0;
        mpComponent=0;
    }



    void cCombatStatusBox::Display()
    {
     if(*mpComponent)
     {
        if(mpLast!=(*mpComponent))
        {
            _WAKE(mpBox);
            (*mpComponent)->Display(this);
        }

       (*mpComponent)->UpdateFieldColors(this);
     }
     else
     {
        _SLEEP(mpBox);
        _SLEEP(mpFieldDisplay[0]);
        _SLEEP(mpFieldDisplay[1]);
        _SLEEP(mpFields[0]);
        _SLEEP(mpFields[1]);
     }
     mpLast=(*mpComponent);
    };

void cCombatStatusBox::ResetPosition()
{
    mpBox->Position(COMBAT_STATUS_BOX_X,COMBAT_STATUS_BOX_Y);
    mpFields[0]->Position(COMBAT_STATUS_TEXT_X,COMBAT_STATUS_DISPLAY_Y_START);
    mpFields[1]->Position(COMBAT_STATUS_TEXT_X,COMBAT_STATUS_DISPLAY_Y_START-COMBAT_STATUS_DISPLAY_Y_STEP);

    mpFieldDisplay[0]->Position(COMBAT_STATUS_DISPLAY_X,COMBAT_STATUS_DISPLAY_Y_START);
    mpFieldDisplay[1]->Position(COMBAT_STATUS_DISPLAY_X,COMBAT_STATUS_DISPLAY_Y_START-COMBAT_STATUS_DISPLAY_Y_STEP);
};

void cCombatStatusBox::Color(cRGBA lsCol)
{
    mpBox->SetVariable("UniformColor",lsCol.Color());
}
