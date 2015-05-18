#ifndef __HUD_h_
#define __HUD_h_

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

using namespace std;

class HUD
{

public:
	HUD(); // constructor 
	~HUD(); // deconstructor 

	int displayScore() { return score; }
	void incrementScore();
	void displayEnding(bool display);
	void displayScore(bool display);
	void displayMenuBG(bool display);
	void displayHint(bool display);
	void displayInstructions(bool display);
	void setInstructions();
protected: 
	Ogre::Overlay *endingOverlay;
	Ogre::Overlay *scoreOverlay;
	Ogre::Overlay *menuBgOverlay;
	Ogre::Overlay *hintsOverlay;
	Ogre::Overlay *instructionsOverlay; 

	Ogre::OverlayElement *scoreText;
	Ogre::OverlayElement *endingText; 
	Ogre::OverlayElement *hintText;
	Ogre::OverlayElement *inText;


	void setScore();

	int score; 
};


#endif