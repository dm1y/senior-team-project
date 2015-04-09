#ifndef __World_h_
#define __World_h_

#include "PhysicsManager.h"
#include "DynamicObject.h"
#include "StaticScenery.h"
#include "GameLibrary.h"


// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

using namespace std;

// Forward delcarations of our own classes
class GameCamera;
class InputHandler;
class Player;
class Kinect;


class World
{
public:
	
<<<<<<< HEAD
    World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera);
=======
	World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera, GameLibrary *gameLib);
>>>>>>> origin/Moscow

    // You'll want various methods to access & change your world here
    
    void Think(float time);
	
	void addCamera(GameCamera *c) { mCamera = c; }


	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	PhysicsManager *physManager;

	GameLibrary *gameLibrary;

protected:

	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;

	GameCamera *mCamera;
	Kinect *mKinect;

	Player *mPlayer;
};

#endif