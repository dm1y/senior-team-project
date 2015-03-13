#include "OgreString.h"
#include "OgreVector3.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class OBB;
class World;

class GameObject
{
public:

	enum ObjectType { PLAYER, NOTPLAYER };
	ObjectType getType() { return objType; }

	GameObject(World *world, Ogre::SceneManager *sceneManager, ObjectType gameObjType); 

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

<<<<<<< HEAD
=======
	
	void translate(Ogre::Vector3 vector); 
	
	bool collides(GameObject *other, Ogre::Vector3 &MTD);
    bool collides(const GameObject &other, Ogre::Vector3 &MTD);

	Ogre::Vector3 minPointLocalScaled();
	Ogre::Vector3 maxPointLocalScaled();

	void setPosition(Ogre::Vector3 newPosition);
	void setOrientation(Ogre::Quaternion newOrientation);

	Ogre::Vector3 getPosition() { return mPosition; }
    Ogre::Quaternion getOrientation() { return mOrentation; }
>>>>>>> origin/master

protected:
    Ogre::SceneNode *mSceneNode;
    Ogre::SceneManager *mSceneManager;
    Ogre::Vector3 mScale;
	Ogre::Entity *mEntity;
	Ogre::String mMaterialName;
	Ogre::Quaternion mOrientation;
	Ogre::Vector3 mPosition;
	World *mWorld;

	Ogre::Vector3 mMinPointLocal;
	Ogre::Vector3 mMaxPointLocal;
	ObjectType objType;
	OBB *mCollision;
    Ogre::Vector3 mPosition;
    Ogre::Quaternion mOrentation;
};

