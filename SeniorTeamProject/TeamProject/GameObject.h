#include "OgreString.h"
#include "OgreVector3.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsManager.h"

namespace Ogre
{
    class SceneManager;
    class SceneNode;
}

class World;

class GameObject
{
public:

	// From RunnerTransfer 
	enum ObjectType { PLAYER, NOTPLAYER };
	ObjectType getType() { return objType; }

	// Basic necessities 
	GameObject(Ogre::Vector3 position, PhysicsManager *physManager, World *world, Ogre::SceneManager *sceneManager, ObjectType gameObjType);
	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	Ogre::SceneNode *getSceneNode() { return mSceneNode; }
	void Think(float time);

	// From RunnerTransfer 
    void loadModel(Ogre::String modelName);

	// From RunnerTransfer -- not sure if we need this anymore though 
	void yaw(Ogre::Degree d);
    void pitch(Ogre::Degree d);
    void roll(Ogre::Degree d);

	// From RunnerTransfer -- not sure if we need this anymore though
    void yaw(Ogre::Radian r);
    void pitch(Ogre::Radian r);
    void roll(Ogre::Radian r);
	void translate(Ogre::Vector3 vector); 

	// From RunnerTransfer 
	void setScale(Ogre::Vector3 newScale);
	void setPosition(Ogre::Vector3 newPosition);
	void setOrientation(Ogre::Quaternion newOrientation);
	void setAlpha(float alpha); // not sure if this is needed so might remove 

	// For Bullet 
	Ogre::Vector3 getPosition() { return mPosition; }
    Ogre::Quaternion getOrientation() { return mOrientation; }
    Ogre::Vector3 getScale() { return mScale;}
	btRigidBody *getRigidBody() {return rigidBody; }
	btCollisionShape *getHitBox() {return hitBox; }
	void GameObject::setRigidBody() ;

	// From RunnerTransfer 
	void setMaterial(Ogre::String materialName);
	void restoreOriginalMaterial();
	
	// No longer used -- old collision/physics code 
	bool collides(GameObject *other, Ogre::Vector3 &MTD);
    bool collides(const GameObject &other, Ogre::Vector3 &MTD);
	Ogre::Vector3 minPointLocalScaled();
	Ogre::Vector3 maxPointLocalScaled();

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
	
	// For Bullet 
	PhysicsManager *mPhysManager;
	btRigidBody *rigidBody;
	btCollisionShape *hitBox;
	
};

