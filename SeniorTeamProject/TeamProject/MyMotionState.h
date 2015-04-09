
#include "PhysicsManager.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

/* Code below is from a tutorial. 
   Still unsure if we can use it to make motion states easier 
   (might make it easier for player movement as well as object movement in 
   general if we decide have additional moving objects). 
   Still tweaking it to have it compile since there are build errors as is. 
*/
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