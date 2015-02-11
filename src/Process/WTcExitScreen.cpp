
#include "../main.h"


cExitScreen::cExitScreen()
{
 mpBackground=_CREATE(cImage);
 mpBackground->Transparency(1);
 mpBackground->Shader("Image2DProgram");
 mpBackground->AddTexture("ExitBackground");
 mpBackground->Width(gpWindow->RenderAreaWidth());
 mpBackground->Height(gpWindow->RenderAreaHeight());
 mpBackground->Position(gpWindow->RenderAreaWidth()/2,gpWindow->RenderAreaHeight()/2);
 //mpBackground->Priority(7.0f);

float lfSize=20.0f;
float lfTop=500.0f;

 TextColor[0]=0.5f;
 TextColor[1]=0.0f;
 TextColor[2]=1.0f;
 TextColor[3]=1.0f;

 cText *lpText;

 TextColor[0]=0.1f;
 TextColor[1]=0.1f;
 TextColor[2]=0.3f;
 TextColor[3]=1.0f;

 string TextFont="Legrand";

 lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*2);
 lpText->Position(50.0f,lfTop);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("Made using Bamboo");

 lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*2);
 lpText->Position(50.0f,lfTop-40.0f);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("in under 200 lines");

 TextColor[0]=0.2f;
 TextColor[1]=0.2f;
 TextColor[2]=0.2f;
 TextColor[3]=1.0f;

lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*2.0);
 lpText->Position(50.0f,lfTop-310.0f);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("Bamboo available");

 lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*2.0);
 lpText->Position(50.0f,lfTop-350.0f);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("from SilkCircuit");

 TextColor[0]=0.1f;
 TextColor[1]=0.4f;
 TextColor[2]=0.1f;
 TextColor[3]=1.0f;

 lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*1.7f);
 lpText->Position(50.0f,lfTop-400.0f);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("www.silkcircuit.co.uk");

 TextColor[0]=0.8f;
 TextColor[1]=0.1f;
 TextColor[2]=0.1f;
 TextColor[3]=1.0f;

 lpText=_CREATE(cText);
 lpText->Shader("TextProgram");
 lpText->AddFont(TextFont.c_str());
 lpText->Size(lfSize*2.2f);
 lpText->Position(50.0f,lfTop-200.0f);
 lpText->SetVariable("TextColor",TextColor);
 lpText->Text("Press Esc to Quit");


 miTimer=250;
}

void cExitScreen::Run()
{
 if(miTimer) --miTimer;
 if(_KEY(KEY_ESC) && !miTimer) _QUIT;

}

void cExitScreen::Stop()
{

}

