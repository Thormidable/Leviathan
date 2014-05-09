#ifndef __WTCPLANNINGLEVIATHAN_H__
#define __WTCPLANNINGLEVIATHAN_H__

class cPlanningComponent;

class cPlanningLeviathan : public cProcess
{

    cPlanningComponent **mpComponents;
    uint32 miComponents;
    vRenderNode *mpBaseNode;
  public:
    static cPlanningComponent *mpSelection;
	static float mfSelectionDistance;
	static bool sbSelectionOn;
    static cKeyToggle mcKeyToggles[];
    static cRGBA scSelectionColors[];
    static uint8 siColor;
    uint32 miSelectedComp;
        cPlanningLeviathan(cLeviathanSettings *lpSettings);
        void Run();
        void Stop();

        void UnselectAll();
    static vRenderNode *spLast;

        template <class T> void SelectByType()
        {
            for(uint32 liCount=0;liCount<miComponents;++liCount)
            {
                if(dynamic_cast<T*>(mpComponents[liCount]))
                {
                    mpComponents[liCount]->Selected(1);
                }
            }
        };

        void Reselect();
        uint32 GetTargeted();

        static void ResetColor();
        static cRGBA GetNextColor();


};

extern cPlanningLeviathan *gpPlanningLeviathan;

#endif
