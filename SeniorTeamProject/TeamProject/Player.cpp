#include "Player.h"
#include "GameObject.h"
#include "World.h"
#include "OgreVector3.h"
#include "Receivers.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "InputHandler.h"
#include <list>
#include <ois/ois.h>

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

#include "Kinect.h"

Player::Player(World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input) : 
	mWorld(world), mKinect(k), mSceneManager(sceneManager), mInputHandler(input)
{
	//mPlayerObject = new GameObject(mWorld, mSceneManager);

	mAutoCallibrate = true;

	// For testing purposes 
	overlyBool = false; 

	//playerNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mPlayerObject = new GameObject(mWorld, mSceneManager, GameObject::PLAYER);

	mEnableKinect = false;
	lineVisible = true;
	initSkel = false;
	//drawSkeleton();
}

void Player::addOgreEntity(Ogre::String m)
{
	mPlayerObject->loadModel(m);
}

void Player::setScale(Ogre::Vector3 v)
{
	mPlayerObject->setScale(v);


	mPlayerObject->setPosition(Ogre::Vector3(50, 30, 30));
	mPlayerObject->setOrientation(Ogre::Quaternion(0, 0, -45, 45));
	//playerNode->scale(v);
}

void 
Player::Think(float time)
{
	mPlayerObject->Think(time);

	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	//playerNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
	//// We can move the single object around using the input manager ...
	
	if (overlyBool)
		overly->show();

	// testing kinect 
	if (mInputHandler->IsKeyDown(OIS::KC_SPACE))
	{
		mEnableKeyboard = false;
		mEnableKinect = true; 
		overlyBool = true;
	}
	/*
	if (mInputHandler->IsKeyDown(OIS::KC_TAB))
	{
		mEnableKeyboard = true;
		mEnableKinect = false;
		overlyBool = false;
	}*/
	
	if (mAutoCallibrate) {
//		mKinect->callibrate(4.0f, [this]() { });
//		mEnableKinect = true;
	}

	// If kinect is enabled 
	if (mEnableKinect) 
	{
		if (mInputHandler->IsKeyDown(OIS::KC_LSHIFT))
			mKinect->standingOrSeated = false;
		if (mInputHandler->IsKeyDown(OIS::KC_RSHIFT))
			mKinect->standingOrSeated = true;
		
		//detectSway(time);
		detectTurn(time);
	}

	drawSkeleton();

	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		if (mInputHandler->IsKeyDown(OIS::KC_B))
		{
			mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0));
		}
		else if (mInputHandler->IsKeyDown(OIS::KC_M))
		{
			mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED, 0, 0));
		}

		 else if (mInputHandler->IsKeyDown(OIS::KC_J))
		 {
			 mPlayerObject->translate(Ogre::Vector3(0, 0, time*COIN_SPEED));
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_N))
		{
			mPlayerObject->translate(Ogre::Vector3(0, 0, -time*COIN_SPEED));
		}
		
		//checkCollision();
	}
}

void
Player::detectSway(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	Ogre::Degree leftRightAngle = Ogre::Degree(0);
	Ogre::Degree frontBackAngle = Ogre::Degree(0);

	getSkeletonAngles(leftRightAngle, frontBackAngle);
	
	if (leftRightAngle.valueDegrees() < 0)
		mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED / 2, 0, 0));

	if (leftRightAngle.valueDegrees() > 0)
		mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED / 2, 0, 0));

	if (frontBackAngle.valueDegrees() < 0)
		mPlayerObject->translate(Ogre::Vector3(0, 0, time * COIN_SPEED / 2));

	if (frontBackAngle.valueDegrees() > 0)
		mPlayerObject->translate(Ogre::Vector3(0, 0, -time * COIN_SPEED / 2));
}

