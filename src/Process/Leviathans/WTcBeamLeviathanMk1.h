#ifndef __WTCBEAMLEVIATHANMK1_H__
#define __WTCBEAMLEVIATHANMK1_H__

class cBeamLeviathanMk1 : public cLeviathanSettings
{
public:
    void CreateData();

  string LeviathanName();
  uint8 LeviathanLevel();
  uint32 LeviathanType();
  cTexture *LeviathanTypeIcon();
};

#endif
