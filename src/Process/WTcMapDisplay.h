#ifndef __WTCMAPDISPLAY_H__
#define __WTCMAPDISPLAY_H__

class cMapDisplayObject
{

public:
    cBillBoard *mpPoint;
    cLine *mpLine;
    cMatrix4 *mpFollow;

    cMapDisplayObject(vRenderObject *lpObj,cRGBA lcColor,string lsTexture);
    ~cMapDisplayObject();

};

class cMapDisplay: public cProcess
{
 friend class cMapDisplayObject;
 cRenderNode *mpNode;
 cRenderObject *mpFollow;
 cCamera *mpCamera;

public:
	cMapDisplay(cCamera *lpCamera);
	void Run();
	void Stop();
    void Follow(cRenderObject *lpFollow);
	bool UserSignal(SIGNAL lsSignal,void* lpData);

	void MapObject(cMapDisplayObject *lpObj);


    static cMapDisplay *mpStaticThis;

};


#endif
