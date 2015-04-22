#include "OgreVector3.h"
#include "Receivers.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include <ois/ois.h>
//#include "OgreOverlayManager.h"
//#include "OgreOverlay.h"
//#include "OgreFontManager.h"
//#include "OgreTextAreaOverlayElement.h"
#include "PhysicsManager.h"

// Forward declarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

class World;
class Kinect;
class DynamicObject;
class InputHandler;

class Player 
{
public:

	Player(DynamicObject *dynamic, Ogre::Vector3 position, PhysicsManager *physManager, World *world, 
		Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input);

	void addToScene(); 
	void setScale(Ogre::Vector3 v);

	void Think(float time);
	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	bool getEnableKinect() { return mEnableKinect; }
	void setEnableKinect(bool enable) { mEnableKinect = enable; }
	bool getEnableKeyboard() { return mEnableKeyboard; }
	void setEnableKeyboard(bool enable) { mEnableKeyboard = enable; }

	// For testing purposes
//	Ogre::Overlay *setOverlay(Ogre::Overlay *o) { return overly = o;}

	DynamicObject *getDynamicObject() { return mPlayerObject; }

	void setPosition (Ogre::Vector3 p);

protected:

	Ogre::SceneManager *mSceneManager;
	InputHandler *mInputHandler;
	World *mWorld;
	Kinect *mKinect;
	DynamicObject *mPlayerObject;
	PhysicsManager *mPhysManager;
	Ogre::String meshName; 

	// For testing purposes 
//	Ogre::Overlay *overly; 
//	bool overlyBool; 

	// For kinect - Trying to follow format of RunnerTransfer for this 
	bool mEnableKinect;
	bool mEnableKeyboard;
	bool mAutoCallibrate;
};