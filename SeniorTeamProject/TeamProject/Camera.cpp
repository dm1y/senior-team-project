#include "OgreCamera.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"

// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"

GameCamera::GameCamera(Ogre::Camera *renderCamera, InputHandler *input) :
mRenderCamera(renderCamera), mInputHandler(input)
{
	mRenderCamera->setNearClipDistance(2);
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
