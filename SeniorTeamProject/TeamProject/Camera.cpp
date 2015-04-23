#include "OgreCamera.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"

// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"

GameCamera::GameCamera(Ogre::Camera *renderCamera, InputHandler *input, Ogre::SceneManager *sceneManager) :
mRenderCamera(renderCamera), mInputHandler(input), mSceneManager (sceneManager)
{
	mRenderCamera->setNearClipDistance(1);
	setup();
}

void GameCamera::updatePosition(Ogre::Vector3 camP, Ogre::Vector3 tarP) {
	//mRenderCamera->setPosition(Ogre::Vector3(p.x, p.y + 30, p.z));
	//mRenderCamera->lookAt(p);
    mCamNode->setPosition (camP);
    mTargetNode->setPosition (tarP);
}

// Sets up autotracking for player 
void GameCamera::setup() 
{
	 mCamNode = mSceneManager->getRootSceneNode ()->createChildSceneNode ("camera");
     mTargetNode = mSceneManager->getRootSceneNode ()->createChildSceneNode ("camera_target");
	 mCamNode->setAutoTracking (true, mTargetNode); 
	 mCamNode->setFixedYawAxis (true);
	 mRenderCamera->setPosition(Ogre::Vector3(0,0,0));
	 //mCamNode->setPosition(mRenderCamera->getPosition());
	 mCamNode->attachObject(mRenderCamera);

}

void GameCamera::update(Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition)
{
	// Handles the movement 
	Ogre::Vector3 displacement; 

	displacement = cameraPosition - mCamNode->getPosition() * 0.5f; 
	mCamNode->translate(displacement);

	//displacement = targetPosition - mTargetNode->getPosition () * 0.5f; 
	//mCamNode->translate(displacement);

	mCamNode->setPosition(Ogre::Vector3(displacement.x, displacement.y, displacement.z));
}

void
GameCamera::Think(float time)
{


	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
		
	// Moves the camera up 
	if (mInputHandler->IsKeyDown(OIS::KC_W))
	{
		 Ogre::Vector3 camPos = mRenderCamera->getPosition();
		 mRenderCamera->setPosition(Ogre::Vector3(camPos.x, camPos.y, camPos.z + 1)); 
	}

	// Moves the camera down 
	else if (mInputHandler->IsKeyDown(OIS::KC_S))
	{
		Ogre::Vector3 camPos = mRenderCamera->getPosition();
		mRenderCamera->setPosition(Ogre::Vector3(camPos.x, camPos.y, camPos.z - 1));  
	}

	// Moves the camera left 
	else if (mInputHandler->IsKeyDown(OIS::KC_A))
	{
		Ogre::Vector3 camPos = mRenderCamera->getPosition();
		mRenderCamera->setPosition(Ogre::Vector3(camPos.x + 1, camPos.y, camPos.z));  
	}
	
	// Moves the camera right 
	else if (mInputHandler->IsKeyDown(OIS::KC_D))
	{
		Ogre::Vector3 camPos = mRenderCamera->getPosition();
		mRenderCamera->setPosition(Ogre::Vector3(camPos.x - 1, camPos.y, camPos.z)); 
	}

	// Zooms camera out 
	if (mInputHandler->IsKeyDown(OIS::KC_Q))
	{
		 Ogre::Vector3 camPos = mRenderCamera->getPosition();
		 mRenderCamera->setPosition(Ogre::Vector3(camPos.x, camPos.y + 1, camPos.z)); 

	// Zooms camera in 
	} else if (mInputHandler->IsKeyDown(OIS::KC_E))
	{
		 Ogre::Vector3 camPos = mRenderCamera->getPosition();
		 mRenderCamera->setPosition(Ogre::Vector3(camPos.x, camPos.y - 1, camPos.z)); 
	}

}
