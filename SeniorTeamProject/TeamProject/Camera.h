#ifndef __Camera_h_
#define __Camera_h_


namespace Ogre
{
    class Camera;
    class Vector3;
}
class World;
class InputHandler;

class GameCamera

{

public:
    GameCamera(Ogre::Camera *renderCamera, World *world, InputHandler *input); 
    void Think(float time);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely

protected:

    Ogre::Camera *mRenderCamera; 
    World *mWorld;
	InputHandler *mInputHandler;
};

#endif