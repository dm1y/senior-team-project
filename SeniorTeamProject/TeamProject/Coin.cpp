#include "Coin.h"

/* Initialize static hitbox data
 * The collision box is static since it is the same for all coins.
 */
btCollisionShape * Coin::coinHitBox = new btCylinderShape(btVector3(1,1,1));

Coin::Coin(Ogre::Vector3 position, Ogre::SceneManager *sceneManager, PhysicsManager *physManager) {
	
	// create the scene node
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();

	// attach the model entity
	Ogre::Entity *mEntity = sceneManager->createEntity("Coin.MESH.mesh");
	mEntity->setCastShadows(true);
	mSceneNode->attachObject(mEntity);

	// setup rigid body for physics
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
	btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    coinHitBox->calculateLocalInertia(mass, fallInertia);

	// construct the rigid body and add it to the world
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, coinHitBox, fallInertia);
    fallRigidBodyCI.m_restitution = 1.0f;
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
    physManager->_world->addRigidBody(fallRigidBody);


}

void Coin::synchWithBullet() {
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

void Coin::update() {
	synchWithBullet();
}

