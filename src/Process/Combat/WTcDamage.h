#ifndef __WTCDAMAGE_H__
#define __WTCDAMAGE_H__

class cLeviathanReactor;

class cDamage
{

public:
  cDamage(){};
  cDamage(float lfDamage,uint8 liType);
  cDamage(cDamageSettings *lpSettings);
  float mfDamage;
  uint8 miType;
  c3DVf mfPos;
  static float mfFinalDamage;

  cDamage operator=(cDamage lpOther);
};

class vArmour
{

public:
    virtual void Damage(cDamage *lpDam);
    virtual float ArmourStatus(){return 0.0f;};
    virtual void Reset(){};
    static vArmour *MakeArmour(vArmourSettings *lpArmour,cLeviathanReactor *lpReactor=0);
};

class cReductiveArmour : public vArmour
{

public:
    cReductiveArmour(cReductiveArmourSettings *lpSettings);
    float mpArmour[DAMAGE_TYPES];
    void Damage(cDamage *lpDam);
    float ArmourStatus();
};

class cPoweredArmour : public vArmour
{
    cLeviathanReactor *mpReactor;
    float mfDamageEnergyConversion;
    float mfMaxDamageConversion;
    float mfDamageConverted;
public:
    cPoweredArmour(cPoweredArmourSettings *lpSettings,cLeviathanReactor *lpReactor);
    void Damage(cDamage *lpDam);
    float ArmourStatus();
    void Reset();
};

class cBrittleArmour : public vArmour
{
    float mfBreakingPoint;
    float mfArmourPoints;
    float mfInvArmour;
public:
    cBrittleArmour(cBrittleArmourSettings *lpSettings);
    void Damage(cDamage *lpDam);
    float ArmourStatus();
};

class cTriangularArmour : public vArmour
{
    float mfArmourPoints;
    float mfArmourScaling;
    float mfMinWear;
    float mfInvArmour;
public:
    cTriangularArmour(cTriangularArmourSettings *lpSettings);
    void Damage(cDamage *lpDam);
    float ArmourStatus();
};

#endif
