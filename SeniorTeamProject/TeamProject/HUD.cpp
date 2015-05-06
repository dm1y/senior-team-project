#include "HUD.h"
#include <stdlib.h> 
#include <list> // might be unnecessary but using it just in case 

// Sets up the HUD information
HUD::HUD() 
{
	score = 0; 

	// Used for loading fonts 
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
		iter.getNext()->load(); 

	// Sets up the overlay 
	endingOverlay = Ogre::OverlayManager::getSingleton().getByName("Ending");
	scoreOverlay = Ogre::OverlayManager::getSingleton().getByName("Score");

	// Sets up text 
	endingText = Ogre::OverlayManager::getSingleton().getOverlayElement("Ending/Panel/Text1");
	scoreText = Ogre::OverlayManager::getSingleton().getOverlayElement("Score/Panel/Text1");

	// default setup 
	displayScore(true);
	displayEnding(false);
}

HUD::~HUD() 
{
}

void HUD::incrementScore()
{
	score++;
	setScore();
}

void HUD::displayScore(bool display)
{
	if (display)
		scoreOverlay->show();
	else 
		scoreOverlay->hide();
}


void HUD::displayEnding(bool display)
{
	if (display)
		endingOverlay->show();
	else 
		endingOverlay->hide();
}

void HUD::setScore()
{
	string scr = std::to_string(score);
	scoreText->setCaption("Score is: " + scr);
}