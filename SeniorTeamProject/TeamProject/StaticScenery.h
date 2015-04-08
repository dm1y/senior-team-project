#ifndef STATICSCENERY_H
#define STATICSCENERY_H
#include "OgreVector3.h"
#include "PhysicsManager.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreSubMesh.h"

class StaticScenery {
public:
	Ogre::SceneNode *mSceneNode;
	StaticScenery(Ogre::Vector3 position, Ogre::String meshName, Ogre::SceneManager *sceneManager, PhysicsManager *physManager);
	btTriangleMesh* ogreToBulletMesh(Ogre::MeshPtr mesh);

};
#endif