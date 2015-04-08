#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"


namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class MyMotionState : public btMotionState
{
protected:

    //Ogre::SceneNode* mSceneNode;
    //btTransform mInitialPosition;

public:
	Ogre::SceneNode* mSceneNode;
    btTransform mInitialPosition;

    MyMotionState(const btTransform &initialPosition, Ogre::SceneNode *node)
    {
        mSceneNode = node;
		mInitialPosition = initialPosition;
    }

    virtual ~MyMotionState()
    {
    }

    void setNode(Ogre::SceneNode *node)
    {
        mSceneNode = node;
    }

	Ogre::SceneNode* mSceneNode() { return mSceneNode; }

    virtual void getWorldTransform(btTransform &worldTrans) const
    {
        worldTrans = mInitialPosition;
    }

    virtual void setWorldTransform(const btTransform &worldTrans)
    {
        if(mSceneNode == nullptr)
            return; // silently return before we set a node

        btQuaternion rot = worldTrans.getRotation();
        mSceneNode ->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        btVector3 pos = worldTrans.getOrigin();
        mSceneNode ->setPosition(pos.x(), pos.y(), pos.z());
    }
};