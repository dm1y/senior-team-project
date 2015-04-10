#ifndef IPHYSOBJECT_H
#define IPHYSOBJECT_H
#include "btBulletDynamicsCommon.h"

/* (TO: OLGA)
 * (From: Jordan)
 *
 * This is all written by me.
 */

class IPhysObject {
private:

public:
	btRigidBody *fallRigidBody;
	btCollisionShape *hitBox; 
	virtual void synchWithBullet() = 0;
};
#endif