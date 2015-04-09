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
#include "PhysicsManager.h"
#include "Kinect.h"

Player::Player(Ogre::Vector3 position, PhysicsManager *physManager, World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input) : 
	mWorld(world), mKinect(k), mSceneManager(sceneManager), mInputHandler(input)
{
	mPhysManager = physManager;
	//mPlayerObject = new GameObject(mWorld, mSceneManager);

	mAutoCallibrate = true;

	// For testing purposes 
	overlyBool = false; 

	//playerNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mPlayerObject = new GameObject(position, physManager, mWorld, mSceneManager, GameObject::PLAYER);

}

void Player::addOgreEntity(Ogre::String m)
{
	mPlayerObject->loadModel(m);
}

void Player::setScale(Ogre::Vector3 v)
{
	mPlayerObject->setScale(v);
	//playerNode->scale(v);
}


void Player::setPosition (Ogre::Vector3 p) 
{
	mPlayerObject->setPosition(p);
}

void 
Player::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	//mPlayerObject->Think(time);

	//playerNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
	//// We can move the single object around using the input manager ...

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
	//mSceneNode->setPosition(Ogre::Vector3(x, y, z));
	//mSceneNode->setOrientation(Qw, Qx, Qy, Qz);

	Ogre::Vector3 pos = mPlayerObject->getPosition();
	btVector3 Point = mPlayerObject->getFallRigidBody()->getCenterOfMassPosition();
	btVector3 test = mPlayerObject->getFallRigidBody()->getAngularVelocity();
	//btRigidBody *playerR = mPlayerObject->getFallRigidBody(); 
    //node->setPosition(Ogre::Vector3((float)Point[0], (float)Point[1], (float)Point[2]));

	//btTransform trans;
	//mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(trans); 
	//trans.setOrigin(); 
	//trans.setOrigin(BtOgre::Convert::toBullet(absPos));
	/*tr.setOrigin(BtOgre::Convert::toBullet(absPos));
	tr.setRotation(BtOgre::Convert::toBullet(absOrient));
	rigid->getMotionState()->setWorldTransform(tr);*/

	//	iter->RigidBody()->setLinearVelocity((btVector3(iter->CentralVelocity().LinearX, iter->CentralVelocity().LinearY, iter->CentralVelocity().LinearZ)));
	//iter->RigidBody()->setAngularVelocity((btVector3(iter->CentralVelocity().AngularX, iter->CentralVelocity().AngularY, iter->CentralVelocity().AngularZ)));
	//iter->RigidBody()->applyForce(btVector3(fx, fy, fz), btVector3(px, py, pz));

	
	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE)) 
		{
			btTransform trans;
		    mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(trans);	
			Ogre::Real x = trans.getOrigin().getX();
			Ogre::Real y = trans.getOrigin().getY();
			Ogre::Real z = trans.getOrigin().getZ();

			Ogre::Real Qx = trans.getRotation().getX();
			Ogre::Real Qy = trans.getRotation().getY();
			Ogre::Real Qz = trans.getRotation().getZ();
			Ogre::Real Qw = trans.getRotation().getW();
			
			mPlayerObject->setPosition(Ogre::Vector3(x, y, z));
			mPlayerObject->setOrientation(Ogre::Quaternion(Qw, Qx, Qy, Qz));
			mPhysManager->stepSimulation(time);
		} 
		else if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			/*Ogre::Real x = trans.getOrigin().getX() * time * COIN_SPEED;
				Ogre::Real y = trans.getOrigin().getY();
				Ogre::Real z = trans.getOrigin().getZ();
				mPlayerObject->getSceneNode()->setPosition(Ogre::Vector3(x, y, z));
				trans.setOrigin(btVector3(trans.getOrigin().getX() * time * COIN_SPEED, trans.getOrigin().getY(), trans.getOrigin().getZ()));
				mPlayerObject->getFallRigidBody()->getMotionState()->setWorldTransform(trans);*/
			btTransform ts;
		    mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(ts);	
			Ogre::Vector3 pos = mPlayerObject->getPosition(); 
			mPlayerObject->getFallRigidBody()->applyForce(btVector3(20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getFallRigidBody()->setLinearVelocity(btVector3(20, 0, 0));
			mPhysManager->stepSimulation(time);
			//mPlayerObject->getFallRigidBody()->applyForce(btVector3(time, 0, 0), Point);
			
			//mPlayerObject->setPosition(Ogre::Vector3((float)test[0] - COIN_SPEED, (float)Point[1], (float)Point[2]));
			//mPlayerObject->getFallRigidBody()->setAngularVelocity(btVector3(test.getX() * time, test.getY(), test.getZ()));
			
			//mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0)); 
			//mPlayerObject->setPosition(Ogre::Vector3(time * pos.x, 0, 0));

			/*btVector3 relativeForce = btVector3(0,10,0);
			btMatrix3x3& boxRot = mPlayerObject->getFallRigidBody()->getWorldTransform().getBasis();
			btVector3 correctedForce = boxRot * relativeForce;
			mPlayerObject->getFallRigidBody()->applyCentralForce(correctedForce);*/
			
			/*btVector3 relativeForce = btVector3(0,10,0);
			btTransform boxTrans;
			mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(boxTrans);
			btVector3 correctedForce = (boxTrans * relativeForce) - boxTrans.getOrigin();
			mPlayerObject->getFallRigidBody()->applyCentralForce(correctedForce);*/

			//mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0));
			

		}
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			btTransform ts;
		    mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(ts);	
			Ogre::Vector3 pos = mPlayerObject->getPosition(); 
			mPlayerObject->getFallRigidBody()->applyForce(btVector3(- 20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getFallRigidBody()->setLinearVelocity(btVector3(- 20, 0, 0));
			mPhysManager->stepSimulation(time);
			//mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED, 0, 0));
		}

		 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
		 {
			 btTransform ts;
		    mPlayerObject->getFallRigidBody()->getMotionState()->getWorldTransform(ts);	
			Ogre::Vector3 pos = mPlayerObject->getPosition(); 
			mPlayerObject->getFallRigidBody()->applyForce(btVector3(0, -20, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getFallRigidBody()->setLinearVelocity(btVector3(0, 10, 0));
			mPhysManager->stepSimulation(time);
			 //mPlayerObject->translate(Ogre::Vector3(0, time*COIN_SPEED, 0));
			 //mPlayerObject->getFallRigidBody()->applyCentralImpulse(mPlayerObject->getFallRigidBody()->getWorldTransform().getBasis().getColumn(2) * -20 * time);
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			mPlayerObject->translate(Ogre::Vector3(0, -time*COIN_SPEED, 0));
			//mPlayerObject->getFallRigidBody()->applyCentralImpulse(mPlayerObject->getFallRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
		}
		
		//checkCollision();
		 //mPhysManager->stepSimulation(time);
	}
}


