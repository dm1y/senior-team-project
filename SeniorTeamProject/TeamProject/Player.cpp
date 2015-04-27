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
#include <math.h>

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
	
	// Create player node using GameObject class 
	mPlayerObject = dynamic;
	mPlayerObject->setPosition(position);
	mPlayerObject->addToOgreScene(mSceneManager);


	// Children nodes for camera in 3rd person perspective 
	//sightNode = mPlayerObject->mSceneNode->createChildSceneNode("player_sight", Ogre::Vector3 (0, 0,  100));
	//camNode = mPlayerObject->mSceneNode->createChildSceneNode("player_cam", Ogre::Vector3 (0, 50, -100));
	//camNode = mPlayerObject->mSceneNode->createChildSceneNode("player_cam", Ogre::Vector3 (0, 400, -650));
	camNode = mPlayerObject->mSceneNode->createChildSceneNode("player_cam");
	camNode->attachObject(mCamera->mRenderCamera);
	
	// Sets up Bullet 

	mPlayerObject->getRigidBody()->setActivationState(DISABLE_DEACTIVATION); 
	mPlayerObject->getRigidBody()->setAngularFactor(btVector3(0.0f,0.01f,0.0f));
	mPlayerObject->getRigidBody()->setDamping(0.8f, .95f);
	mPlayerObject->getRigidBody()->setFriction(0.5f);
	mPlayerObject->addToBullet(mPhysManager); 
	mPlayerObject->synchWithBullet();
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

#pragma endregion End of Kinect code/Not used right now   
	
#pragma region Controls 

	btTransform ts;
	mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts);

	// If the keyboard is enabled 
	if (mEnableKeyboard) 
	{

#pragma region Old Left and Right Controls 
		// Left 
		//if (mInputHandler->IsKeyDown(OIS::KC_LEFT) && onGround)
		//{

		//	//if (!isJumping)
		//	mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
		//	//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));			
		//	mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(10, 0, 0));
		//	mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10 , 0, 0));
		//}

		//// Right 
		//else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT) && onGround)
		//{
		//	//if (!isJumping)
		//	mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
		//	//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
		//	mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(-10, 0, 0));
		//	mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(-10, 0, 0));			
		//}
#pragma endregion 

		// Does the rotation 
		if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{

#pragma region Testing Purposes 
			//btQuaternion or = mPlayerObject->fallRigidBody->getOrientation();
			//std::string x = std::to_string(or.getX());
			//std::string y = std::to_string(or.getY());
			//std::string z = std::to_string(or.getZ());
			//std::string w = std::to_string(or.getW());

			//OutputDebugString("M pressed [[ Orientation ]]:  \n x");
			//OutputDebugString(x.c_str());
			//OutputDebugString("\n y ");
			//OutputDebugString(y.c_str());
			//OutputDebugString("\n z ");
			//OutputDebugString(z.c_str());
			//OutputDebugString("\n w ");
			//OutputDebugString(w.c_str());
			//OutputDebugString("\n Rotation \n");

			//btQuaternion ro = mPlayerObject->fallRigidBody->getWorldTransform().getRotation();
			//std::string W = std::to_string(ro.getW());
			//std::string X = std::to_string(ro.getX());
			//std::string Y = std::to_string(ro.getY());
			//std::string Z = std::to_string(ro.getZ());

			//OutputDebugString("Rotation  \n w");
			//OutputDebugString(W.c_str());
			//OutputDebugString("\n x ");
			//OutputDebugString(X.c_str());
			//OutputDebugString("\n y ");
			//OutputDebugString(Y.c_str());
			//OutputDebugString("\n z ");
			//OutputDebugString(Z.c_str());
			//OutputDebugString("\n Before END \n");
			//if (!isJumping)
#pragma endregion Prints out to Console 

			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,-1,0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,mPhysManager->_world->getGravity().getY() + 70,0));
			
#pragma region Testing Purposes 
			//btQuaternion rot = mPlayerObject->fallRigidBody->getWorldTransform().getRotation();
			//std::string fW = std::to_string(rot.getW());
			//std::string fX = std::to_string(rot.getX());
			//std::string fY = std::to_string(rot.getY());
			//std::string fZ = std::to_string(rot.getZ());

			//btQuaternion orz = mPlayerObject->fallRigidBody->getOrientation();
			//std::string xz = std::to_string(orz.getX());
			//std::string yz = std::to_string(orz.getY());
			//std::string zz = std::to_string(orz.getZ());
			//std::string ww = std::to_string(orz.getZ());

			//OutputDebugString("After [[ Orientation]] \n x");
			//OutputDebugString(xz.c_str());
			//OutputDebugString("\n y ");
			//OutputDebugString(yz.c_str());
			//OutputDebugString("\n z ");
			//OutputDebugString(zz.c_str());
			//OutputDebugString("\n w ");
			//OutputDebugString(ww.c_str());
			//OutputDebugString("\n Next \n");
			//OutputDebugString("After [[ Rotation ]] \n w");
			//OutputDebugString(fW.c_str());
			//OutputDebugString("\n x ");
			//OutputDebugString(fX.c_str());
			//OutputDebugString("\n y ");
			//OutputDebugString(fY.c_str());
			//OutputDebugString("\n z ");
			//OutputDebugString(fZ.c_str());
			//OutputDebugString("\n END \n");
