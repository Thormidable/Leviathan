#include "stdafx.h"
#include "../../main.h"

cPlayerGun::cPlayerGun()
{
 mpGun=_CREATE(cImage(gp2DCamera));
 mpGun->Shader("Image2DProgram");
 mpGun->AddTexture("PlayerGunIcon");
 mpGun->Transparency(4);
 //mpGun->Priority(4.0f);
 mpGun->Width(PLAYER_GUN_ICON_WIDTH);
 mpGun->Height(PLAYER_GUN_ICON_HEIGHT);
 mpGun->Position(PLAYER_GUN_ICON_X,PLAYER_GUN_ICON_Y);


 mpBigger=_CREATE(cButton(gp2DCamera));
 mpBigger->Shader("Image2DProgram");
 mpBigger->AddTexture("PlusButton");
 mpBigger->Transparency(5);
 //mpBigger->Priority(3.0f);
 mpBigger->Width(PLAYER_GUN_SIZING_WIDTH);
 mpBigger->Height(PLAYER_GUN_SIZING_HEIGHT);
 mpBigger->Position(PLAYER_GUN_ICON_X+0.25*PLAYER_GUN_ICON_WIDTH,PLAYER_GUN_ICON_Y+0.25*PLAYER_GUN_ICON_HEIGHT);

 mpSmaller=_CREATE(cButton(gp2DCamera));
 mpSmaller->Shader("Image2DProgram");
 mpSmaller->AddTexture("MinusButton");
 mpSmaller->Transparency(5);
 //mpSmaller->Priority(3.0f);
 mpSmaller->Width(PLAYER_GUN_SIZING_WIDTH);
 mpSmaller->Height(PLAYER_GUN_SIZING_HEIGHT);
 mpSmaller->Position(PLAYER_GUN_ICON_X-0.25*PLAYER_GUN_ICON_WIDTH,PLAYER_GUN_ICON_Y+0.25*PLAYER_GUN_ICON_HEIGHT);

 mpRate=_CREATE(cText(gp2DCamera));
 mpRate->Shader("TextProgram");
 mpRate->AddFont("Pirulen");
 mpRate->SetUniform("TextColor",cRGBA(1.0f,1.0f,1.0f,1.0f).Color());
 mpRate->Size(DATA_ITEM_HEIGHT);
 mpRate->Position(PLAYER_GUN_ICON_X,PLAYER_GUN_ICON_Y+PLAYER_GUN_ICON_HEIGHT*0.7+DATA_ITEM_HEIGHT*1.5);
 mpRate->Transparency(5);
 //mpRate->Priority(3.0f);

 mpDamage=_CREATE(cText(gp2DCamera));
 mpDamage->Shader("TextProgram");
 mpDamage->AddFont("Pirulen");
 mpDamage->SetUniform("TextColor",cRGBA(1.0f,1.0f,1.0f,1.0f).Color());
 mpDamage->Size(DATA_ITEM_HEIGHT);
 mpDamage->Position(PLAYER_GUN_ICON_X,PLAYER_GUN_ICON_Y+PLAYER_GUN_ICON_HEIGHT*0.7+DATA_ITEM_HEIGHT*3);
 mpDamage->Transparency(5);
 //mpDamage->Priority(3.0f);

 Resize(1);



};
void cPlayerGun::Run()
{
    if(mpBigger->Clicked()) Resize(miSize+1);
    if(mpSmaller->Clicked()) Resize(miSize-1);

};

void cPlayerGun::Stop()
{
    _KILL(mpGun);
    _KILL(mpBigger);
    _KILL(mpSmaller);
	_KILL(mpRate);
	_KILL(mpDamage);
};

void cPlayerGun::Resize(uint8 liSize)
{
 if(!liSize) miSize=1;
 else miSize=liSize;

    mfReloadTime=PLAYER_RELOAD_TIME*pow(2,miSize)*0.5f;
    mfDamage=PLAYER_BULLET_DAMAGE;
 for(uint8 liCount=1;liCount<miSize;++liCount){mfDamage*=PLAYER_BULLET_DAMAGE_SCALE;};


 mpRate->Text("ROF: ");
 float ROF=10.0f/mfReloadTime;
 mpRate->Add(ROF);

 mpDamage->Text("Damage :");
 mpDamage->Add(mfDamage);

}
