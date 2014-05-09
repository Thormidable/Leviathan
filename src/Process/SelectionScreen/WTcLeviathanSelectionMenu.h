#ifndef __WTCLEVIATHANSELECTIONMENU_H__
#define __WTCLEVIATHANSELECTIONMENU_H__

class cLeviathanStarControl;

class cLeviathanStar : public cProcess
{
	friend class cLeviathanStarControl;
    cImage *mpOuterReticule;
    cImage *mpInnerReticule;
    cPoint *mpStar;
    float mfFrame;
    cImage *mpInfo;
    cImage *mpTypeIcon;
	cRGBA mcStarColor;
	cRGBA mcCoronaColor;


public:
    bool mbSelected;
    cLeviathanStar(cTexture *lpLeviathanType);
    void Run();
    void Stop();


};

class cLeviathanStarControl : public cProcess
{
    cLeviathanStar *mpLeviathanStar[LEVIATHAN_SELECTION_ROWS];
    int8 miSelected;

    cKeyToggle mpToggles[2];
public:
    cLeviathanStarControl();
    void Run();
    void Stop();

    void SelectUp();
    void SelectDown();

};


class cLeviathanPlanet : public cProcess
{
    cRenderNode *mpCentre;
    cModel *mpPlanet;
    cImage *mpCursor;
    float mfPlanetOrbitSpeed;
    float mfPlanetRotateSpeed;
    cRenderNode **mpMoons;
	cIcoSphere **mpMoonModels;
    float *mpMoonSpeeds;
    uint8 miMoons;

public:
    cLeviathanPlanet(cRenderNode *lpNode,float lfDist);
    void Run();
    void Stop();

    bool mbSelected;
};


class cLeviathanSolarSystemControl : public cProcess
{
    cPoint *mpStar;
    float mfFrame;
    cRenderNode *mpCentre;
    cLeviathanPlanet **mpPlanets;

    uint8 miSystem,miPlanets;
    bool mbEnterKey;
	bool mbBackKey;

    cKeyToggle mpToggles[2];
    int8 miSelected;

    cLight *mpLight;
public:
    cLeviathanSolarSystemControl(cRGBA lcStarCol,cRGBA lcCoronaCol);
    void Run();
    void Stop();

    void SelectUp();
    void SelectDown();

};

class cLeviathanArray
{
    cLeviathanArray();
    static cLeviathanArray *mpInstance;
    cLeviathanStarControl *mpStarControl;
    cLeviathanSolarSystemControl *mpSolarSystemControl;


public:
    static cLeviathanArray *Instance();
    cLeviathanSettings *mpLeviathanArray[LEVIATHAN_SELECTION_ROWS][LEVIATHAN_SELECTION_COLUMNS];
    void Embody();
    void Clear();
    void AddLeviathan(cLeviathanSettings *lpSettings);
    void StarMap();
    void SolarSystemMap();

	void ResetForCombat();

    bool Star(uint8 liType);
    bool System(uint8 liType,uint8 liMk);

    uint8 Planets(uint8 liType);
    void GenerateGame();

    uint8 miStarSystem;
    uint8 miPlanet;

    cLeviathanSettings *Access(uint8 liSystem);
    cLeviathanSettings *Access(uint8 liSystem,uint8 liStar);

    static cRGBA StarColor();
    static cRGBA CoronaColor(cRGBA lcBase);

	cRGBA mcStarColor;
	cRGBA mcCoronaColor;

    ~cLeviathanArray();
};

#endif
