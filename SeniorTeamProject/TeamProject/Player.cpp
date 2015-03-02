#include "Player.h"
#include "GameObject.h"
#include "World.h"
#include "OgreVector3.h"
#include "Receivers.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "InputHandler.h"
#include <ois/ois.h>

Player::Player(World *world, /*Kinect *k,*/ Ogre::SceneManager *sceneManager, InputHandler *input) : 
	mWorld(world), /*mKinect(k),*/ mSceneManager(sceneManager), mInputHandler(input)
{
	playerNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
}

void Player::addOgreEntity(Ogre::String m)
{
	Ogre::Entity *ent = SceneManager()->createEntity(m);
	playerNode->attachObject(ent);
}

void Player::setScale(Ogre::Vector3 v)
{
	playerNode->scale(v);
}

void 
Player::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	// This is a pretty silly think method, but it gives you some ideas about how
	//  to proceed.  The single object will rotate

	playerNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
	//// We can move the single object around using the input manager ...

	 if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
	 {
		 playerNode->translate(time * COIN_SPEED, 0, 0);
	 }
	 else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
	 {
		 playerNode->translate(-time * COIN_SPEED, 0, 0);
	 }

	 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
	 {
		 playerNode->translate(0, time*COIN_SPEED, 0);
	 }

	 else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
	 {
		 playerNode->translate(0, -time*COIN_SPEED, 0);
	 }
}
