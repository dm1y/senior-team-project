#include "World.h"


/* (TO: OLGA)
 * (From: Jordan)
 *
 * The world class was coded by all of us, I wrote the parts of it that
 * use DynamicObject, GameLibrary, StaticScenery, and PhysicsManager.
 */


// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
<<<<<<< HEAD
#include "StaticScenery.h"
=======
#include <stdlib.h> 

>>>>>>> origin/Moscow

// IOS (Input system) header files

//#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"
#include "Kinect.h"
#include <list>

<<<<<<< HEAD
World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor), mCamera(gameCamera)
{
	physManager = new PhysicsManager();
	
	// create static scenery

	mCamera->mRenderCamera->setPosition(Ogre::Vector3(0,100,-100));
	
	StaticScenery *testRoom = new StaticScenery(Ogre::Vector3(0,0,0), "testBox.MESH.mesh", mSceneManager, physManager);
	
	mCamera->mRenderCamera->lookAt(testRoom->mSceneNode->getPosition());

=======

using namespace rapidjson;

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera, GameLibrary *gameLib)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor), mCamera(gameCamera), gameLibrary(gameLib)
{
	sceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
>>>>>>> origin/Moscow

	Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
    directionalLight->setSpecularColour(Ogre::ColourValue(1, 1, 1));
	directionalLight->setDirection(0,-1,1);

<<<<<<< HEAD
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
=======
	physManager = new PhysicsManager();
	
	// create static scenery

	mCamera->mRenderCamera->setPosition(Ogre::Vector3(0,20,-10));

	StaticScenery *iceIsland = new StaticScenery(Ogre::Vector3(0,0,0), "iceIsland.MESH.mesh", mSceneManager, physManager);

	mCamera->mRenderCamera->lookAt(iceIsland->mSceneNode->getPosition());
>>>>>>> origin/Moscow
}


void 
World::Think(float time)
{
<<<<<<< HEAD
	
	mPlayer->Think(time);

	//physManager->stepSimulation(time);

	//for (std::list<Coin*>::iterator it = coins.begin(); it != coins.end(); it++) {
	//	it._Ptr->_Myval->update();
	//}
=======
	if (mInputHandler->IsKeyDown(OIS::KC_SPACE)) {
		DynamicObject *d = gameLibrary->getDynamicObject("Box");
		d->setPosition(mCamera->mRenderCamera->getPosition() + Ogre::Vector3(0, -2, 2));
		d->addToOgreScene(mSceneManager);
		d->addToBullet(physManager);
	}
	
	physManager->stepSimulation(time);
>>>>>>> origin/Moscow
}


