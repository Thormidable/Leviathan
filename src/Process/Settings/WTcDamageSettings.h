#ifndef __WTCDAMAGESETTINGS_H__
#define __WTCDAMAGESETTINGS_H__

class cLeviathanReactorSettings;

class cDamageSettings
{
public:
    cDamageSettings(float lfDamage,uint8 liType);
    float mfDamage;
    uint8 miType;

};

class vArmourSettings
{

public:
    static vArmourSettings *MakeArmour(vArmourSettings *lpArmour);
    virtual void ReactorPower(cLeviathanReactorSettings *lpReactor){(void) lpReactor;};
    virtual uint8 Type()=0;
    virtual string TypeString()=0;
    virtual float Value()=0;

};

class cReductiveArmourSettings : public vArmourSettings
{

public:
    cReductiveArmourSettings();
    cReductiveArmourSettings(float lfInstant,float lfContinuous,float lfArea);
    cReductiveArmourSettings(float lfArmour);
    cReductiveArmourSettings(cReductiveArmourSettings *lpArmour);
    float mpArmour[DAMAGE_TYPES];
    uint8 Type(){return 1;};

    string TypeString(){return "Reductive";};
    float Value(){return (mpArmour[0]+mpArmour[1]+mpArmour[2])/3;};
};

class cPoweredArmourSettings : public vArmourSettings
{
public:
    float mfDamageEnergyConversion;
    float mfMaxDamageConversion;

    cPoweredArmourSettings(float lfDamageEnergyConversion,float lfMaxDamage);
    cPoweredArmourSettings(cPoweredArmourSettings *lpArmour);
    uint8 Type(){return 2;};

    string TypeString(){return "Powered";};
    float Value(){return mfDamageEnergyConversion;};

    void ReactorPower(cLeviathanReactorSettings *lpReactor);
};

class cBrittleArmourSettings : public vArmourSettings
{
public:
    cBrittleArmourSettings(float lfArmourPoints,float lfBreakingPoint);
    cBrittleArmourSettings(cBrittleArmourSettings *lpSettings);
    uint8 Type(){return 3;};

    string TypeString(){return "Brittle";};
    float Value(){return mfArmourPoints;};

    float mfBreakingPoint;
    float mfArmourPoints;
};

class cTriangularArmourSettings : public vArmourSettings
{
public:
    cTriangularArmourSettings(float lfArmourPoints,float lfMinWear,float lfArmourScaling=1.0f);
    cTriangularArmourSettings(cTriangularArmourSettings *lpSettings);
    uint8 Type(){return 4;};

    string TypeString(){return "Triangle";};
    float Value(){return mfArmourPoints;};

    float mfArmourPoints;
    float mfArmourScaling;
    float mfMinWear;
};

#endif
