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


int DynamicObject::numCreated = 0;

DynamicObject::DynamicObject(Ogre::Entity *entity,  btRigidBody* rigidBody, btScalar mass, btScalar restitution) {

	this->ent = entity;
	this->mass = mass;
	this->restitution = restitution;

	numCreated++;
	
	// save entity for later when we want to add it to the ogre scene
	// this->mEntity = entity;

	this->fallRigidBody = rigidBody;
}

/* Constructor for compatiblity with Player class */
DynamicObject::DynamicObject(std::list<Ogre::String> meshNames, btCollisionShape *collisionShape, 
							 Ogre::Vector3 position, int interaction) {
	/* Compatiblity for Simon + Diana */
	this->meshNames = meshNames;
	this->position = position;
	this->interaction = interaction;

	/* create the rigid body */
	
	// hardcoding mass TODO: CHANGE LATER!!!!
	// hardcoding restituion TODO: CHANGE LATER!!!
	int tempMass = 1;
	int tempRestitution = 0.5;

	btDefaultMotionState* fallMotionState =
			new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
		
	btVector3 fallInertia(0, 0, 0);
	collisionShape->calculateLocalInertia(tempMass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(tempMass, fallMotionState, collisionShape, fallInertia);
	fallRigidBodyCI.m_restitution = tempRestitution;

	this->fallRigidBody = new btRigidBody(fallRigidBodyCI);
	this->fallRigidBody->setUserIndex(interaction); // used for collision filtering
}


void DynamicObject::synchWithBullet() {
	btTransform trans;
	this->fallRigidBody->getMotionState()->getWorldTransform(trans);	
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


/* Only need to set bullet position since the ogre scene node will be
 * synced to it.
 */
void DynamicObject::setPosition(Ogre::Vector3 newPos) {
	btTransform trans;
	this->fallRigidBody->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
	//mRigidBody->setCenterOfMassTransform(trans);
	this->fallRigidBody->setWorldTransform(trans);
}

/* Only need to set bullet rotation since the ogre scene node will be
 * synced to it.
 */
void DynamicObject::setOrientation(Ogre::Quaternion newRot) {
	btTransform trans = this->fallRigidBody->getCenterOfMassTransform();
	trans.setRotation(btQuaternion(newRot.x, newRot.y, newRot.z, newRot.w));
	this->fallRigidBody->setWorldTransform(trans);
}

// sets scale of node to new scale 
void DynamicObject::setScale(Ogre::Vector3 v) {
	mSceneNode->setScale(v);
}
void DynamicObject::addToOgreScene(Ogre::SceneManager *sceneManager) {
	
	if(meshNames.size() == 0) {
		// Compatibility for Jordan's way
		
		/* create the scene node */
		// mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		// mSceneNode->attachObject(mEntity);

		// synchWithBullet();

	} else {
		// Compatiblity with Diana + Simon's way

		mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		mSceneNode->setPosition(this->position);


		Ogre::Entity *mEntity;
		// attach the model entity
		for (Ogre::String name : meshNames) {
			mEntity = sceneManager->createEntity(name);
			ent = mEntity;

			//mEntity->setCastShadows(true);
			mSceneNode->attachObject(mEntity);

/*			if (mEntity->hasSkeleton())
			{
				mEntity->getAnimationState("default_skl")->setEnabled(true);
				mEntity->getAnimationState("default_skl")->setLoop(true);
				mEntity->getAnimationState("default_skl")->setWeight(1.0);
				mEntity->getAnimationState("default_skl")->setLength(1.0);
			}	*/		
		}
	}	
}


void DynamicObject::addToBullet(PhysicsManager *physmanager) {
	physmanager->_world->addRigidBody(this->fallRigidBody);
	physmanager->physObjects.push_back(this);
}

void DynamicObject::update() {
	synchWithBullet();
}



/* Fixing the clone I believe is the last piece of the merge puzzle.
*/
DynamicObject * DynamicObject::clone(Ogre::SceneManager *mSceneManager) {
	return new DynamicObject(this->meshNames, this->fallRigidBody->getCollisionShape(), Ogre::Vector3(0,0,0), this->interaction);
}

