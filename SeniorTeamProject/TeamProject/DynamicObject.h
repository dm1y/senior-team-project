#ifndef DynamicObject_H
#define DynamicObject_H
#include "IPhysObject.h"
#include "IOgreObject.h"
#include "PhysicsManager.h"


class DynamicObject: public IPhysObject, public IOgreObject {
private:

public:
	DynamicObject(Ogre::String meshName, btCollisionShape *collisionShape, Ogre::Vector3 position);
	void update();
	void synchWithBullet();
	void addToOgreScene(Ogre::SceneManager *sceneManager);
	void addToBullet(PhysicsManager *physmanager);

	void setPosition(Ogre::Vector3 newPos);
	void setScale(Ogre::Vector3 v);
	
	//btRigidBody *getRigidBody() {return fallRigidBody; }
	btCollisionShape *getHitBox();

	DynamicObject * clone();
};

#endif