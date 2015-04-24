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
	mEnableKinect = false;
	initSkel = false;

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
	mPlayerObject->addToOgreScene(mSceneManager);

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

	drawSkeleton();

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


void
Player::detectSway(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	Ogre::Degree leftRightAngle = Ogre::Degree(0);
	Ogre::Degree frontBackAngle = Ogre::Degree(0);

	getSkeletonAngles(leftRightAngle, frontBackAngle);
	
	/*
	if (leftRightAngle.valueDegrees() < 0)
		mPlayerObject->translate(Ogre::Vector3(time * COIN_SPEED / 2, 0, 0));

	if (leftRightAngle.valueDegrees() > 0)
		mPlayerObject->translate(Ogre::Vector3(-time * COIN_SPEED / 2, 0, 0));

	if (frontBackAngle.valueDegrees() < 0)
		mPlayerObject->translate(Ogre::Vector3(0, 0, time * COIN_SPEED / 2));

	if (frontBackAngle.valueDegrees() > 0)
		mPlayerObject->translate(Ogre::Vector3(0, 0, -time * COIN_SPEED / 2));
	*/
}

void
Player::detectTurn(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;


	vector<Ogre::Vector3> skeletonNodes = getSkeletonNodes();

	/*
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
	*/
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
		
		myManualObject->clear();

		Ogre::Vector3 bone1 = 20 * skeletonNodes[joint1] + Ogre::Vector3(-50, 30, 20);
		Ogre::Vector3 bone2 = 20 * skeletonNodes[joint2] + Ogre::Vector3(-50, 30, 20);
						
		myManualObject->begin(bone + "Material", Ogre::RenderOperation::OT_LINE_LIST);
		myManualObject->position(bone1.x, bone1.y, bone1.z); 
		myManualObject->position(bone2.x, bone2.y, bone2.z); 
		myManualObject->end();
	}
}

void
Player::clearLine(std::string bone)
{
	mSceneManager->destroyManualObject(bone);
	mSceneManager->getRootSceneNode()->removeAndDestroyChild(bone + "_node");
}
