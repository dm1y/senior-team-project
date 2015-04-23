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

#include <ois/ois.h>

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
	
	StaticScenery *testRoom = new StaticScenery(Ogre::Vector3(0,0,0), "TestPlane.mesh", mSceneManager, physManager);
	
	mCamera->mRenderCamera->lookAt(testRoom->mSceneNode->getPosition());



	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	// mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
	
	//mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

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
	
	for(int i = 0; i < 20; i++) {
		//coins.push_back(new Coin(Ogre::Vector3(i * 2 % 3,100,20), sceneManager, physManager));

		GameObject* gggggo = new GameObject(this, sceneManager, GameObject::NOTPLAYER);
		gggggo->loadModel("catcoin.MESH.mesh");
		gggggo->setScale(Ogre::Vector3(.1, .1, .1));
		gggggo->setPosition(Ogre::Vector3(50, 0, 0));
		gameObjects.push_back(gggggo);
	}

	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::Overlay *overly = om.getByName("Sample");

	//TODO::MAKE MORE GENERAL
	mPlayer1 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer1->addOgreEntity("cubeBeards.mesh");
	mPlayer1->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer1->setOverlay(overly);

	mPlayer2 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer2->addOgreEntity("cubeBottoms.mesh");
	mPlayer2->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer2->setOverlay(overly);

	mPlayer3 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer3->addOgreEntity("cubeHair.mesh");
	mPlayer3->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer3->setOverlay(overly);

	mPlayer4 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer4->addOgreEntity("cubeMoustaches.mesh");
	mPlayer4->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer4->setOverlay(overly);

	mPlayer5 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer5->addOgreEntity("cubeShoes.mesh");
	mPlayer5->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer5->setOverlay(overly);

	mPlayer6 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer6->addOgreEntity("cubeTops.mesh");
	mPlayer6->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer6->setOverlay(overly);

	mPlayer = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer->addOgreEntity("cubeBody.mesh");
	mPlayer->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer->setOverlay(overly);

	mPlayer7 = new Player(this, mKinect, mSceneManager, mInputHandler);
	mPlayer7->addOgreEntity("cubeJordan.mesh");
	mPlayer7->setScale(Ogre::Vector3(.25, .25, .25));
	mPlayer7->setOverlay(overly);
	mPlayer7->getGameObject()->setPosition(Ogre::Vector3(0, 30, 30));
	mPlayer7->getGameObject()->setOrientation(Ogre::Quaternion::IDENTITY);
}


void 
World::Think(float time)
{
	physManager->stepSimulation(time);

	mPlayer7->Think(time);

	
	if (mInputHandler->IsKeyDown(OIS::KC_TAB))
	{
		mPlayer->getGameObject()->Think(time);
		mPlayer1->getGameObject()->Think(time);
		mPlayer2->getGameObject()->Think(time);
		mPlayer3->getGameObject()->Think(time);
		mPlayer4->getGameObject()->Think(time);
		mPlayer5->getGameObject()->Think(time);
		mPlayer6->getGameObject()->Think(time);
	}
	
	for (std::list<Coin*>::iterator it = coins.begin(); it != coins.end(); it++) {
		it._Ptr->_Myval->update();
	}
}
