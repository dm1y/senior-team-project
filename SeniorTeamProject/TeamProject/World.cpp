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
//#include "OgreOverlayManager.h"
//#include "OgreOverlay.h"
//#include "OgreFontManager.h"
//#include "OgreTextAreaOverlayElement.h"
#include <stdlib.h> 


// IOS (Input system) header files

//#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"
#include "Kinect.h"
#include "Player.h"
#include "HUD.h"
#include <list>

using namespace rapidjson;

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera, GameLibrary *gameLib, Ogre::Root *mRoot)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor), mCamera(gameCamera), gameLibrary(gameLib)
{
	//score = 0;
	sceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	// sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
    directionalLight->setSpecularColour(Ogre::ColourValue(1, 1, 1));
	directionalLight->setDirection(0,-1,1);

	physManager = new PhysicsManager();

	// Causes shadowcaster error, vertex limit exceeded?
	// Fixed by turning off shadows... but thats lame
	DynamicObject *p = gameLibrary->getDynamicObject("Human");
	DynamicObject *j = gameLibrary->getDynamicObject("Jordan");
	
	mPlayer = new Player(j, Ogre::Vector3(0, 50,-10), physManager, this, mKinect, mSceneManager, mInputHandler, mCamera);
	mPlayer->setAnimation(p);
	mPlayer->setScale(Ogre::Vector3(.25, .25, .25));
	
#pragma region Testing objects spawn 
	// Teapot object setup 
	//d = gameLibrary->getDynamicObject("TeaPot");
	//d->setPosition(Ogre::Vector3(0, 80, -50));
	//d->addToOgreScene(mSceneManager);
	//d->addToBullet(physManager);
	//d->setScale(Ogre::Vector3(10,10,10));
	//
	//dynaList.push_back(d);
	//
	//e = gameLibrary->getDynamicObject("TeaPot");
	//e->setPosition(Ogre::Vector3(0, 80, -90));
	//e->addToOgreScene(mSceneManager);
	//e->addToBullet(physManager);
	//e->setScale(Ogre::Vector3(10,10,10));

	//dynaList.push_back(e);

	//// Tuna object setup 
	//t = gameLibrary->getDynamicObject("Tuna");
	//t->setPosition(Ogre::Vector3(10, 80, -150));
	//t->addToOgreScene(mSceneManager);
	//t->addToBullet(physManager);
	//t->setScale(Ogre::Vector3(.3,.3,.3));

	//dynaList.push_back(t);
#pragma endregion TODO move logic elsewhere once stage is completed 

	Stage* stage = gameLibrary->getStage("IceIsland");

	StaticScenery *tempIceIsland;
	for (std::list<DynamicObject*>::iterator it = stage->dynObjects.begin(); it != stage->dynObjects.end(); it++) {
		it._Ptr->_Myval->addToOgreScene(mSceneManager);
	 	it._Ptr->_Myval->addToBullet(physManager);
	}

	for (std::list<StaticScenery*>::iterator it = stage->staticScenery.begin(); it != stage->staticScenery.end(); it++) {
		it._Ptr->_Myval->addToOgreScene(mSceneManager);
	 	it._Ptr->_Myval->addToBullet(physManager);
		tempIceIsland = it._Ptr->_Myval;
	}

	// TODO: Fix this so it's not hardcoded
	mCamera->mRenderCamera->lookAt(tempIceIsland->mSceneNode->getPosition());

	createWater();
	
	// Creates new HUD 
	display = new HUD();
}


void 
World::Think(float time)
{
	doWaterStuff(time);

	/*if (mInputHandler->IsKeyDown(OIS::KC_SPACE)) {
		DynamicObject* temp = this->gameLibrary->getDynamicObject("TeaPot");
		temp->addToBullet(physManager);
		temp->addToOgreScene(mSceneManager);
	}*/

#pragma region Collision Filtering 
	// TODO Move this game logic to Physics after stage is completed 
	// Variables to remove the dynamic object that's in the list 
	//DynamicObject *objToRm; 
	//bool remove = false;

	//int i = 0;

	//for (DynamicObject *obj : dynaList) 
	//{

	//	mPlayer->drawHitBox("Object" + std::to_string(i), obj->fallRigidBody);

	//	if (physManager->checkIntersect(mPlayer->getDynamicObject()->fallRigidBody, obj->fallRigidBody))
	//	{

	//		if (obj->fallRigidBody->getUserIndex() == 1) 
	//		{

	//			remove = true;
	//			objToRm = obj;

	//			display->incrementScore();
	//			//OutputDebugString("\nPLAYER IS COLLIDING WITH THE TEAPOT ZOMG!\n");
	//			
	//			physManager->_world->removeRigidBody(obj->fallRigidBody);
	//			physManager->physObjects.remove(obj);
	//			break; 
	//		}
	//		else if (obj->fallRigidBody->getUserIndex() == 2) 
	//		{
	//			OutputDebugString("\nPLAYER IS COLLIDING WITH THE TUNACAN ZOMG!\n");
	//			display->displayEnding(true);
	//		}
	//	}
	//	i++;
	//}

	//if (remove) 
	//{
 //		dynaList.remove(objToRm);				
	//	mSceneManager->destroyEntity(objToRm->ent->getName().c_str());
	//	remove = false; 
	//}

	mPlayer->Think(time);

#pragma endregion TODO: Move to physmanager after stage is done 

	physManager->stepSimulation(time, this);
}

#pragma region Water

void
World::createWater()
{

#define FLOW_SPEED 1
#define FLOW_HEIGHT 10

	Ogre::Entity *mWaterEntity;
	Ogre::Plane mWaterPlane;

	mWaterPlane.normal = Ogre::Vector3::UNIT_Y;
	mWaterPlane.d = -1.5;

	Ogre::MeshManager::getSingleton().createPlane(
		"WaterPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		mWaterPlane, 1000, 1000, 5, 1, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	mWaterEntity = mSceneManager->createEntity("water", "WaterPlane");
	mWaterEntity->setMaterialName("Examples/Water9");

	Ogre::SceneNode *mWaterNode = mSceneManager->getRootSceneNode()->createChildSceneNode("WaterNode");
	mWaterNode->attachObject(mWaterEntity);
	mWaterNode->setPosition(0, 0, 0);
	mWaterNode->setOrientation(Ogre::Quaternion::IDENTITY);
	//mWaterNode->setOrientation(0, 0, 1, 0);
	//mWaterNode->translate(3000, -50, 3000);

	
	Ogre::Light *mLight = mSceneManager->createLight("WaterLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setDirection(0, -100, 0);
	
}


void
World::doWaterStuff(float time)
{
	float waterFlow = FLOW_SPEED * time;
	static float flowAmount = 0.0f;
	static bool flowUp = true;

	// Ogre::SceneNode *mCamera = mPlayer->getCameraNode();

	Ogre::SceneNode *mWaterNode = static_cast<Ogre::SceneNode*>
		(mSceneManager->getRootSceneNode()->getChild("WaterNode"));

	//mWaterNode->setOrientation(0, 0, 1, 0);

	if (mWaterNode)
	{
		if (flowUp)
			flowAmount += waterFlow;
		else
			flowAmount -= waterFlow;

		if (flowAmount >= FLOW_HEIGHT)
			flowUp = false;
		else if (flowAmount <= 0.0f)
			flowUp = true;

		mWaterNode->translate(0, (flowUp ? waterFlow : -waterFlow), 0);
	}
}

#pragma endregion Water