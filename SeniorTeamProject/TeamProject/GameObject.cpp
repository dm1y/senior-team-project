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

	//mCollision->setScale(newScale);
    mOrientation = Ogre::Quaternion::IDENTITY;
    mPosition = Ogre::Vector3::ZERO;

	mCollision->setScale(newScale);
}


/* Attaches a mesh named <modelName> to the GameObject instance's
 * scene node.
 */
void GameObject::loadModel(Ogre::String modelName)
{
    mEntity = SceneManager()->createEntity(modelName);
	mSceneNode->attachObject(mEntity);
	mMaterialName = mEntity->getSubEntity(0)->getMaterialName();
	mCollision = new OBB(mEntity->getBoundingBox());
	mMaxPointLocal = mEntity->getBoundingBox().getMaximum();
	mMinPointLocal =  mEntity->getBoundingBox().getMinimum();
	
	LPCSTR name = modelName.c_str();

	if (mEntity->hasSkeleton())
	{
		//OutputDebugString("HEEEEEEEEEEHEEEEEEEHEEEEE");
		//OutputDebugString(name);

		Ogre::StringVector anims = mEntity->getAnimableValueNames();

		for(Ogre::StringVector::const_iterator i = anims.begin(); i != anims.end(); i++)
		{
			//OutputDebugString(i->c_str());
		}

		Ogre::SkeletonInstance *skeleton = mEntity->getSkeleton();

		int animNum = skeleton->getNumAnimations();

		Ogre::Animation *anim = skeleton->getAnimation(0);

		//OutputDebugString(anim->getName().c_str());

		//OutputDebugString(std::to_string(animNum).c_str());

		//OutputDebugString("HEEEEEEEEEEHEEEEEEEHEEEEE");

		mEntity->getAnimationState("default_skl")->setEnabled(true);
		mEntity->getAnimationState("default_skl")->setLoop(true);
		mEntity->getAnimationState("default_skl")->setWeight(1.0);
		mEntity->getAnimationState("default_skl")->setLength(1.0);
	}
}


void GameObject::setMaterial(Ogre::String materialName)
{
	mEntity->setMaterialName(materialName);
}

void GameObject::restoreOriginalMaterial()
{
	mEntity->setMaterialName(mMaterialName);
}

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

}

void GameObject::setOrientation(Ogre::Quaternion newOrientation)
{
    mSceneNode->setOrientation(newOrientation);
    mOrientation = newOrientation;
    mCollision->setOrientation(newOrientation);
    mOrientation = newOrientation;
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

}

void GameObject::yaw(Ogre::Degree d)
{
    mSceneNode->yaw(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
    mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::pitch(Ogre::Degree d)
{
    mSceneNode->pitch(d);
//    mCollision->setOrientation(mSceneNode->getOrientation());
}


void GameObject::roll(Ogre::Degree d)
{
    mSceneNode->roll(d);
    mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::yaw(Ogre::Radian r)
{
    mSceneNode->yaw(r);

//    mCollision->setOrientation(mSceneNode->getOrientation());
    mCollision->setOrientation(mSceneNode->getOrientation());

}

void GameObject::pitch(Ogre::Radian r)
{
    mSceneNode->pitch(r);
//    mCollision->setOrientation(mSceneNode->getOrientation());
    mCollision->setOrientation(mSceneNode->getOrientation());

}

void GameObject::roll(Ogre::Radian r)
{
    mSceneNode->roll(r);
//    mCollision->setOrientation(mSceneNode->getOrientation());
    mCollision->setOrientation(mSceneNode->getOrientation());
}

void GameObject::Think(float time) {

	if (mEntity->hasSkeleton())
	{
		Ogre::AnimationState *anim = mEntity->getAnimationState("default_skl");
		//OutputDebugString(anim->getAnimationName().c_str());
		anim->addTime(time);
		if (mEntity->getAnimationState("default_skl")->hasEnded())
		{
			mEntity->getAnimationState("default_skl")->setEnabled(true);
			mEntity->getAnimationState("default_skl")->setWeight(1.0);
			mEntity->getAnimationState("default_skl")->setLength(1.0);
		}
		/*
			std::string posX = std::to_string(mPosition.x);
			std::string posY = std::to_string(mPosition.y);
			std::string posZ = std::to_string(mPosition.z);

			std::string pos;
			pos.append(posX);
			pos.append(posY);
			pos.append(posZ);
			*/
			//OutputDebugString(pos.c_str());
	}
}