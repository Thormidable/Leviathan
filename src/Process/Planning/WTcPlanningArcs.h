#ifndef __WTCPLANNINGARCS_H__
#define __WTCPLANNINGARCS_H__

class cPlanningArcs
{
    c2DVf mfYaw;
    c2DVf mfPitch;
    float mfRange;
    cMesh *mpArcMesh;
    cModel *mpArc;
    cLineArray *mpOutline;
    cLineArrayData *mpOutlineData;

    static cUVSphere *gpArcBase;
public:
    cPlanningArcs();
    ~cPlanningArcs();
    void Yaw(c2DVf lfYaw);
    void Pitch(c2DVf lfPitch);
    void Range(float lfRange);
    void Create(vRenderNode *lpNode);
    void Destroy();
    void ConstructArcs();
    void GenerateOutline(uint16 liCentreFace,float lfRange);
    bool Created();

};

#endif
