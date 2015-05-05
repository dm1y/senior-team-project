#ifndef PhysicsManager_H
#define PhysicsManager_H
#include "IPhysObject.h"
//#include "DynamicObject.h"
//#include "Player.h"
#include <list>

//#include "OgreOverlayManager.h"
//#include "OgreOverlay.h"
//#include "OgreFontManager.h"
//#include "OgreTextAreaOverlayElement.h"
 
class PhysicsManager
{
private:

public:
	PhysicsManager();
	~PhysicsManager();
	void addBall(btVector3* initialPos);
	void addPlane();
	void stepSimulation(float time);
	bool checkIntersect(btRigidBody *A, btRigidBody *B);
	//void checkCollisions(Player *p, Ogre::Overlay *overly, Ogre::SceneManager *mSceneManager);

	btBroadphaseInterface* _broadphase;
    btDefaultCollisionConfiguration* _collisionConfiguration;
    btCollisionDispatcher* _dispatcher;
    btSequentialImpulseConstraintSolver* _solver;
    btDiscreteDynamicsWorld* _world;

	/* Stores all physics objects in the world */
	std::list<IPhysObject*> physObjects;

	/* Stores all interactive objects in the world */
	//std::list<DynamicObject*> dynaObjects;

	/* Overlay for ending when it collides with object */
	//Ogre::Overlay *overly;
};


#endif
