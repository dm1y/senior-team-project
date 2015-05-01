#ifndef STATICSCENERY_H
#define STATICSCENERY_H
#include "OgreVector3.h"
#include "PhysicsManager.h"
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreSubMesh.h"

class StaticScenery {
public:
	StaticScenery(Ogre::Entity *mEntity);
	StaticScenery(Ogre::Entity *mEntity, btCollisionObject *colObject);
	void addToOgreScene(Ogre::SceneManager *sceneManager);
	void addToBullet(PhysicsManager *physmanager);
	btTriangleMesh* ogreToBulletMesh(Ogre::MeshPtr mesh);
	StaticScenery * clone();
	void setPosition(Ogre::Vector3 newPos);
	void setOrientation(Ogre::Quaternion newRot);
	Ogre::SceneNode *mSceneNode;
	Ogre::Entity *mEntity;
	
	btCollisionObject* btObj;


	btRigidBody* mRigidBody;

	void synchWithBullet();



	// should these be pointers?
	Ogre::Vector3 position;
	Ogre::Quaternion rotation;
};
#endif