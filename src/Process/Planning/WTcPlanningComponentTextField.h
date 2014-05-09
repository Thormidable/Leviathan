#ifndef __WTCPLANNINGCOMPONENTTEXTFIELD_H__
#define __WTCPLANNINGCOMPONENTTEXTFIELD_H__

template<class T> class cComponentTextField
{
    cText *mpText;
    string StartText;
    T mcData;
public:
    cComponentTextField()
    {
        mpText=0;
        StartText="Mine";
    };

    void Data(T lcData)
    {
        mcData=lcData;
        if(mpText)
        {
            mpText->Text(StartText);
            mpText->Add(mcData);
        }
    };

    void String(string lsStart)
    {
        StartText=lsStart;
        if(mpText)
        {
            mpText->Text(StartText);
            mpText->Add(mcData);
        }
    };

    void Create()
    {
        mpText=_CREATE(cText(gp2DCamera));
        mpText->Shader("TextProgram");
        mpText->SetVariable("TextColor",cPlanningComponentBox::scTextColor.Color());
        mpText->AddFont(cPlanningComponentBox::mpPlanningFont);
        mpText->Text(StartText);
        mpText->Add(mcData);
        mpText->Size(DATA_ITEM_HEIGHT);
		mpText->Transparency(3);
    };

    void Destroy()
    {
        _KILL(mpText);
        mpText=0;
    };

    void Display()
    {

       mpText->Position(cPlanningComponentBox::sfPosition[0]+DATA_ITEM_HEIGHT,cPlanningComponentBox::sfPosition[1],cPlanningComponentBox::sfPosition[2]);
       cPlanningComponentBox::sfPosition[1]-=DATA_ITEM_HEIGHT;
    };

};



#endif
