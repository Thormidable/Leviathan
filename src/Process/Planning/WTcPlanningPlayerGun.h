#ifndef __WTCPLANNINGPLAYERGUN_H__
#define __WTCPLANNINGPLAYERGUN_H__

class cPlayerGun : public cProcess
{
 cImage *mpGun;
 cButton *mpBigger;
 cButton *mpSmaller;
 cText *mpRate;
 cText *mpDamage;
 uint8 miSize;
public:

    cPlayerGun();
    void Run();
    void Stop();
    void Resize(uint8 liSize);

     float mfReloadTime;
    float mfDamage;

};

#endif
