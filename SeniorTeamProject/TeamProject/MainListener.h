#ifndef __MainListener_h_
#define __MainListener_h_

#include "Ogre.h"
#include "OgreFrameListener.h"


// Forward declaration of classes
namespace Ogre
{
	class RenderWindow;
}

class InputHandler;
class World;
class GameCamera;
class Kinect;

class MainListener : public Ogre::FrameListener
{
public:
	MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputHandler, World *world, GameCamera *cam, Kinect *sensor);

	bool frameStarted(const Ogre::FrameEvent &evt);


protected:
	InputHandler *mInputHandler;
	World *mWorld;
    GameCamera *mGameCamera;
	Kinect *mKinect;
	Ogre::RenderWindow *mRenderWindow;
	int x;
};

#endif