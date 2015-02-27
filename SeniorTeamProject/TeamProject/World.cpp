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

#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"


World::World(Ogre::SceneManager *sceneManager, InputHandler *input)   : mSceneManager(sceneManager), mInputHandler(input)
{
	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

	// First, we create a scene node, and attach a model to it.  coin.mesh is defined in the Content directory,
	//  under models.  Note that you should probably place all of this creation code into a separate method (or methods)
	//  for your final game
	Ogre::Entity *ent1 =SceneManager()->createEntity("Box001.mesh");
	Ogre::Entity *ent2 =SceneManager()->createEntity("coin.mesh");
	mCoinNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mCoinNode->attachObject(ent1);
	mCoinNode->attachObject(ent2);

	// Now that we have a scene node, we can move, scale and rotate it as we please.  We'll scale this up a smidge
	// just as an example.  
	//   (take a look at the header file for Ogre::SceneNode -- a good IDE is your friend, here)

	mCoinNode->scale(5,5,5);

	// Yeah, this should be done automatically for all fonts referenced in an overlay file.
	//  But there is a bug in the OGRE code so we need to do it manually.
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}

	// Now we will show the sample overlay.  Look in the file Content/Overlays/Example to
	// see how this overlay is defined
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::Overlay *overly = om.getByName("Sample");
	overly->show();
}


void 
World::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;

	// This is a pretty silly think method, but it gives you some ideas about how
	//  to proceed.  The single object will rotate

	 mCoinNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));

	// We can move the single object around using the input manager ...

	 if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
	 {
		 mCoinNode->translate(time * COIN_SPEED, 0, 0);

	 }
	 else if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
	 {
		 mCoinNode->translate(-time * COIN_SPEED, 0, 0);
	 }

	 else if (mInputHandler->IsKeyDown(OIS::KC_UP))
	 {
		 mCoinNode->translate(0, time*COIN_SPEED, 0);
	 }

	 else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
	 {
		 mCoinNode->translate(0, -time*COIN_SPEED, 0);
	 }
	 // Some other fun stuff to try:
	 //mCoinNode->yaw(Ogre::Radian(time * RADIANS_PER_SECOND));
	 //mCoinNode->roll(Ogre::Radian(time * RADIANS_PER_SECOND));

	 //Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	 //Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Sample/Panel/Text1");
	 //te->setCaption("New Caption!");
}