void
Player::detectTurn(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;


	vector<Ogre::Vector3> skeletonNodes = getSkeletonNodes();

	//RIGHT TURN
	if (skeletonNodes[NUI_SKELETON_POSITION_SHOULDER_LEFT].z < skeletonNodes[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z)
		mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED / 2, 0, 0));
	
	//LEFT TURN
	if (skeletonNodes[NUI_SKELETON_POSITION_SHOULDER_LEFT].z > skeletonNodes[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z)
		mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED / 2, 0, 0));

	//ARMS IN FRONT
	if (skeletonNodes[NUI_SKELETON_POSITION_HAND_LEFT].z < skeletonNodes[NUI_SKELETON_POSITION_SPINE].z &&
		skeletonNodes[NUI_SKELETON_POSITION_HAND_RIGHT].z < skeletonNodes[NUI_SKELETON_POSITION_SPINE].z)
		mPlayerObject->translate(Ogre::Vector3(0, 0, time * COIN_SPEED / 2));
	
	//ARMS IN BACK
	if (skeletonNodes[NUI_SKELETON_POSITION_HAND_LEFT].z > skeletonNodes[NUI_SKELETON_POSITION_SPINE].z &&
		skeletonNodes[NUI_SKELETON_POSITION_HAND_RIGHT].z > skeletonNodes[NUI_SKELETON_POSITION_SPINE].z)
		mPlayerObject->translate(Ogre::Vector3(0, 0, -time * COIN_SPEED / 2));
}

void
Player::getSkeletonAngles(Ogre::Degree &angle, Ogre::Degree &angle2)
{
	angle = mKinect->leftRightAngle();
	angle2 = mKinect->frontBackAngle();
}

std::vector<Ogre::Vector3>
Player::getSkeletonNodes() 
{
	vector<Ogre::Vector3> nodes;
	nodes = mKinect->getSkeletonNodes();
	return nodes;
}

void Player::checkCollision()
{
}

void
Player::drawSkeleton()
{
	//TORSO
	drawLine("head2ShoulderCenter", NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER);
	drawLine("shoulderCenter2ShoulderLeft", NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT);
    drawLine("shoulderCenter2ShoulderRight", NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT);
    drawLine("shoulderCenter2Spine", NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE);
    drawLine("spine2HipCenter", NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER);

	
    drawLine("hipCenter2HipLeft", NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT);
    drawLine("hipCenter2HipRight", NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT);

    //LEFT ARM
    drawLine("shoulderLeft2ElbowLeft", NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT);
    drawLine("elbowLeft2WristLeft", NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT);
    drawLine("wristLeft2HandLeft", NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT);

    //RIGHT ARM
    drawLine("shoulderRight2ElbowRight", NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT);
    drawLine("elbowRight2WristRight", NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT);
    drawLine("wristRight2HandRight", NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT);

    //LEFT LEG
    drawLine("hipLeft2KneeLeft", NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT);
    drawLine("kneeLeft2AnkleLeft", NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT);
    drawLine("ankleLeft2FootLeft", NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT);

    //RIGHT LEG
    drawLine("hipRight2KneeRight", NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT);
    drawLine("kneeRight2AnkleRight", NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT);
    drawLine("ankleRight2FootRight", NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT);

	initSkel = true;
}

void
Player::createLine(std::string bone, int joint1, int joint2)
{
	Ogre::ManualObject* myManualObject =  mSceneManager->createManualObject(bone); 
	myManualObject->setDynamic(true);
	Ogre::SceneNode* myManualObjectNode = mSceneManager->getRootSceneNode()->createChildSceneNode(bone + "_node"); 
 
	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create(bone + "Material","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);

	myManualObjectNode->attachObject(myManualObject);

}

void
Player::drawLine(std::string bone, int joint1, int joint2)
{
	if (!initSkel)
		createLine(bone, joint1, joint2);
	else if (initSkel)
	{
		vector<Ogre::Vector3> skeletonNodes = getSkeletonNodes();
		Ogre::ManualObject* myManualObject = mSceneManager->getManualObject(bone);
		
		if (lineVisible)
		{
			Ogre::Vector3 bone1 = 10 * skeletonNodes[joint1] + Ogre::Vector3(0, 30, 0);
			Ogre::Vector3 bone2 = 10 * skeletonNodes[joint2] + Ogre::Vector3(0, 30, 0);
						
			myManualObject->begin(bone + "Material", Ogre::RenderOperation::OT_LINE_LIST);
			myManualObject->position(bone1.x, bone1.y, bone1.z); 
			myManualObject->position(bone2.x, bone2.y, bone2.z); 
			myManualObject->end();

			lineVisible = false;
		}
		else if (!lineVisible)
		{
			myManualObject->clear();
			lineVisible = true;
		}
	}
}

void
Player::clearLine(std::string bone)
{
	mSceneManager->destroyManualObject(bone);
	mSceneManager->getRootSceneNode()->removeAndDestroyChild(bone + "_node");
}