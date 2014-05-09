#ifndef __WTCFOUNDATIONSETTINGS_H__
#define __WTCFOUNDATIONSETTINGS_H__

class cFoundationSettingsList;
class cFoundationTracking;

class cFoundationSettings
{
 friend class cFoundationSettingsList;
    cLeviathanComponentSettings *mpComponent;
    cMatrix4 mmMatrix;
public:
    cFoundationSettings();

};

class cFoundationSettingsList
{
    friend class cFoundationTracking;
    cFoundationSettings *mpFoundations;
    uint8 miFoundations;
public:
    cFoundationSettingsList();
    cFoundationSettingsList(uint8 liFoundations);
    cFoundationSettingsList(cFoundationSettingsList *lpFoundSet);
    cFoundationSettingsList(cLeviathanComponentSettings *lpComponent,cMatrix4 lpMatrix);
    ~cFoundationSettingsList();
    void Foundation(uint8 liFoundation, cLeviathanComponentSettings *lpComponent,cMatrix4 lpMatrix);
    cFoundationSettings *Foundation(uint8 liFoundation);
    cLeviathanComponentSettings *Component(uint8 liFoundation);
    cMatrix4 *Matrix(uint8 liFoundation);
    void Set(cFoundationSettingsList *lpList);
    cFoundationSettingsList *operator=(cFoundationSettingsList *lpList);
    cFoundationSettingsList &operator=(cFoundationSettingsList &lpList);
};

#endif
