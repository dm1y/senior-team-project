#include "OgreCamera.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"

// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"

GameCamera::GameCamera(Ogre::Camera *renderCamera, World *world, InputHandler *input) :
mRenderCamera(renderCamera), mWorld(world), mInputHandler(input)
{
	mRenderCamera->setNearClipDistance(2);
}

void
GameCamera::Think(float time)
{

	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
		
	if (mInputHandler->IsKeyDown(OIS::KC_W))
	 {
		 // When 'W' is pressed, rotates among the y axis 
		 
		 //mRenderCamera->rotate(Ogre::Quaternion(30.0, 30.0, 5.0, 69.0));		 
	 }
	else if (mInputHandler->IsKeyDown(OIS::KC_S))
	 {
	 }

	else if (mInputHandler->IsKeyDown(OIS::KC_A))
	 {
		 mRenderCamera->yaw(Ogre::Radian(time * -1.0));

	 }

	 else if (mInputHandler->IsKeyDown(OIS::KC_D))
	 {
		 mRenderCamera->yaw(Ogre::Radian(time * 1.0));
	 }

}
