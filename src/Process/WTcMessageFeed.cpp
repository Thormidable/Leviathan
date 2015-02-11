
//#include "../main.h"
//
//cMessageFeedItem::cMessageFeedItem(string lsMessage,float lfDelay,cFont *lpFont,cRGBA lcColor)
//{
//   mpText=_CREATE(cText(gp2DCamera));
//   mpText->Shader("TextProgram");
//   mpText->SetUniform("TextColor",lcColor.Color());
//   mpText->Size(DATA_ITEM_HEIGHT);
//   mpText->AddFont(lpFont);
//   mpText->Text(lsMessage);
//   mpText->Transparency(6);
//   mfDelay=lfDelay;
//   msMessage=lsMessage;
//};
//
//bool cMessageFeedItem::Update(c3DVf &lfPos)
//{
//    mfDelay-=WT_FRAME_TIME;
//    if(mfDelay<0.0f) return 0;
//    mpText->Position(lfPos.v);
//    lfPos[1]-=DATA_ITEM_HEIGHT;
//    return 1;
//}
//
//cMessageFeedItem::~cMessageFeedItem()
//{
// _KILL(mpText);
// mpText=0;
//}
//
//
//cMessageFeed::cMessageFeed(uint8 liItems,cTexture *lpBox,cRGBA lsBoxColor,cFont *lpFont,cRGBA lsFontColor)
//{
//    miSpaces=liItems;
//    miItems=0;
//    mpItems=new cMessageFeedItem*[miSpaces];
//
//    mpBox=new cImage(gp2DCamera);
//    mpBox->Shader("Image2DUniformColorProgram");
//    mpBox->AddTexture(lpBox);
//    mpBoxColor=lsBoxColor;
//    mpBox->SetUniform("UniformColor",mpBoxColor.Color());
//    mpBox->Width(DATA_BOX_WIDTH);
//    mpBox->Height(DATA_ITEM_HEIGHT*(miSpaces+1));
//	mpBox->Transparency(5);
//
//    mpBox->Position(_WINDOW->RenderAreaWidth()-DATA_BOX_WIDTH*0.5,_WINDOW->RenderAreaHeight()-DATA_ITEM_HEIGHT*(miSpaces+1)*0.5,0.0f);
//
//    mpFont=lpFont;
//    mpFontColor=lsFontColor;
//
//};
//
//void cMessageFeed::Font(cFont *lpFont,cRGBA lsFontColor)
//{
//    mpFont=lpFont;
//    mpFontColor=lsFontColor;
//};
//
//void cMessageFeed::Box(cTexture *lpBox,cRGBA lsBoxColor)
//{
//    mpBox->ClearTextureStack();
//    mpBox->AddTexture(lpBox);
//    mpBoxColor=lsBoxColor;
//};
//
//void cMessageFeed::Position(c3DVf lfPos)
//{
//    mpBox->Position(lfPos.v);
//}
//void cMessageFeed::AddMessage(string lsMessage,float lfDelay)
//{
//    if(miItems<miSpaces)
//    {
//        mpItems[miItems++]=new cMessageFeedItem(lsMessage,lfDelay,mpFont,mpFontColor);
//    }
//    else
//    {
//        delete mpItems[0];
//        memmove(mpItems,&mpItems[1],sizeof(cMessageFeedItem*)*(miItems-1));
//        mpItems[miItems-1]=new cMessageFeedItem(lsMessage,lfDelay,mpFont,mpFontColor);
//    }
//};
//
//void cMessageFeed::Run()
//{
// c3DVf lfPos=mpBox->Position();
// lfPos[0]+=DATA_ITEM_HEIGHT-DATA_BOX_WIDTH*0.5;
// lfPos[1]+=(DATA_ITEM_HEIGHT*(miSpaces+1))*0.5f-DATA_ITEM_HEIGHT;
// uint8 liSpare=0;
// for(uint8 liCount=0;liCount<miItems;++liCount)
// {
//     if(!mpItems[liCount]->Update(lfPos))
//     {
//         delete mpItems[liCount];
//     }
//     else
//     {
//        if(liCount!=liSpare){mpItems[liSpare]=mpItems[liCount];}
//        ++liSpare;
//     }
// }
// miItems=liSpare;
//};
//
//void cMessageFeed::Stop()
//{
//
//};
//
//cMessageFeed::~cMessageFeed()
//{
//    _KILL(mpBox);
//    uint8 liCount;
// for(liCount=0;liCount<miItems;++liCount)
// {
//  delete mpItems[liCount];
//  mpItems[liCount]=0;
// }
//
// while(liCount<miSpaces)
// {
//     mpItems[liCount++]=0;
// }
//
// delete []mpItems;
// mpItems=0;
//};
//
//void cMessageFeed::UpdatePosition()
//{
// mpBox->Position(_WINDOW->RenderAreaWidth()-DATA_BOX_WIDTH*0.5,_WINDOW->RenderAreaHeight()-DATA_ITEM_HEIGHT*(miSpaces+1)*0.5,0.0f);
//}
