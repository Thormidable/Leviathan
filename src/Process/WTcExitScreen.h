#ifndef __WTCEXITSCREEN_H__
#define __WTCEXITSCREEN_H__


//class cExitScreen : public cProcess
_PROCESS(cExitScreen)
{
 cImage *mpBackground;

 float TextColor[4];
 float mfColor;
 float mfColorStep;

 uint32 miTimer;
  // cExitScreens version of cProcess::Run().
 void Run();
public:

 // cExitScreens constructor. Should be used to initialise the program. Load files, create processes etc.
 cExitScreen();
 // cExitScreens destructor. Will kill and end cExitScreen, but will NOT end the program.
 void Stop();
};

#endif
