#ifndef __WTCBULLET_H__
#define __WTCBULLET_H__

class cBullet : public cProcess
{

 //cPoint *mpBullet;
 cLine *mpBullet;
 float mfLife;
 //float mfDamage;
 cDamage *mcDamage;
 cCollisionObject *mpBulletColl;

 float mfSpeed;
 uint32 miTargetFilter;

public:
  cBullet(cMatrix4 *lpMatrix,c3DVf lfOffset,float lfSpeed,cDamage *lpDamage,uint32 lfFilter,uint32 lfTargetFilter);
  void Run();
  void Stop();
};

void GenerateDamageParticles(c3DVf mpCentre,uint32 liParticles);
void GenerateDamageParticles(c3DVf mpCentre);
#endif
