#ifndef __Camera_h_
#define __Camera_h_


namespace Ogre
{
    class Camera;
    class Vector3;
    class SceneNode;
    class SceneManager;
}
class World;
class InputHandler;
class Player;

class GameCamera

{

public:
    GameCamera(Ogre::Camera *renderCamera, InputHandler *input, Ogre::SceneManager *sceneManager); 
	void updatePosition(Ogre::Vector3 camP, Ogre::Vector3 tarP);
	void setup();
	void update(Player *player);

	Ogre::Camera *mRenderCamera; 

    
	void Think(float time);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely
protected:

	InputHandler *mInputHandler;
	Ogre::SceneManager *mSceneManager; 
	Ogre::SceneNode *mCamNode;
	Ogre::SceneNode *mTargetNode;
};

#endif