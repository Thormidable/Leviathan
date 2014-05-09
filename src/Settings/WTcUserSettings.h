#ifndef __WTUSERSETTINGS_H__
#define __WTUSERSETTINGS_H__

class cUserSettings : public cSettings
{
public:
	cUserSettings(){};
	~cUserSettings(){};
	void Settings();

	void UserWindowSizeUpdate();

    static void FileSettings();

 static float mfMouseThrustSensitivity;
 static float mfMouseXAngleSensitivity;
 static float mfMouseYAngleSensitivity;
 static float mfPlanningLeviathanRotationSensitivity;
 static bool mbYawPitchControls;
 static bool mbKeyThrustControl;

};


#endif
