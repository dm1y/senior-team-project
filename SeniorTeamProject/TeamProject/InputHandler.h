#ifndef __InputHandler_h_
#define __InputHandler_h_

#include <ois/ois.h>
#include <Ogre.h>
#include "OgreRenderWindow.h"
#include "Console.h"

class World;
class GameCamera;
class InputHandler;


class InputHandler : OIS::KeyListener  // : public OIS::MouseListener, public 
{
public:

	InputHandler(Ogre::RenderWindow* win, Console* console);
	~InputHandler();
	void Think(float time);

	bool IsKeyDown(OIS::KeyCode key);
	bool WasKeyDown(OIS::KeyCode key);

	static InputHandler *getInstance();
	void setEventCallback(OIS::KeyListener *keyListener);
	static void destroyInstance();
	void initialize(Ogre::RenderWindow* win);

protected:
	OIS::InputManager* mInputManager;
	Ogre::RenderWindow *mRenderWindow;
	OIS::Keyboard *mPreviousKeyboard;
	OIS::Keyboard *mCurrentKeyboard;
	char mOldKeys[256];
	Console *mConsole;
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

};

#endif