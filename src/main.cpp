
#include "main.h"



bool gbQuit=false;
cRenderObject *gpRenderCollision=0;
#if ACTIVATE_SOUND
	bool gbSoundOn=true;
#else
	bool gbSoundOn=false;
#endif

#if WT_OS_TYPE==OS_WIN32
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{

	_START_PROGRAM(cCore,cUserSettings,hInstance);
	return 0;
}


#endif

#if WT_OS_TYPE==OS_LINUX
int main ()
{
	_START_PROGRAM(cCore,cUserSettings);
	return 0;
}

#endif



