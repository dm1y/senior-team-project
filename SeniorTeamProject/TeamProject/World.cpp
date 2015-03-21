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
#include <list>
#include "btBulletDynamicsCommon.h"
#include "PhysObject.h"

World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor)   : 
	mSceneManager(sceneManager), mInputHandler(input), mKinect(sensor)
{
	physManager = new PhysicsManager();
	physManager->addPlane();


	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
	mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* pointLight = mSceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));

	Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
 
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 
 
	Ogre::Light* spotLight = mSceneManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
 
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
 
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}

	// Now we will show the sample overlay.  Look in the file Content/Overlays/Example to
	// see how this overlay is defined
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::Overlay *overly = om.getByName("Sample");
//	overly->show();

	mPlayer = new Player (this, mKinect, mSceneManager, mInputHandler);
	mPlayer->addOgreEntity("tunacan.MESH.mesh");
	//mPlayer->addOgreEntity("coin.mesh");
	mPlayer->setScale(Ogre::Vector3(.5, .5, .5));

	// For testing purposes 
	mPlayer->setOverlay(overly);

	PhysObject *p1;

	for(int i = 0; i < 50; i++) {
		p1 = new PhysObject(mSceneManager, "coin.mesh", Ogre::Vector3((i*2) % 5, 20, i*2), physManager);
		p1->mSceneNode->setScale(3,3,3);
		physObjects.push_back(p1);
	}

}


void 
World::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	physManager->stepSimulation(time);
	mPlayer->Think(time);	

	int i = 0;
	for (std::list<PhysObject*>::iterator it = physObjects.begin(); it != physObjects.end(); it++) {
		if(i%2 ==0) {
			// it._Ptr->_Myval->fallRigidBody->applyForce(btVector3(5,0,0),btVector3(0,0,0));
		}
		it._Ptr->_Myval->Think(time);
		i++;
	}


}


