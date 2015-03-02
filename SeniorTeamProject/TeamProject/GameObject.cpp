#include "GameObject.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
//#include "CollisionManager.h"
#include "OgreSubEntity.h"
#include "OgreMaterial.h"

GameObject::GameObject(ObjectType type) : mType(type)
{
    mCollision = NULL;
    mSceneNode = NULL;
    mOrentation = Ogre::Quaternion::IDENTITY;
    mPosition = Ogre::Vector3::ZERO;
}


GameObject::~GameObject(void)
{
    mScale = Ogre::Vector3::UNIT_SCALE;
    if (mSceneNode != NULL)
    {
        	mSceneManager->getRootSceneNode()->removeChild(mSceneNode);

	unsigned short index = 0;
	Ogre::MovableObject *mo = mSceneNode->detachObject(index);
	Ogre::Entity *ent = static_cast<Ogre::Entity *>(mo);

	mSceneManager->destroyEntity(ent);
	mSceneManager->destroySceneNode(mSceneNode);

    }
//    delete mCollision;
}


//bool GameObject::collides(GameObject *other, Ogre::Vector3 &MTD)
//{
//    return mCollision->collides(other->mCollision, MTD);
//
//}
//bool GameObject::collides(const RunnerObject &other, Ogre::Vector3 &MTD)
//{
//    return mCollision->collides(other.mCollision, MTD);
//}




void GameObject::setScale(Ogre::Vector3 newScale)
{
	mScale = newScale;
	mSceneNode->setScale(newScale);
	//mCollision->setScale(newScale);
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


void 
	GameObject::loadModel(Ogre::String modelName, Ogre::SceneManager *sm)
{
    mSceneManager = sm;
    mEntity =sm->createEntity(modelName);
	mSceneNode =sm->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mEntity);
    //mCollision = new OBB(mEntity->getBoundingBox());
	mMaxPointLocal = mEntity->getBoundingBox().getMaximum();
	mMinPointLocal =  mEntity->getBoundingBox().getMinimum();
	mMaterialName = mEntity->getSubEntity(0)->getMaterialName();
}



void GameObject::setMaterial(Ogre::String materialName)
{
	mEntity->setMaterialName(materialName);
}

void GameObject::restoreOriginalMaterial()
{
	mEntity->setMaterialName(mMaterialName);
}


void GameObject::setAlpha(float alpha)
{
	for (unsigned int i = 0; i < mEntity->getNumSubEntities(); i++)
	{

		mEntity->getSubEntity(i)->getMaterial()->getBestTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
		mEntity->getSubEntity(i)->getMaterial()->getBestTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, alpha);

	}


}

//void GameObject::setPosition(Ogre::Vector3 newPosition)
//{
//	mSceneNode->setPosition(newPosition);
//	mCollision->setPosition(newPosition);
//	mPosition = newPosition;
//
//}
//void GameObject::setOrientation(Ogre::Quaternion newOrientation)
//{
//    mSceneNode->setOrientation(newOrientation);
//    mCollision->setOrientation(newOrientation);
//    mOrentation = newOrientation;
//}
//void GameObject::yaw(Ogre::Degree d)
//{
//    mSceneNode->yaw(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//}
//void GameObject::pitch(Ogre::Degree d)
//{
//    mSceneNode->pitch(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//}
//
//void GameObject::translate(Ogre::Vector3 delta)
//{
//	mCollision->translate(delta);
//	mSceneNode->translate(delta);
//	mPosition += delta;
//}
//
//
//
//void GameObject::roll(Ogre::Degree d)
//{
//    mSceneNode->roll(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//
//
//}
//
//void GameObject::yaw(Ogre::Radian r)
//{
//        mSceneNode->yaw(r);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//
//}
//void GameObject::pitch(Ogre::Radian r)
//{
//        mSceneNode->pitch(r);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//
//}
//void GameObject::roll(Ogre::Radian r)
//{
//        mSceneNode->roll(r);
//    mCollision->setOrientation(mSceneNode->getOrientation());
//
