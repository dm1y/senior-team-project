#pragma once
#define KINECT_AVAILABLE
#include <windows.h>
#include <ole2.h>

#ifdef KINECT_AVAILABLE

#include "NuiApi.h"
#pragma comment(lib, "Kinect10.lib")
#endif
#include "OgreVector2.h"
#include "Receivers.h"


const float CALIBRATION_TIME = 4.0f;

namespace Ogre
{
	class Overlay;
	class OverlayElement;
}




class Kinect : public SessionListener
{
public:
	Kinect(void);
	~Kinect(void);
	HRESULT initSensor();
	void update(float);

	void callibrate(float delay = 4.0f, std::function<void(void)> callback = NULL);
	void shutdown();

	Ogre::Degree leftRightAngle() { return mLeftRightAngle; }
	Ogre::Degree frontBackAngle() { return mFrontBackAngle; }

	float fLeftRight() { return mLeftRightAngle.valueDegrees(); }
	float fFrontBack() { return mFrontBackAngle.valueDegrees(); }

	bool standingOrSeated;
	bool fStandSeat() { return standingOrSeated; }

	Ogre::Vector3 getNodePositions() { return mSkelPositions[NUI_SKELETON_POSITION_COUNT]; }

	Ogre::Vector3 trackRightHand() { return mSkelPositions[NUI_SKELETON_POSITION_HAND_RIGHT]; }
	Ogre::Vector3 trackLeftHand() { return mSkelPositions[NUI_SKELETON_POSITION_HAND_LEFT]; }

	std::vector<Ogre::Vector3> getSkeletonNodes();

    bool callibrating() { return mCallibrating; }
    void cancelCallibration();
	void addSkelListener(KinectSkelMsgr *listener);
	virtual void StartSession();
	virtual void EndSession();

	
	Ogre::Real detectSway();
	Ogre::Real detectLean();
	int detectArm();
	Ogre::Real detectTurn();
	int detectJump();
	void getSkeletonAngles(Ogre::Degree &angle, Ogre::Degree &angle2);

	Ogre::Real leanForwardMax;
	Ogre::Real leanBackMax;
	Ogre::Real swayLeftMax;
	Ogre::Real swayRightMax;
	Ogre::Real leftRotationMax;
	Ogre::Real rightRotationMax;
	Ogre::Real leftLegLiftMax;
	Ogre::Real rightLegLiftMax;
	void performCallibration();

	Ogre::Real leftRightRotation;
	std::vector<Ogre::Vector3> initialPositions;

protected:

	void updateKinectSkeleton( );
	std::vector<KinectSkelMsgr *> mSkelListeners;

#ifdef KINECT_AVAILABLE
	// Current kinect
	INuiSensor *            m_pNuiSensor;
	BSTR                    m_instanceId;
	HANDLE        m_hNextSkeletonEvent;
	DWORD         m_SkeletonIds[NUI_SKELETON_COUNT];
	DWORD         m_TrackedSkeletonIds[NUI_SKELETON_MAX_TRACKED_COUNT];
	HANDLE        m_hThNuiProcess;
	HANDLE        m_hEvNuiProcessStop;
	Ogre::Vector3 mSkelPositions[NUI_SKELETON_POSITION_COUNT];

	static DWORD WINAPI     Nui_ProcessThread(LPVOID pParam);
	DWORD WINAPI            Nui_ProcessThread();
#endif

	bool   recenterNext;
	bool   updateDelay; 
	float  mTimeSinceLastLog;
	Ogre::Vector2 baseVectorDelta;

	Ogre::Degree mLeftRightAngle;
	Ogre::Degree mFrontBackAngle;
	Ogre::Degree mLeftRightTrue;

	float mTimeSinceLastUpdate;
	float mCalibrationClock;

	Ogre::Overlay *mToso1Overlay;
	Ogre::Overlay *mToso2Overlay;
	Ogre::Overlay *mCallibrationOverlay;
	bool mCallibrating;
	Ogre::OverlayElement *mCallibrationText;
    std::function<void()>  mCallibrationFinishedCallback;


};

