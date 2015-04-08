#ifndef __World_h_
#define __World_h_

#include <list>
#include "PhysicsManager.h"
#include "Coin.h"

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

using namespace std;

// Forward delcarations of our own classes
class GameCamera;
class GameObject;
class InputHandler;
class Player;
class Kinect;


class World
{
public:
	
    World(Ogre::SceneManager *sceneManager, InputHandler *input, Kinect *sensor, GameCamera *gameCamera);

    // You'll want various methods to access & change your world here
    
    void Think(float time);
	
	void addCamera(GameCamera *c) { mCamera = c; }

	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	vector<GameObject*> getWorldObjects() { return gameObjects; } 

	list<Coin*> getCoins() { return coins; }

	PhysicsManager *physManager;

protected:

	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;

	GameCamera *mCamera;
	Kinect *mKinect;

	Player *mPlayer;

	GameObject *mGameObject;

	vector<GameObject*> gameObjects;

	list<Coin*> coins;
};

#endif