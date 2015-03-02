#ifndef __World_h_
#define __World_h_

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

// Forward delcarations of our own classes
class GameCamera;
class InputHandler;
class Player;


class World
{
public:
	
    World(Ogre::SceneManager *sceneManager, InputHandler *input);

    // You'll want various methods to access & change your world here
    
    void Think(float time);
	
	void addCamera(GameCamera *c) { mCamera = c; }

	Ogre::SceneManager *SceneManager() { return mSceneManager; }


protected:

	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;

	GameCamera *mCamera;

	Player *mPlayer;
};

#endif