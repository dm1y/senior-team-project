#ifndef IPHYSOBJECT_H
#define IPHYSOBJECT_H
#include "btBulletDynamicsCommon.h"
#include "OgreEntity.h"

class IPhysObject {
private:

public:
	btRigidBody *fallRigidBody;
	btCollisionShape *hitBox; 
	virtual void synchWithBullet() = 0;
	Ogre::Entity *ent; 
};
#endif