#pragma endregion Prints out to Console 

		} 
		else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			//if (!isJumping)
			mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,1,0));
			
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,mPhysManager->_world->getGravity().getY() + 70,0));
		}

		// Moves Forward 
		if (mInputHandler->IsKeyDown(OIS::KC_UP))
		{
			btVector3 currCameraPos = btVector3(mCamera->mRenderCamera->getRealDirection().x, 
				mCamera->mRenderCamera->getRealDirection().y, mCamera->mRenderCamera->getRealDirection().z); 

			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(currCameraPos.getX(), 
				mPhysManager->_world->getGravity().getY() + 70, currCameraPos.getZ()));
			
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(currCameraPos.getX() * 40, 
				mPhysManager->_world->getGravity().getY() + 70, currCameraPos.getZ() * 40)); 

#pragma region Other method 
			//btScalar anglee = ts.getRotation().getAngle();
			//btScalar xRot = btCos(anglee);
			//btScalar yRot = btSin(anglee);
			//btScalar zRot = btAtan2(xRot, yRot);
			//btScalar newXRot = btAtan2(-1 * yRot, zRot);
			//btScalar newYRot = btAtan2(-1 * zRot, xRot);

			//if (!isJumping)
			//btVector3 angul = (mPlayerObject->fallRigidBody->getAngularVelocity());
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(5, 0, 5));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(newXRot * 10, 0, zRot * 10)); 
			/*mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(btCos((ts.getRotation().getAngle()) * 10), 
				0,btSin((ts.getRotation().getAngle())) * 10));*/

			//mPlayerObject->fallRigidBody->setFriction(5);

			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1, 0, 0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(10, 0, 0));
#pragma endregion Redo once camera is replaced

		}

		// Moves Backward 
		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			//if (!isJumping)

			btVector3 currCameraPos = btVector3(mCamera->mRenderCamera->getRealDirection().x, 
				mCamera->mRenderCamera->getRealDirection().y, mCamera->mRenderCamera->getRealDirection().z); 

			mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(currCameraPos.getX() * -1, 
				mPhysManager->_world->getGravity().getY() + 70, currCameraPos.getZ()) * -1);
			
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(currCameraPos.getX() * -40, 
				mPhysManager->_world->getGravity().getY() + 70, currCameraPos.getZ() * -40)); 

		}

#pragma region Old movement code 
		//// Up 
		//else if (mInputHandler->IsKeyDown(OIS::KC_UP) && onGround)
		// {
		//	/*mPlayerObject->fallRigidBody->getMotionState()->getWorldTransform(ts);
		//	Ogre::Real x = ts.getOrigin().getX();
		//	Ogre::Real y = ts.getOrigin().getY();
		//	Ogre::Real z = ts.getOrigin().getZ();

		//	Ogre::Real Qx = ts.getRotation().getX();
		//	Ogre::Real Qy = ts.getRotation().getY();
		//	Ogre::Real Qz = ts.getRotation().getZ();
		//	Ogre::Real Qw = ts.getRotation().getW();*/

		//	//mPlayerObject->fallRigidBody->applyCentralImpulse();

		//	//if (!isJumping)
		//	mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
		//	
		//	//mPlayerObject->fallRigidBody->setFriction(1);
		//	
		//	//mPlayerObject->fallRigidBody->applyCentralImpulse(mPlayerObject->fallRigidBody->getAngularVelocity());
		//	mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(1,0,-1));
		//	//mPlayerObject->fallRigidBody->setLinearVelocity(mPlayerObject->fallRigidBody->getAngularVelocity());
		//	mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0, 10));
		//	
		//}

		//// Down 
		//else if (mInputHandler->IsKeyDown(OIS::KC_DOWN) && onGround)
		//{
		//	//if (!isJumping)
		//	mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));

		//	//mPlayerObject->fallRigidBody->setFriction(1);
		//	mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0, 0, 10));
		//	mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 0, -10));
		//	
		//}
#pragma endregion 
		
		// "Jump" 
		else if (mInputHandler->IsKeyDown(OIS::KC_SPACE) && !isJumping)
		{
			//mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->applyCentralImpulse(btVector3(0, 40, 0));
			mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0, 90, 0));
			//isJumping = true; 
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

		else if (mInputHandler->WasKeyDown(OIS::KC_DOWN) || mInputHandler->WasKeyDown(OIS::KC_UP) || 
			mInputHandler->WasKeyDown(OIS::KC_LEFT) || mInputHandler->WasKeyDown(OIS::KC_RIGHT))
		{
			//mPlayerObject->fallRigidBody->setAngularVelocity(btVector3(0,0,0));
			//mPlayerObject->fallRigidBody->setLinearVelocity(btVector3(0,0,0));
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
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,0,0);

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
