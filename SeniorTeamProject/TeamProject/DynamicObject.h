#ifndef DynamicObject_H
#define DynamicObject_H
#include "IPhysObject.h"
#include "IOgreObject.h"
#include "PhysicsManager.h"
#include <list>



class DynamicObject: public IPhysObject, public IOgreObject {
private:

public:
	DynamicObject(std::list<Ogre::String> meshName, btCollisionShape *collisionShape, Ogre::Vector3 position);
	void update();
	void synchWithBullet();
	void addToOgreScene(Ogre::SceneManager *sceneManager);
	void addToOgreScene(Ogre::SceneManager *sceneManager, Ogre::String s);
	void addToBullet(PhysicsManager *physmanager);

	void setOrientation(Ogre::Quaternion newOrientation);
	void setPosition(Ogre::Vector3 newPos);
	void setScale(Ogre::Vector3 v);
	
	btRigidBody *getRigidBody() {return fallRigidBody; }
	btCollisionShape *getHitBox() {return hitBox; }
	Ogre::Entity *getEntity() {return mEntity;}
	void addEntity(Ogre::SceneManager *sceneManager, Ogre::String meshName); 


	DynamicObject * clone();

protected:
	Ogre::Entity *mEntity; 
};

#endif