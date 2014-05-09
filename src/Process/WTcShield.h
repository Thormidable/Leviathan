#ifndef __WTCSHIELD_H__
#define __WTCSHIELD_H__

class cLeviathanShieldSettings;

class cShield : public cProcess
{
protected:
    cModel *mpGenerator;
    cModel *mpShield;
    cCollisionObject *mpShieldColl;
    cRGBA mcShieldColor;
    cRGBA mcCurrColor;
    float mfHealth;
    float mfRecharge;
    float mfMax;
    float mfDelay;
	float mfInvMax;

	cMatrix4 InvMatrix;
public:
    cShield(cModel *lpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float Delay,cMatrix4 *OffSet=0);
    cShield(cModel *lpGenerator,cLeviathanShieldSettings *lpSettings);
    void Run();
    void Stop();

    bool UserSignal(SIGNAL lsSignal,void *lpData);

	void Max(float lfMax){mfMax=lfMax;}
	void Recharge(float lfRecharge){mfRecharge=lfRecharge;}
	void Delay(float lfDelay){mfDelay=lfDelay;}
	void Health(float lfHealth){mfHealth=lfHealth;}

	float Health(){return mfHealth;};

	void NoPower();

	cRGBA ShieldStatusColor();

	virtual void PlaySound(){};
};

class cPlayerShield : public cShield
{
  cImage *mpDisplay;

  static cAudioObject *mpShieldSound;
public:
    cPlayerShield(cModel *mpGenerator,string lpShield,string lpShieldColl,uint16 liFilter,cRGBA lcShieldColor,float lfRecharge,float lfMax, float Delay, float lfX,float lfY, float lfSize,cTexture *lpTexture);
	void Run();
	void PlaySound();
};
#endif
