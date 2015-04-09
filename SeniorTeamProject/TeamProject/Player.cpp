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

	// For Kinect later on 
	mAutoCallibrate = true;

	// For testing purposes 
	overlyBool = false; 

	// Create player node using GameObject class 
	mPlayerObject = new GameObject(position, physManager, mWorld, mSceneManager, GameObject::PLAYER);

}

// Uses mesh name to create the entity 
void Player::addOgreEntity(Ogre::String m)
{
	mPlayerObject->loadModel(m);
}

// Sets the scale of player to resize 
void Player::setScale(Ogre::Vector3 v)
{
	mPlayerObject->setScale(v);
}

// Sets the position -- will probably remove 
void Player::setPosition (Ogre::Vector3 p) 
{
	mPlayerObject->setPosition(p);
}

// Basically the update method for the Player class. 
void 
Player::Think(float time)
{
	// Galles code. Not really used 
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

#pragma region Old_code 
	//mPlayerObject->Think(time);

	//playerNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
	//// We can move the single object around using the input manager ...
	#pragma endregion end of old collision code 

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

#pragma region TestCode 
	//mSceneNode->setPosition(Ogre::Vector3(x, y, z));
	//mSceneNode->setOrientation(Qw, Qx, Qy, Qz);
	Ogre::Vector3 pos = mPlayerObject->getPosition();
	btVector3 Point = mPlayerObject->getRigidBody()->getCenterOfMassPosition();
	btVector3 test = mPlayerObject->getRigidBody()->getAngularVelocity();
	//btRigidBody *playerR = mPlayerObject->getRigidBody(); 
    //node->setPosition(Ogre::Vector3((float)Point[0], (float)Point[1], (float)Point[2]));
	//btTransform trans;
	//mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(trans); 
	//trans.setOrigin(); 
	//trans.setOrigin(BtOgre::Convert::toBullet(absPos));
	/*tr.setOrigin(BtOgre::Convert::toBullet(absPos));
	tr.setRotation(BtOgre::Convert::toBullet(absOrient));
	rigid->getMotionState()->setWorldTransform(tr);*/
	//	iter->RigidBody()->setLinearVelocity((btVector3(iter->CentralVelocity().LinearX, iter->CentralVelocity().LinearY, iter->CentralVelocity().LinearZ)));
	//iter->RigidBody()->setAngularVelocity((btVector3(iter->CentralVelocity().AngularX, iter->CentralVelocity().AngularY, iter->CentralVelocity().AngularZ)));
	//iter->RigidBody()->applyForce(btVector3(fx, fy, fz), btVector3(px, py, pz));
#pragma endregion Code to get objects moving (unsuccessful) -- could recycle so keeping it commented out for now 
	
	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		//mPhysManager->stepSimulation(time);
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE)) 
		{
#pragma region JordansFallingCodeFromCoinClass 
			btTransform trans;
		    mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(trans);	
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
#pragma endregion still probably useful in understanding how Bullet works. Basically has "player" movement fall when space is pressed.  
		} 
		else if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			/* Applies force to tuna can so it shifts to the left when you press the left key. 
			Only works if you press 'space' with it for some reason 
			Probably has something to do in stepSimulation but still looking into this.
			Waiting for Jordan's new "stepSimulation" method that he renamed as update to 
			see if problem will be resolved */
			btTransform ts;
		    mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			mPlayerObject->getRigidBody()->applyForce(btVector3(20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(20, 0, 0));
			mPhysManager->stepSimulation(time);

#pragma region FailedCode 
			//mPlayerObject->getRigidBody()->applyForce(btVector3(time, 0, 0), Point);
			
			//mPlayerObject->setPosition(Ogre::Vector3((float)test[0] - COIN_SPEED, (float)Point[1], (float)Point[2]));
			//mPlayerObject->getRigidBody()->setAngularVelocity(btVector3(test.getX() * time, test.getY(), test.getZ()));
			
			//mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0)); 
			//mPlayerObject->setPosition(Ogre::Vector3(time * pos.x, 0, 0));

			/*btVector3 relativeForce = btVector3(0,10,0);
			btMatrix3x3& boxRot = mPlayerObject->getRigidBody()->getWorldTransform().getBasis();
			btVector3 correctedForce = boxRot * relativeForce;
			mPlayerObject->getRigidBody()->applyCentralForce(correctedForce);*/
			
			/*btVector3 relativeForce = btVector3(0,10,0);
			btTransform boxTrans;
			mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(boxTrans);
			btVector3 correctedForce = (boxTrans * relativeForce) - boxTrans.getOrigin();
			mPlayerObject->getRigidBody()->applyCentralForce(correctedForce);*/

			//mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED, 0, 0));
#pragma endregion Might still be recyclable/useable

		}
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			/* Applies force to tuna can so it shifts to the right when you press the right key. 
			Only works if you press 'space' with it for some reason 
			Probably has something to do in stepSimulation but still looking into this.
			Waiting for Jordan's new "stepSimulation" method that he renamed as update to 
			see if problem will be resolved */
			btTransform ts;
		    mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			mPlayerObject->getRigidBody()->applyForce(btVector3(- 20, 0, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(- 20, 0, 0));
			mPhysManager->stepSimulation(time);
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
		    mPlayerObject->getRigidBody()->getMotionState()->getWorldTransform(ts);	
			//Ogre::Vector3 pos = mPlayerObject->getPosition(); 
			mPlayerObject->getRigidBody()->applyForce(btVector3(0, -20, 0), btVector3(ts.getOrigin().getX(), ts.getOrigin().getY(), ts.getOrigin().getZ())); 
			mPlayerObject->getRigidBody()->setLinearVelocity(btVector3(0, 10, 0));
			mPhysManager->stepSimulation(time);
			 //mPlayerObject->translate(Ogre::Vector3(0, time*COIN_SPEED, 0));
			 //mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * -20 * time);
		 }

		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			// Old code, haven't modified yet
			mPlayerObject->translate(Ogre::Vector3(0, -time*COIN_SPEED, 0));
			//mPlayerObject->getRigidBody()->applyCentralImpulse(mPlayerObject->getRigidBody()->getWorldTransform().getBasis().getColumn(2) * 20 * time);
		}
		
	}
}


