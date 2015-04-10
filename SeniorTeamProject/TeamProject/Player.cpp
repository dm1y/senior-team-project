#include "Player.h"
#include "DynamicObject.h"
#include "World.h"
#include "OgreVector3.h"
//#include "Receivers.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "InputHandler.h"
//#include <list>
#include <ois/ois.h>

//#include "OgreOverlayManager.h"
//#include "OgreOverlay.h"
//#include "OgreFontManager.h"
//#include "OgreTextAreaOverlayElement.h"
#include "PhysicsManager.h"
#include "Kinect.h"

Player::Player(Ogre::String name, btCollisionShape *collisionShape, Ogre::Vector3 position, 
			   PhysicsManager *physManager, World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input) : 
	meshName(name), mWorld(world), mKinect(k), mSceneManager(sceneManager), mInputHandler(input)
{
	mPhysManager = physManager;

	// For Kinect later on 
	mAutoCallibrate = true;

	// For testing purposes 
	//overlyBool = false; 

	// Create player node using GameObject class 
	mPlayerObject = new DynamicObject(name, collisionShape, position);
}

// Adds player object to the scene
void Player::addToScene()
{
	mPlayerObject->addToOgreScene(mSceneManager);
}

// Sets the scale of player to resize 
void Player::setScale(Ogre::Vector3 v)
{
	mPlayerObject->setScale(v);
}

// Sets the position 
void Player::setPosition (Ogre::Vector3 p) 
{
	mPlayerObject->setPosition(p);
}

// Basically the update method for the Player class. 
void 
Player::Think(float time)
{

#pragma region Kinect
	//if (overlyBool)
	//	overly->show();
	// testing kinect 
	//if (mInputHandler->IsKeyDown(OIS::KC_SPACE))
	///{
	//	mEnableKeyboard = false;
	//	mEnableKinect = true; 
	//}
	if (mAutoCallibrate) {
//		mKinect->callibrate(4.0f, [this]() { });
//		mEnableKinect = true;
	}
	// If kinect is enabled 
	//if (mEnableKinect) 
	//{
		// add code here for movement via kinect sensor 
		//mPlayerObject->translate(mKinect->leftRightAngle(), 0, 0); 
		//playerNode->translate(mKinect->leftRightAngle(), 0, 0);
		//angle2 = mKinect->frontBackAngle() * 0.8f *  mKinectSensitivityFB;
	/*	overlyBool = true; 
	}*/
#pragma endregion End of Kinect code/Not used right now   
	
	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			/* Applies force to tuna can so it shifts to the left when you press the left key. 
			Only works if you press 'space' with it for some reason 
			Probably has something to do in stepSimulation but still looking into this.
			Waiting for Jordan's new "stepSimulation" method that he renamed as update to 
			see if problem will be resolved */
			//btTransform ts;
		 //   mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			//mPlayerObject->getRigidBody()->applyForce(btVector3(20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			//mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(20, 0, 0));
			//mPhysManager->stepSimulation(time);
		}
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			/* Applies force to tuna can so it shifts to the right when you press the right key. 
			Only works if you press 'space' with it for some reason 
			Probably has something to do in stepSimulation but still looking into this.
			Waiting for Jordan's new "stepSimulation" method that he renamed as update to 
			see if problem will be resolved */
			btTransform ts;
		 //   mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			//mPlayerObject->getRigidBody()->applyForce(btVector3(- 20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			//mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(- 20, 0, 0));
			//mPhysManager->stepSimulation(time);
		}
		 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
		 {
			/* Applies force to tuna can so it shifts upwards when you press the up key (kind of 
			simulating jump but need to fix stepSimulation to get actual flow instead of the current slow-mo). 
			Only works if you press 'space' with it for some reason 
			Probably has something to do in stepSimulation but still looking into this.
			Waiting for Jordan's new "stepSimulation" method that he renamed as update to 
			see if problem will be resolved */
			btTransform ts;
		 //   mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			////Ogre::Vector3 pos = mPlayerObject->getPosition(); 
			//mPlayerObject->getRigidBody()->applyForce(btVector3(0, -20, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			//mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(0, 10, 0));
			//mPhysManager->stepSimulation(time);
			 //mPlayerObject->translate(Ogre::Vector3(0, time*COIN_SPEED, 0));
			 //mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * -20 * time);
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			// Old code, haven't modified yet
//			mPlayerObject->translate(Ogre::Vector3(0, -time*COIN_SPEED, 0));
			//mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
		}
		
	}
}

