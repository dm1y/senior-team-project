#ifndef PhysObject_H
#define PhysObject_H
#include "OgreString.h"
#include "OgreVector3.h"
#include "PhysicsManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"


namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class PhysObject {
public:
	PhysObject(Ogre::SceneManager *sceneManager, Ogre::String modelName, Ogre::Vector3 pos, PhysicsManager *physManager);
	void Think(float time);
	Ogre::SceneNode *mSceneNode;
	btRigidBody *fallRigidBody;
};


#endif