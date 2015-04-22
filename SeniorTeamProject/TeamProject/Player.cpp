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

Player::Player(DynamicObject *dynamic, Ogre::Vector3 position, PhysicsManager *physManager, 
			   World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input) : 
	mWorld(world), mKinect(k), mSceneManager(sceneManager), mInputHandler(input)
{
	mPhysManager = physManager;

	// For Kinect later on 
	mAutoCallibrate = true;


	// For testing purposes 
	//overlyBool = false; 
//	btCollisionObject s = new btCapsuleShape();
	
	// Create player node using GameObject class 
	mPlayerObject = dynamic;
	mPlayerObject->setPosition(position);
	mPlayerObject->addToOgreScene(mSceneManager);
	mPlayerObject->addToBullet(mPhysManager);
	mPlayerObject->getRigidBody()->isKinematicObject();
	//mPlayerObject->getRigidBody()->setCollisionShape(btCapsuleShape(5,1));
	mPlayerObject->synchWithBullet();
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
	
#pragma region Controls 
	btTransform ts;

	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		// Left 
		if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			//btVector3 p; 
			//p = btVector3(mPlayerObject->position.x, mPlayerObject->position.y, mPlayerObject->position.z);
			//mPlayerObject->fallRigidBody->applyCentralForce(btVector3(1, 0, 0));
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts);
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->applyForce(btVector3(1, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->applyForce(btVector3(1, 0, 0), mPlayerObject->fallRigidBody->getCenterOfMassPosition());
			//mPlayerObject->fallRigidBody->applyForce(btVector3(1, 0, 0), p);
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
			
			
		}

		// Right 
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			mPlayerObject->fallRigidBody->applyCentralForce(btVector3(-1, 0, 0));
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts); 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(-1, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(-10, 0, 0));
			//mPlayerObject->fallRigidBody->isActive();
			
		}

		// Up 
		 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
		 {
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts); 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(0, 0, -1), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, 5));
			//mPlayerObject->fallRigidBody->isActive();
			
		}

		// Down 
		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts); 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(0, 0, 1), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, -5));
			//mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
			//mPlayerObject->fallRigidBody->isActive();
			
		}

		// "Jump" 
		else if (mInputHandler->IsKeyDown(OIS::KC_RSHIFT))
		{
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts); 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(0, 1, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 5, 0));
			//mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
			//mPlayerObject->fallRigidBody->isActive();
			
		}

		// "Crouch"
		else if (mInputHandler->IsKeyDown(OIS::KC_L))
		{

			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts); 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(0, -1, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, -5, 0));
			
			//mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
			//mPlayerObject->fallRigidBody->isActive();
		}

		
		else if (mInputHandler->WasKeyDown(OIS::KC_LEFT) || mInputHandler->WasKeyDown(OIS::KC_RIGHT) || 
			mInputHandler->WasKeyDown(OIS::KC_UP) || mInputHandler->WasKeyDown(OIS::KC_DOWN)) {
			mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts);
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			mPlayerObject->fallRigidBody->applyForce(btVector3(0, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ()));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, 0));
			
		}
		mPlayerObject->synchWithBullet();

#pragma endregion Input controls for keyboard 
	}
}

