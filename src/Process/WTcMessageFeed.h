//#ifndef __WTCMESSAGEFEED_H__
//#define __WTCMESSAGEFEED_H__
//
//class cMessageFeed;
//
//class cMessageFeedItem
//{
//    friend class cMessageFeed;
//    float mfDelay;
//    string msMessage;
//    cText *mpText;
//    public:
//        cMessageFeedItem(string lsMessage,float lfDelay=2.0f,cFont *lpFont=_GET_FONT_FILE("Ecliptic"),cRGBA lcColor=cRGBA(0.0f,0.0f,0.0f,1.0f));
//        ~cMessageFeedItem();
//        bool Update(c3DVf &lfPos);
//};
//
//class cMessageFeed : public cProcess
//{
//    cFont *mpFont;
//    cRGBA mpFontColor;
//    cImage *mpBox;
//    cRGBA mpBoxColor;
//    cMessageFeedItem **mpItems;
//    uint8 miItems;
//    uint8 miSpaces;
//    public:
//        cMessageFeed(uint8 liItems,cTexture *lpBox,cRGBA lsBoxColor=cRGBA(0.0f,1.0f,1.0f,1.0f),cFont *lpFont=_GET_FONT_FILE("Ecliptic"),cRGBA lsFontColor=cRGBA(0.0f,0.0f,0.0f,1.0f));
//        void Font(cFont *lpFont,cRGBA lsColor=cRGBA(0.0f,0.0f,0.0f,1.0f));
//        void Box(cTexture *lpBox,cRGBA lsColor=cRGBA(0.0f,1.0f,1.0f,1.0f));
//        void Position(c3DVf lfPos);
//        void AddMessage(string lsMessage,float lfDelay=2.0f);
//        void Run();
//        void Stop();
//        void UpdatePosition();
//        ~cMessageFeed();
//};
//
//#endif
