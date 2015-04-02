#include "GameObject.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"
#include "OgreSubEntity.h"
#include "OgreMaterial.h"
#include "World.h"

GameObject::GameObject(Ogre::Vector3 position, PhysicsManager *physManager, World *world, Ogre::SceneManager *sceneManager, ObjectType gameObjType) :
	mPosition(position), mPhysManager(physManager), mWorld(world), mSceneManager(sceneManager), objType(gameObjType)
{
    mSceneNode = SceneManager()->getRootSceneNode()->createChildSceneNode();

	mSceneNode->setPosition(position);

}


void GameObject::setScale(Ogre::Vector3 newScale)
{
	mScale = newScale;
	mSceneNode->setScale(newScale);

	//mCollision->setScale(newScale);
    mOrientation = Ogre::Quaternion::IDENTITY;
    mPosition = Ogre::Vector3::ZERO;

//	mCollision->setScale(newScale);
}

void GameObject::setRigidBody() 
{
	btCollisionShape* fallShape = new btCylinderShape(btVector3(5, 5, 5));

	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState( btTransform(btQuaternion(0, 0, 0, 1), btVector3(mPosition.x, mPosition.y, mPosition.z)));
	btScalar mass = 5;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);

	// construct the rigid body and add it to the world
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    fallRigidBodyCI.m_restitution = 1.0f;
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	mPhysManager->_world->addRigidBody(fallRigidBody);
}

/* Attaches a mesh named <modelName> to the GameObject instance's
 * scene node.
 */
void GameObject::loadModel(Ogre::String modelName)
{
    mEntity = SceneManager()->createEntity(modelName);
	mEntity->setCastShadows(true);
	mSceneNode->attachObject(mEntity);
	mMaterialName = mEntity->getSubEntity(0)->getMaterialName();
	//mCollision = new OBB(mEntity->getBoundingBox());
	mMaxPointLocal = mEntity->getBoundingBox().getMaximum();
	mMinPointLocal =  mEntity->getBoundingBox().getMinimum();
	setRigidBody();
}


void GameObject::setMaterial(Ogre::String materialName)
{
	mEntity->setMaterialName(materialName);
}

void GameObject::restoreOriginalMaterial()
{
	mEntity->setMaterialName(mMaterialName);
}


void GameObject::setPosition(Ogre::Vector3 newPosition)
{
	mSceneNode->setPosition(newPosition);
	//mCollision->setPosition(newPosition);
	mPosition = newPosition;

}

void GameObject::setOrientation(Ogre::Quaternion newOrientation)
{
    mSceneNode->setOrientation(newOrientation);
    mOrientation = newOrientation;
//    mCollision->setOrientation(newOrientation);
    mOrientation = newOrientation;
}

void GameObject::translate(Ogre::Vector3 delta)
{
	//mCollision->translate(delta);
	mSceneNode->translate(delta);
	mPosition += delta;

	mSceneNode->setPosition(mPosition);
}

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

void GameObject::yaw(Ogre::Degree d)
{
    mSceneNode->yaw(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
    //mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::pitch(Ogre::Degree d)
{
    mSceneNode->pitch(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
}


void GameObject::roll(Ogre::Degree d)
{
    mSceneNode->roll(d);
    //mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::yaw(Ogre::Radian r)
{
    mSceneNode->yaw(r);


}

void GameObject::pitch(Ogre::Radian r)
{
    mSceneNode->pitch(r);

}

void GameObject::roll(Ogre::Radian r)
{
    mSceneNode->roll(r);
}

void GameObject::Think(float time)
{
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