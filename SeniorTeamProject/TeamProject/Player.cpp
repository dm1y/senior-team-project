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

	Ogre::Entity *ent1 =SceneManager()->createEntity("Box001.mesh");
	Ogre::Entity *ent2 =SceneManager()->createEntity("coin.mesh");
	playerNode->attachObject(ent1);
	playerNode->attachObject(ent2);
	playerNode->scale(5,5,5);
	//setup();
}

//void Player::setup()
//{
//	mPlayerObject = new GameObject(GameObject::PLAYER);
//	mPlayerObject->loadModel("coin.mesh", mWorld->SceneManager());
//	mPlayerObject->setScale(Ogre::Vector3(5,6,10));
//}

void 
Player::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	// This is a pretty silly think method, but it gives you some ideas about how
	//  to proceed.  The single object will rotate

	// //mCoinNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
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
