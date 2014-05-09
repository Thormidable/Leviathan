#ifndef __WTCGUNLEVIATHANMK1_H__
#define __WTCGUNLEVIATHANMK1_H__

class cGunLeviathanMk1 : public cLeviathanSettings
{
public:
    void CreateData();

  string LeviathanName();
  uint8 LeviathanLevel();
  uint32 LeviathanType();
  cTexture *LeviathanTypeIcon();
};

#endif
