#include "DynamicObject.h"

/* (TO: OLGA)
 * (From: Jordan)
 *
 * This is all code written by me.
 */

/* This class represents objects in the world that: 
 *		1. move
 *		2. are collidable
 * 
 * You can use any bullet collision shape except the following static collision shapes:
 *		1. btBvhTriangleMeshShape
 *		2. btHeightfieldTerrainShape
 *		3. btStaticPlaneShape
 *
 * (for a full list of collision shapes see 
 * http://bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Shapes)
 * 
 * Bullet does not calculate physics correctly for collision shapes smaller
 * than 1 unit. DO NOT define collision shapes to be less than 1 unit in any
 * direction!
 *
 * If the object does not move but still requires collision use the class 
 * StaticScenery instead.
 */

DynamicObject::DynamicObject(Ogre::String meshName, btCollisionShape *collisionShape, Ogre::Vector3 position) {
	
	this->position = position;
	this->meshName = meshName;
	this->hitBox = collisionShape; 
	
	// setup rigid body for physics
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
	btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, fallInertia);

	// construct the rigid body and add it to the world
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, collisionShape, fallInertia);
    fallRigidBodyCI.m_restitution = 1.0f;
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
}

void DynamicObject::synchWithBullet() {
	btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);	
	Ogre::Real x = trans.getOrigin().getX();
	Ogre::Real y = trans.getOrigin().getY();
	Ogre::Real z = trans.getOrigin().getZ();

	Ogre::Real Qx = trans.getRotation().getX();
	Ogre::Real Qy = trans.getRotation().getY();
	Ogre::Real Qz = trans.getRotation().getZ();
	Ogre::Real Qw = trans.getRotation().getW();
	mSceneNode->setPosition(Ogre::Vector3(x, y, z));
	mSceneNode->setOrientation(Qw, Qx, Qy, Qz);
}

void DynamicObject::setPosition(Ogre::Vector3 newPos) {
	// only need to set bullet pos, since synch with bullet will take care
	// of the ogre pos.
	btTransform trans = fallRigidBody->getCenterOfMassTransform();
	trans.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
	fallRigidBody->setCenterOfMassTransform(trans);
}

void DynamicObject::setScale(Ogre::Vector3 v) {
	// sets scale of node to new scale 
	mSceneNode->setScale(v);
	// 
}

void DynamicObject::addToOgreScene(Ogre::SceneManager *sceneManager) {
	// create the scene node
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->setPosition(position);

	// attach the model entity
	Ogre::Entity *mEntity = sceneManager->createEntity(meshName);
	mEntity->setCastShadows(true);
	//mEntity->anim
	mSceneNode->attachObject(mEntity);
}

void DynamicObject::addToOgreScene(Ogre::SceneManager *sceneManager, Ogre::String s) {
	// create the scene node
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(s);
	mSceneNode->setPosition(position);

	// attach the model entity
	Ogre::Entity *mEntity = sceneManager->createEntity(s, meshName);
	mEntity->setCastShadows(true);
	//mEntity->anim
	mSceneNode->attachObject(mEntity);
}



void DynamicObject::addToBullet(PhysicsManager *physmanager) {
	physmanager->_world->addRigidBody(fallRigidBody);
	physmanager->physObjects.push_back(this);
}

void DynamicObject::update() {
	synchWithBullet();
}

DynamicObject * DynamicObject::clone() {
	return new DynamicObject(this->meshName, this->fallRigidBody->getCollisionShape(), this->position);
}
