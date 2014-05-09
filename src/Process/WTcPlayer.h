#ifndef __WTCPLAYER_H__
#define __WTCPLAYER_H__

class cLeviathanComponent;
class cCombatStatusBox;

class cPlayer : public cProcess
{


   static vMissileSettings **mpMissileSettings;
public:
	float mfDodgeY,mfDodgeX;
	float mfThrust;

	cAudioObject *mAO;
	cModel *mpHull;
	cPoint *mpFollowShip;
	cImage *mpHealthDisplay;
	cImage *mpCannonDisplay;

	cCollisionObject *mpHullColl,*mpBeamColl,*mpWholeCollision;
	cBeam *mpBeamWeapon;

	cRGBA mcBeamColor;

	cText *mpThrust;
    uint8 miThrustChangeRate;

	cText *mpHealthText;

	cViewport *mpViewport;
	cCamera *mpCamera;

	//PLAYER_TARGETING_TYPE *mpTarget;

	cImage *mpTargetReticule;
	cText *mpTargetDistance;

	float mfReload;
	float mfMissileReload;

	cImage *mpMoveIcon;
	cTexture *mpSlideIcon;
	cTexture *mpBrakeIcon;

	float mfRackDisplayTimer;

	float Life;
	cRGBA mcHealthColor;

	cBeam *lpXDisp,*lpYDisp,*lpZDisp;
	cDamage mcBeamDamage;
	cDamage mcBulletDamage;
	float mfBulletReloadTime;

    static cMatrix4 HullMatrix;
    static cMomentum *lpMomentum;


	cPlayerShield *mpShields[8];

	float mfMomentumColor[4];

	cAudioObject *mpGunShotSound;
	cAudioObject *mpJetSound;
	cAudioObject *mpBeamSound;
	cAudioObject *mpHullSound;
	uint32 miHullSoundDelay;

    bool TargetingToggle;
	bool mbSlideToggle;
	bool mbMissileSelectToggle;
	cKeyToggle mcZoomToggle;
	cImage *mpViewportBorder;

	uint8 miMissileSlots[MISSILE_SLOTS];
    uint8 miMissileSelected;

    cImage *mpMissileRack;
    cImage *mpMissileSlots[MISSILE_SLOTS];

    cCombatStatusBox *mpTargetStatus;


public:
	cPlayer(cCamera *lpCamera);
	void Run();
	void Stop();

	bool UserSignal(SIGNAL lsSignal,void* lpData);

	void MuteSounds();
	void UnmuteSounds();

	void NextMissileType();

	void UpdateMissileRackDisplay();

	void NewTarget(cGameTarget lpTarget);

    void DisplayMissileRack(float lfTime);

	vMissileSettings **PrepMissileSettings();

	cGameTarget mcTargeting;
	cGameTarget mcPlayerTarget;
};

extern cPlayer *gpPlayer;



#endif
