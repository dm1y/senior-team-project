#include "PhysObject.h"


PhysObject::PhysObject(Ogre::SceneManager *sceneManager, Ogre::String modelName, Ogre::Vector3 pos, PhysicsManager *physManager) {
	
	// create the scene node
	mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->setPosition(pos);

	// attach an entity
	Ogre::Entity *mEntity = sceneManager->createEntity(modelName);
	mSceneNode->attachObject(mEntity);


	// create the collision shape and other data needed to make a rigid body
	btCollisionShape* fallShape = new btCylinderShape(btVector3(5, 5, 5));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
	btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);

	// construct the rigid body and add it to the world
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    fallRigidBodyCI.m_restitution = 1.0f;
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
    physManager->_world->addRigidBody(fallRigidBody);
}

void PhysObject::Think(float time) {

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