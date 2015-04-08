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
#include "StaticScenery.h"

// IOS (Input system) header files

//#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Player.h"
#include "Kinect.h"
#include <list>

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor), mCamera(gameCamera)
{
	physManager = new PhysicsManager();
	
	// create static scenery

	mCamera->mRenderCamera->setPosition(Ogre::Vector3(0,100,-100));
	
	StaticScenery *testRoom = new StaticScenery(Ogre::Vector3(0,0,0), "testBox.MESH.mesh", mSceneManager, physManager);
	
	mCamera->mRenderCamera->lookAt(testRoom->mSceneNode->getPosition());



	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	// mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
	
	mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* pointLight = mSceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 0));

	Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
	directionalLight->setPosition(Ogre::Vector3(0, 150, 0));
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 0 )); 
 
	Ogre::Light* spotLight = mSceneManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setDirection(0, -1, 0);
    spotLight->setPosition(Ogre::Vector3(0, 200, 0));
 
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	//for(int i = 0; i < 60; i++) {
	//	coins.push_back(new Coin(Ogre::Vector3(i * 2 % 3,100,20), sceneManager, physManager));
	//}

	mPlayer = new Player(Ogre::Vector3(0, 100, 10), physManager, this, mKinect, mSceneManager, mInputHandler);
	//mPlayer = new Player (this, mKinect, mSceneManager, mInputHandler);
	mPlayer->addOgreEntity("tunacan.MESH.mesh");
	//mPlayer->addOgreEntity("coin.mesh");
	mPlayer->setScale(Ogre::Vector3(.5, .5, .5));
}


void 
World::Think(float time)
{
	
	mPlayer->Think(time);

	//for (std::list<Coin*>::iterator it = coins.begin(); it != coins.end(); it++) {
	//	it._Ptr->_Myval->update();
	//}
}


