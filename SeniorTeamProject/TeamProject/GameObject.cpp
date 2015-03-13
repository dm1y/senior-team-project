#include "GameObject.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "CollisionManager.h"
#include "OgreSubEntity.h"

#include "OgreMaterial.h"
#include "World.h"

GameObject::GameObject(World *world, Ogre::SceneManager *sceneManager, ObjectType gameObjType) :
	mWorld(world), mSceneManager(sceneManager), objType(gameObjType)
{
	mCollision = NULL;
    mSceneNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
}

void GameObject::setScale(Ogre::Vector3 newScale)
{
	mScale = newScale;
	mSceneNode->setScale(newScale);
<<<<<<< HEAD
	//mCollision->setScale(newScale);
    mOrientation = Ogre::Quaternion::IDENTITY;
    mPosition = Ogre::Vector3::ZERO;
=======
	mCollision->setScale(newScale);
>>>>>>> origin/master
}

void GameObject::loadModel(Ogre::String modelName)
{
    mEntity = SceneManager()->createEntity(modelName);
	mSceneNode->attachObject(mEntity);
	mMaterialName = mEntity->getSubEntity(0)->getMaterialName();
	mCollision = new OBB(mEntity->getBoundingBox());
	mMaxPointLocal = mEntity->getBoundingBox().getMaximum();
	mMinPointLocal =  mEntity->getBoundingBox().getMinimum();

}

void GameObject::setMaterial(Ogre::String materialName)
{
	mEntity->setMaterialName(materialName);
}

void GameObject::restoreOriginalMaterial()
{
	mEntity->setMaterialName(mMaterialName);
}

<<<<<<< HEAD
=======

void GameObject::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float COIN_SPEED = 30;
	
	mSceneNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
}

/*
>>>>>>> origin/master
void GameObject::translate(Ogre::Vector3 vector)
{
	mSceneNode->translate(vector);
}
<<<<<<< HEAD
=======
*/

	//->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));
>>>>>>> origin/master


//void GameObject::setAlpha(float alpha)
//{
//	for (unsigned int i = 0; i < mEntity->getNumSubEntities(); i++)
//	{
//
//		mEntity->getSubEntity(i)->getMaterial()->getBestTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
//		mEntity->getSubEntity(i)->getMaterial()->getBestTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, alpha);
//
//	}

//GameObject::~GameObject(void)
//{
//    mScale = Ogre::Vector3::UNIT_SCALE;
//    if (mSceneNode != NULL)
//    {
//        	mSceneManager->getRootSceneNode()->removeChild(mSceneNode);
//
//	unsigned short index = 0;
//	Ogre::MovableObject *mo = mSceneNode->detachObject(index);
//	Ogre::Entity *ent = static_cast<Ogre::Entity *>(mo);
//
//	mSceneManager->destroyEntity(ent);
//	mSceneManager->destroySceneNode(mSceneNode);
//
//    }
////    delete mCollision;
//}

<<<<<<< HEAD
//bool GameObject::collides(GameObject *other, Ogre::Vector3 &MTD)
//{
//    return mCollision->collides(other->mCollision, MTD);
//
//}
//bool GameObject::collides(const RunnerObject &other, Ogre::Vector3 &MTD)
//{
//    return mCollision->collides(other.mCollision, MTD);
//}

void GameObject::setPosition(Ogre::Vector3 newPosition)
{
	mSceneNode->setPosition(newPosition);
//	mCollision->setPosition(newPosition);
	mPosition = newPosition;
=======


bool GameObject::collides(GameObject *other, Ogre::Vector3 &MTD)
{
    return mCollision->collides(other->mCollision, MTD);

}
bool GameObject::collides(const GameObject &other, Ogre::Vector3 &MTD)
{
    return mCollision->collides(other.mCollision, MTD);
}

void GameObject::setPosition(Ogre::Vector3 newPosition)
{
	mSceneNode->setPosition(newPosition);
	mCollision->setPosition(newPosition);
	mPosition = newPosition;

>>>>>>> origin/master
}

void GameObject::setOrientation(Ogre::Quaternion newOrientation)
{
    mSceneNode->setOrientation(newOrientation);
<<<<<<< HEAD
    //mcollision->setorientation(neworientation);
    mOrientation = newOrientation;
=======
    mCollision->setOrientation(newOrientation);
    mOrentation = newOrientation;
}

void GameObject::translate(Ogre::Vector3 delta)
{
	mCollision->translate(delta);
	mSceneNode->translate(delta);
	mPosition += delta;

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
>>>>>>> origin/master
}

void GameObject::yaw(Ogre::Degree d)
{
    mSceneNode->yaw(d);
<<<<<<< HEAD
//    mCollision->setOrientation(mSceneNode->getOrientation());
=======
    mCollision->setOrientation(mSceneNode->getOrientation());
>>>>>>> origin/master
}

void GameObject::pitch(Ogre::Degree d)
{
    mSceneNode->pitch(d);
<<<<<<< HEAD
//    mCollision->setOrientation(mSceneNode->getOrientation());
}


void GameObject::roll(Ogre::Degree d)
{
    mSceneNode->roll(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
=======
    mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::roll(Ogre::Degree d)
{
    mSceneNode->roll(d);
    mCollision->setOrientation(mSceneNode->getOrientation());
>>>>>>> origin/master
}

void GameObject::yaw(Ogre::Radian r)
{
    mSceneNode->yaw(r);
<<<<<<< HEAD
//    mCollision->setOrientation(mSceneNode->getOrientation());
=======
    mCollision->setOrientation(mSceneNode->getOrientation());

>>>>>>> origin/master
}

void GameObject::pitch(Ogre::Radian r)
{
    mSceneNode->pitch(r);
<<<<<<< HEAD
//    mCollision->setOrientation(mSceneNode->getOrientation());
=======
    mCollision->setOrientation(mSceneNode->getOrientation());

>>>>>>> origin/master
}

void GameObject::roll(Ogre::Radian r)
{
    mSceneNode->roll(r);
<<<<<<< HEAD
//    mCollision->setOrientation(mSceneNode->getOrientation());
=======
    mCollision->setOrientation(mSceneNode->getOrientation());
>>>>>>> origin/master
}
