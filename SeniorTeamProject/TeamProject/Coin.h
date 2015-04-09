#ifndef COIN_H
#define COIN_H
#include "OgreVector3.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"

class Coin {
private:
	void synchWithBullet();
public:
	Ogre::SceneNode *mSceneNode;
	btRigidBody *fallRigidBody;
	static btCollisionShape *coinHitBox;
	Coin(Ogre::Vector3 position, Ogre::SceneManager *sceneManager, PhysicsManager *physManager);
	void update();
};

#endif