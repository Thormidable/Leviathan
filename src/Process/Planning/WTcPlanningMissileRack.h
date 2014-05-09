#ifndef __WTCPLANNINGMISSILERACK_H__
#define __WTCPLANNINGMISSILERACK_H__

class cPlanningMissileRack;

class cPlanningMissileSlot
{
    friend class cPlanningMissileRack;

    cButton *mpButton;
public:
    uint32 miType;
};

class cPlanningMissileRack : public cProcess
{
    cImage *mpImage;

public:

    uint32 miSlots;
    cPlanningMissileSlot *mpSlots;

    cPlanningMissileRack(uint32 liSlots);
    ~cPlanningMissileRack();
    void Run();
    void Stop();

    static cRGBA *msMissileColors;
    static cRGBA *PrepMissileColors();

};

#endif
