#ifndef DynamicObject_H
#define DynamicObject_H
#include "IPhysObject.h"
#include "IOgreObject.h"
#include "PhysicsManager.h"
#include <string>


class DynamicObject: public IPhysObject {
private:

public:
	DynamicObject(Ogre::Entity *entity, btRigidBody* rigidBody, btScalar mass, btScalar restitution);
	DynamicObject(std::list<Ogre::String> meshNames, btCollisionShape *collisionShape, Ogre::Vector3 position);
	void update();
	void synchWithBullet();
	void addToOgreScene(Ogre::SceneManager *sceneManager);
	void addToBullet(PhysicsManager *physmanager);
	void setPosition(Ogre::Vector3 newPos);
	void setOrientation(Ogre::Quaternion newRot);
	void setScale(Ogre::Vector3 v);
	DynamicObject * clone(Ogre::SceneManager *mSceneManager);

	Ogre::Entity *ent; 
	Ogre::SceneNode *mSceneNode;
	btRigidBody *mRigidBody;
	static int numCreated;
	btScalar mass;
	btScalar restitution;

	/* Added for compatbility with Simon + Diana */
	std::list<Ogre::String> meshNames;
	Ogre::Vector3 position;
};

#endif