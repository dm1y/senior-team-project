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
class Player;

class World
{
public:
	
	World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera, GameLibrary *gameLib);

    // You'll want various methods to access & change your world here
    
    void Think(float time);
	
	void addCamera(GameCamera *c) { mCamera = c; }


	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	PhysicsManager *physManager;

	GameLibrary *gameLibrary;

	void createWater();
	void doWaterStuff(float time);

	bool checkIntersect(btRigidBody *A, btRigidBody *B);


protected:

	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;

	GameCamera *mCamera;
	Kinect *mKinect;
	DynamicObject *d;

	Player *mPlayer;
};

#endif