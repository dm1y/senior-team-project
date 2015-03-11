// My header file.  This should go first!
#include "World.h"

// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

// IOS (Input system) header files

//#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Player.h"
#include "Kinect.h"

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor)
{
	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	mSceneManager->setAmbientLight(Ogre::ColourValue(0,1,256));

	mPlayer = new Player (this, mSceneManager, mInputHandler);
	mPlayer->addOgreEntity("Box001.mesh");
	//mPlayer->addOgreEntity("coin.mesh");
	mPlayer->setScale(Ogre::Vector3(5,5,5));

	//mGameObject = new GameObject(this, sceneManager);
	//mGameObject->loadModel("coin.mesh");

	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	//while (iter.hasMoreElements()) 
	//{ 
	//	iter.getNext()->load(); 
	//}

	// Now we will show the sample overlay.  Look in the file Content/Overlays/Example to
	// see how this overlay is defined
	//Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	//Ogre::Overlay *overly = om.getByName("Sample");
	//overly->show();
}


void 
World::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	mPlayer->Think(time);

}


