#ifndef __WTCLEVIATHANSETTINGS_H__
#define __WTCLEVIATHANSETTINGS_H__

class cLeviathanSettings
{
  public:

  cLeviathanSettings();
  void Initialise(uint16 liComponents,uint16 liNodes);
  uint16 miNodes;
  cLeviathanComponentSettings **mpNodes;

  uint16 miComponents;
  cLeviathanComponentSettings **mpComponents;

  virtual void CreateData()=0;
  ~cLeviathanSettings();

  static cLeviathanComponentSettings *spLast;

  virtual string LeviathanName()=0;
  virtual uint8 LeviathanLevel()=0;
  virtual uint32 LeviathanType()=0;
  virtual cTexture *LeviathanTypeIcon()=0;

};

#endif
