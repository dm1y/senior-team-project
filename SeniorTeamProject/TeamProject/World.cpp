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
#include <stdlib.h> 


// IOS (Input system) header files

//#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"
#include "Kinect.h"
#include "Player.h"
#include <list>

using namespace rapidjson;

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera, GameLibrary *gameLib)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor), mCamera(gameCamera), gameLibrary(gameLib)
{
	sceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	//sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
    directionalLight->setSpecularColour(Ogre::ColourValue(1, 1, 1));
	directionalLight->setDirection(0,-1,1);

	physManager = new PhysicsManager();
	
	// create static scenery

	//mCamera->mRenderCamera->setPosition(Ogre::Vector3(0,50,-10));

	StaticScenery *iceIsland = new StaticScenery(Ogre::Vector3(0,0,0), "iceIsland.MESH.mesh", mSceneManager, physManager);

	//DynamicObject *p = gameLibrary->getDynamicObject("Jordan");
	DynamicObject *p = gameLibrary->getDynamicObject("Jesus");
	DynamicObject *j = gameLibrary->getDynamicObject("Jordan");
	mPlayer = new Player(j, Ogre::Vector3(0, 50,-10), physManager, this, mKinect, mSceneManager, mInputHandler, mCamera);
	mPlayer->testingShit(p);
	mPlayer->setScale(Ogre::Vector3(.25, .25, .25));
	//mCamera->updatePosition (Ogre::Vector3 (0, 200, 0), mPlayer->getSightNode ()->getPosition());

	mCamera->mRenderCamera->lookAt(iceIsland->mSceneNode->getPosition());

}


void 
World::Think(float time)
{
	//mCamera->update (mPlayer->getCameraNode() -> getPosition(), mPlayer->getDynamicObject()->mSceneNode->getPosition());
	
	//mCamera->update (mPlayer->getCameraNode ()->getPosition(), mPlayer->getDynamicObject()->mSceneNode->getPosition ());

	//if (mInputHandler->IsKeyDown(OIS::KC_SPACE)) {
	//	DynamicObject *d = gameLibrary->getDynamicObject("Box");
	//	d->setPosition(mCamera->mRenderCamera->getPosition() + Ogre::Vector3(0, -2, 2));
	//	d->addToOgreScene(mSceneManager);
	//	d->addToBullet(physManager);
	//}

	mPlayer->Think(time);
	//mCamera->update(mPlayer);
	//mCamera->mRenderCamera->lookAt(mPlayer->getWorldPosition());
	physManager->stepSimulation(time);
	//mCamera->mRenderCamera->move(mPlayer->getDynamicObject()->position);
}


