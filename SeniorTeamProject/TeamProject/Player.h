#include "OgreVector3.h"
#include "Receivers.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include <ois/ois.h>

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

class World;
class Kinect;
class GameObject;
class InputHandler;

class Player 
{
public:

	Player(World *world, Kinect *k, Ogre::SceneManager *sceneManager, InputHandler *input);

	void addOgreEntity(Ogre::String mesh); 
	void setScale(Ogre::Vector3 v);

	void Think(float time);
	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	bool getEnableKinect() { return mEnableKinect; }
	void setEnableKinect(bool enable) { mEnableKinect = enable; }

	bool getEnableKeyboard() { return mEnableKeyboard; }
	void setEnableKeyboard(bool enable) { mEnableKeyboard = enable; }

	void getSkeletonAngles(Ogre::Degree &angle, Ogre::Degree &angle2);
	std::vector<Ogre::Vector3> getSkeletonNodes();
	// For testing purposes
	Ogre::Overlay *setOverlay(Ogre::Overlay *o) { return overly = o;}

	GameObject *getGameObject() { return mPlayerObject; }

	void detectSway(float time);
	void detectTurn(float time);
	void drawSkeleton();
	void createLine(std::string bone, int joint1, int joint2);
	void drawLine(std::string bone, int joint1, int joint2);
	void clearLine(std::string bone);

	void checkCollision();


protected:

	Ogre::SceneManager *mSceneManager;
	InputHandler *mInputHandler;
	World *mWorld;
	Kinect *mKinect;
	GameObject *mPlayerObject;

	// For testing purposes 
	Ogre::Overlay *overly; 
	bool overlyBool; 

	// For kinect 

	bool lineVisible;
	bool initSkel;
	
	bool mEnableKinect;
	bool mEnableKeyboard;
	bool mAutoCallibrate;

};