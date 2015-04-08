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

}

void Player::addOgreEntity(Ogre::String m)
{
	mPlayerObject->loadModel(m);
}

void Player::setScale(Ogre::Vector3 v)
{
	mPlayerObject->setScale(v);


	mPlayerObject->setPosition(Ogre::Vector3(50, 0, 0));
	//playerNode->scale(v);
}

void 
Player::Think(float time)
{
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
	}
	if (mInputHandler->IsKeyDown(OIS::KC_TAB))
	{
		mEnableKeyboard = true;
		mEnableKinect = false;
	}

	if (mAutoCallibrate) {
//		mKinect->callibrate(4.0f, [this]() { });
//		mEnableKinect = true;
	}

	// If kinect is enabled 
	if (mEnableKinect) 
	{
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
		
		//mPlayerObject->translate(mKinect->leftRightAngle(), 0, 0); 
		//playerNode->translate(mKinect->leftRightAngle(), 0, 0);
		//angle2 = mKinect->frontBackAngle() * 0.8f *  mKinectSensitivityFB;

		overlyBool = true; 

	}

			vector<GameObject*> gameObjects = mWorld->getWorldObjects();
		/*
		gameObjects[0]->setPosition(10 * mKinect->trackLeftHand() + Ogre::Vector3(0, 50, 0));
		gameObjects[1]->setPosition(10 * mKinect->trackRightHand() + Ogre::Vector3(0, 50, 0));
		*/

		vector<Ogre::Vector3> skeletonNodes = getSkeletonNodes();

		int i = 0;

		for(; i < gameObjects.size(); i++)
		{
			gameObjects[i]->setPosition(10 * skeletonNodes[i] + Ogre::Vector3(-75, 25, 0));
		}

		//mPlayerObject->setPosition(5 * mKinect->trackRightHand());
	
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
			 mPlayerObject->translate(Ogre::Vector3(0, time*COIN_SPEED, 0));
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_N))
		{
			mPlayerObject->translate(Ogre::Vector3(0, -time*COIN_SPEED, 0));
		}
		
		//checkCollision();
	}
}

void
Player::getSkeletonAngles(Ogre::Degree &angle, Ogre::Degree &angle2)
{
	angle = mKinect->leftRightAngle();
	angle2 = mKinect->frontBackAngle();

	//angle = mKinect->fLeftRight();
	//angle2 = mKinect->fFrontBack();
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
	/*
	Ogre::Vector3 MTD;

	std::vector<GameObject*> worldObjs = mWorld->getWorldObjects();

	for(GameObject* go : worldObjs)
	{

		if (mPlayerObject->collides(go, MTD))
		{
			go->setScale(Ogre::Vector3(10,10,10));
		}
		else
		{
			go->setScale(Ogre::Vector3(3,3,3));
		}
	}
	*/
}
