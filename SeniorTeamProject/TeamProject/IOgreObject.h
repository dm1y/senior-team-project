#ifndef IOGREOBJECT_H
#define IOGREOBJECT_H
#include "OgreSceneManager.h"
#include "OgreVector3.h"
#include "OgreEntity.h"
#include <string>

/* (TO: OLGA)
 * (From: Jordan)
 *
 * This is all written by me.
 */

class IOgreObject {
private:

public:
	std::string meshName;
	Ogre::Vector3 position;
	Ogre::SceneNode *mSceneNode;
	virtual void addToOgreScene(Ogre::SceneManager *sceneManager) = 0;
	virtual void setPosition(Ogre::Vector3 newPos) = 0;
};

#endif