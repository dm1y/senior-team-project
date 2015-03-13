#include "OgreString.h"
#include "OgreVector3.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class World;

class GameObject
{
public:

	GameObject(World *world, Ogre::SceneManager *sceneManager); 

	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	void Think(float time);
    void loadModel(Ogre::String modelName);

	void yaw(Ogre::Degree d);
    void pitch(Ogre::Degree d);
    void roll(Ogre::Degree d);

    void yaw(Ogre::Radian r);
    void pitch(Ogre::Radian r);
    void roll(Ogre::Radian r);
	void translate(Ogre::Vector3 vector); 

	void setScale(Ogre::Vector3 newScale);
	void setPosition(Ogre::Vector3 newPosition);
	void setOrientation(Ogre::Quaternion newOrientation);
	void setAlpha(float alpha);

	Ogre::Vector3 getPosition() { return mPosition; }
    Ogre::Quaternion getOrientation() { return mOrientation; }
    Ogre::Vector3 getScale() { return mScale;}

	void setMaterial(Ogre::String materialName);
	void restoreOriginalMaterial();

	Ogre::SceneNode *getSceneNode() { return mSceneNode; }


protected:
    Ogre::SceneNode *mSceneNode;
    Ogre::SceneManager *mSceneManager;
    Ogre::Vector3 mScale;
	Ogre::Entity *mEntity;
	Ogre::String mMaterialName;
	Ogre::Quaternion mOrientation;
	Ogre::Vector3 mPosition;
	World *mWorld;
};

