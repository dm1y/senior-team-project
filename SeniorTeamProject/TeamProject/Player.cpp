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
#include "Camera.h"

Player::Player(DynamicObject *dynamic, Ogre::Vector3 position, PhysicsManager *physManager, 
			   World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input, GameCamera *camera) : 
	mWorld(world), mKinect(k), mSceneManager(sceneManager), mInputHandler(input), mCamera(camera)
{
	mPhysManager = physManager;
	
	// For Kinect later on 
	mAutoCallibrate = true;

	// Player physics
	isJumping = false; 
	onGround = true;
	angle = 0;
	h = 0; 

	// For testing purposes 
	//overlyBool = false; 
//	btCollisionObject s = new btCapsuleShape();
	
	// Create player node using GameObject class 
	mPlayerObject = dynamic;
	mPlayerObject->setPosition(position);
	mPlayerObject->addToOgreScene(mSceneManager, "player");

	// Children nodes for camera in 3rd person perspective 
	sightNode = mPlayerObject->mSceneNode->createChildSceneNode("player_sight", Ogre::Vector3 (0, 0,  100));
	camNode = mPlayerObject->mSceneNode->createChildSceneNode("player_cam", Ogre::Vector3 (0, 50, -100));

	// Sets up Bullet 
	mPlayerObject->addToBullet(mPhysManager); 
	mPlayerObject->getRigidBody()->setActivationState(DISABLE_DEACTIVATION); 
	mPlayerObject->getRigidBody()->setAngularFactor(btVector3(0.0f,1.0f,0.0f));
	mPlayerObject->synchWithBullet();
}
void Player::makeGhostObject() 
{
	btTransform startTransform;
	startTransform.setIdentity ();
	startTransform.setOrigin (btVector3(0.0, 4.0, 0.0));

	//GhostObject Setup 
	m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);
	btScalar characterHeight=1.75;
	btScalar characterWidth =1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
	btScalar stepHeight = btScalar(0.35);
}
// Adds player object to the scene
void Player::addToScene()
{
	mPlayerObject->addToOgreScene(mSceneManager);

	// Children nodes for camera in 3rd person perspective 
	sightNode = mPlayerObject->mSceneNode->createChildSceneNode("player_sight", Ogre::Vector3 (0, 0, 100));
	camNode = mPlayerObject->mSceneNode->createChildSceneNode("player_cam", Ogre::Vector3 (0, 50, -100));
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
	
	//if (mPlayerObject->fallRigidBody->checkCollideWith(NULL))
	//{
	//	mPlayerObject->setPosition(Ogre::Vector3(0, 10,-10));
	//}

	if (mPlayerObject->position == Ogre::Vector3 (0, 15,-10)) {
		mPlayerObject->setPosition(Ogre::Vector3 (0, 15,-10));
	}

	//TODO use ray tracing/testing to detect ground collision 
#pragma region Controls 
	btTransform ts;

	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{
		// Left 
		if (mInputHandler->IsKeyDown(OIS::KC_LEFT) && onGround)
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);

			
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
		}

		// Right 
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT) && onGround)
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));

			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(-1, 0, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(-10, 0, 0));			
		}
		if (mInputHandler->IsKeyDown(OIS::KC_M) && onGround)
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,-1,0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);

			
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
		} 
		else if (mInputHandler->IsKeyDown(OIS::KC_N) && onGround)
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,1,0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);

			
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
		}
		if (mInputHandler->IsKeyDown(OIS::KC_RIGHT) && onGround)
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));

			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(-1, 0, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(-10, 0, 0));			
		}
		if (mInputHandler->IsKeyDown(OIS::KC_O) && onGround)
		{
			//if (!isJumping)
			btVector3 angul = (mPlayerObject->fallRigidBody->getAngularVelocity());
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(mPlayerObject->fallRigidBody->getAngularVelocity().getX(), 0, mPlayerObject->fallRigidBody->getAngularVelocity().getZ()));
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 1));
			//mPlayerObject->fallRigidBody->setFriction(5);

			
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
		}

		// Right 
		else if (mInputHandler->IsKeyDown(OIS::KC_K) && onGround)
		{
			//if (!isJumping)

			mPlayerObject->fallRigidBody->setLinearVelocity(mPlayerObject->fallRigidBody->getAngularVelocity() * -5);
			//mPlayerObject->fallRigidBody->setFriction(5);
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(-1, 0, 0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(-10, 0, 0));			
		}
		// Up 
		else if (mInputHandler->IsKeyDown(OIS::KC_UP) && onGround)
		 {
			//if (!isJumping)
			//mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			
			//mPlayerObject->fallRigidBody->setFriction(1);
			
			//mPlayerObject->fallRigidBody->applyCentralImpulse(mPlayerObject->fallRigidBody->getAngularVelocity());
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0,0,-1));
			//mPlayerObject->fallRigidBody->setLinearVelocity(mPlayerObject->fallRigidBody->getAngularVelocity());
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, 5));
			
		}

		// Down 
		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN) && onGround)
		{
			//if (!isJumping)
				mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));

			//mPlayerObject->fallRigidBody->setFriction(1);
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0, 0, 1));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, -5));
			
		}

		// "Jump" 
		else if (mInputHandler->IsKeyDown(OIS::KC_RSHIFT) && !isJumping)
		{
			//isJumping = true;
			h +=10;

			if (h < 20) {
 
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0, 10, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 10, 0));
			mPlayerObject->fallRigidBody->applyGravity();
			} else if (h > 30) {
				h = 0; 
			}

			
		}

		// "Crouch"
		else if (mInputHandler->IsKeyDown(OIS::KC_L) && !isJumping)
		{
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setFriction(5);
			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0, -1, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, -5, 0));
		}

		else if (isJumping)
		{
			//isJumping = false;
		}


		mPlayerObject->synchWithBullet();
		//mCamera->updatePosition(mPlayerObject->position);

#pragma endregion Input controls for keyboard 
	}
}

