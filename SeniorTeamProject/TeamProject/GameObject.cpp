#include "GameObject.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"
#include "OgreSubEntity.h"
#include "OgreMaterial.h"
#include "World.h"

// Initial Constructor 
GameObject::GameObject(Ogre::Vector3 position, PhysicsManager *physManager, World *world, Ogre::SceneManager *sceneManager, ObjectType gameObjType) :
	mPosition(position), mPhysManager(physManager), mWorld(world), mSceneManager(sceneManager), objType(gameObjType)
{
	// Creates scene node 
    mSceneNode = SceneManager()->getRootSceneNode()->createChildSceneNode();

	// Set initial position of scene node 
	mSceneNode->setPosition(position);

	// TODO: Figure out dimensions of tuna can without hardcoding.  
	hitBox = new btCylinderShape(btVector3(15, 15, 15));
}

// From RunnerTransfer but pretty basic/intuitive 
void GameObject::setScale(Ogre::Vector3 newScale)
{
	mScale = newScale;
	mSceneNode->setScale(newScale);
}

// Used Jordan's Coin class as guide to incorporate it into GameObject
void GameObject::setRigidBody() 
{
	btDefaultMotionState* defMotionState =
		new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), 
		btVector3(mPosition.x, mPosition.y, mPosition.z)));
	btScalar mass = 10; 
    btVector3 inertia(0, 0, 0); // set up inertia 
    hitBox->calculateLocalInertia(mass, inertia);

	// construct the rigid body and add it to the world
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, defMotionState, hitBox, inertia);
    rigidBodyCI.m_restitution = 3.0f; // "bounce-ness" after colliding  
	rigidBody = new btRigidBody(rigidBodyCI);

	rigidBody->setUserPointer(mSceneNode); // Might be unnecessary, but sets pointer of rigid body to the scene node for easier access 
	
	mPhysManager->_world->addRigidBody(rigidBody);
	
}

/* Attaches a mesh named <modelName> to the GameObject instance's
 * scene node. Initial code from Runner Transfer. 
   Basic necessity in loading models though.
 */
void GameObject::loadModel(Ogre::String modelName)
{
    mEntity = SceneManager()->createEntity(modelName);
	mEntity->setCastShadows(true);
	mSceneNode->attachObject(mEntity);
	setRigidBody();

	// Not really necessary 
	mMaterialName = mEntity->getSubEntity(0)->getMaterialName();
	mMaxPointLocal = mEntity->getBoundingBox().getMaximum();
	mMinPointLocal =  mEntity->getBoundingBox().getMinimum();
}

// From RunnerTransfer
void GameObject::setMaterial(Ogre::String materialName)
{
	mEntity->setMaterialName(materialName);
}

// From RunnerTransfer
void GameObject::restoreOriginalMaterial()
{
	mEntity->setMaterialName(mMaterialName);
}

// From RunnerTransfer but pretty basic/intuitive 
void GameObject::setPosition(Ogre::Vector3 newPosition)
{
	mSceneNode->setPosition(newPosition);
	//mCollision->setPosition(newPosition);
	mPosition = newPosition;

}

// From RunnerTransfer but pretty basic/intuitive 
void GameObject::setOrientation(Ogre::Quaternion newOrientation)
{
    mSceneNode->setOrientation(newOrientation);
    mOrientation = newOrientation;
//    mCollision->setOrientation(newOrientation);
    mOrientation = newOrientation;
}

// From RunnerTransfer but pretty basic/intuitive. Also modified. Probably no longer needed.
void GameObject::translate(Ogre::Vector3 delta)
{
	//mCollision->translate(delta);
	mSceneNode->translate(delta);
	mPosition += delta;

	mSceneNode->setPosition(mPosition);

}

// From RunnerTransfer but pretty basic/intuitive -- functions might not be needed
Ogre::Vector3 
	GameObject::minPointLocalScaled()
{
	return mMinPointLocal * mScale;
}
Ogre::Vector3 
	GameObject::maxPointLocalScaled()
{
	return mMaxPointLocal * mScale;

}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::yaw(Ogre::Degree d)
{
    mSceneNode->yaw(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
    //mCollision->setOrientation(mSceneNode->getOrientation());
}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::pitch(Ogre::Degree d)
{
    mSceneNode->pitch(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::roll(Ogre::Degree d)
{
    mSceneNode->roll(d);
    //mCollision->setOrientation(mSceneNode->getOrientation());
}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::yaw(Ogre::Radian r)
{
    mSceneNode->yaw(r);
}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::pitch(Ogre::Radian r)
{
    mSceneNode->pitch(r);

}

// From RunnerTransfer but pretty basic/intuitive  -- probably no longer needed
void GameObject::roll(Ogre::Radian r)
{
    mSceneNode->roll(r);
}
