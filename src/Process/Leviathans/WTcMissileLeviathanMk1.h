#ifndef __WTCMISSILELEVIATHANMK1_H__
#define __WTCMISSILELEVIATHANMK1_H__

class cMissileLeviathanMk1 : public cLeviathanSettings
{
public:
    void CreateData();

  string LeviathanName();
  uint8 LeviathanLevel();
  uint32 LeviathanType();
  cTexture *LeviathanTypeIcon();
};

#endif
