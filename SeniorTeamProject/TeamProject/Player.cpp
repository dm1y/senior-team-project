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

	if (mAutoCallibrate) {
//		mKinect->callibrate(4.0f, [this]() { });
//		mEnableKinect = true;
	}

	// If kinect is enabled 
	if (mEnableKinect) 
	{
		// add code here for movement via kinect sensor 

		//mPlayerObject->translate(mKinect->leftRightAngle(), 0, 0); 
		//playerNode->translate(mKinect->leftRightAngle(), 0, 0);
		//angle2 = mKinect->frontBackAngle() * 0.8f *  mKinectSensitivityFB;

		overlyBool = true; 

	}

	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0));
		}
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED, 0, 0));
		}

		 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
		 {
			 mPlayerObject->translate(Ogre::Vector3(0, time*COIN_SPEED, 0));
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			mPlayerObject->translate(Ogre::Vector3(0, -time*COIN_SPEED, 0));
		}
		
		checkCollision();
	}
}

void Player::checkCollision()
{
	Ogre::Vector3 MTD;

	std::list<GameObject*> worldObjs = mWorld->getWorldObjects();

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
}
