
#include "PhysicsManager.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class MyMotionState : public btMotionState
{
protected:
    Ogre::SceneNode* mSceneNode;
    btTransform mInitialPosition;

public:
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

    virtual void getWorldTransform(btTransform &worldTrans) const
    {
        worldTrans = mInitialPosition;
    }

    virtual void setWorldTransform(const btTransform &worldTrans)
    {
        if(mSceneNode == nullptr)
            return; 

        btQuaternion rot = worldTrans.getRotation();
		// TODO: Try and fix the error "pointer to incomplete class type is not allowed" below. 
        //*mSceneNode ->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        btVector3 pos = worldTrans.getOrigin();
        //*mSceneNode ->setPosition(pos.x(), pos.y(), pos.z());
    }
};