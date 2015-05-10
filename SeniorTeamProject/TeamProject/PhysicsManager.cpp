#include "PhysicsManager.h"
#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"
#include "World.h"
#include "Player.h"
#include "HUD.h"

using namespace std;

/* (TO: OLGA)
 * (From: Jordan)
 * I wrote this entire class, the code in the constructor and destructor is 
 * standard code for configuring the bullet physics environment.
 * 
 * Everything else is all me. 
 */

// Update: Diana worked on the collision and identification aspect of this class 


PhysicsManager::PhysicsManager() {
	/* Setup the bullet Physics world. */
    _broadphase = new btDbvtBroadphase();
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);
    _solver = new btSequentialImpulseConstraintSolver();
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
    _world->setGravity(btVector3(0, -100, 0));

	//_dispatcher->
}

PhysicsManager::~PhysicsManager() {
    delete _world;
    delete _solver;
    delete _collisionConfiguration;
    delete _dispatcher;
    delete _broadphase;
}

void PhysicsManager::addPlane() {
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -20, 0)));

	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBodyCI.m_restitution = 0.5f;
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	_world->addRigidBody(groundRigidBody);
}




void PhysicsManager::stepSimulation(float time, World* mWorld) {
	_world->stepSimulation(time, 10);
	/* update all physics objects */
	//for (std::list<IPhysObject*>::iterator it = physObjects.begin(); it != physObjects.end(); it++) {
	//	it._Ptr->_Myval->synchWithBullet();
	//}

	IPhysObject *objToRm; 
	bool remove = false; 

	/* update all physics objects */
	for (std::list<IPhysObject*>::iterator it = physObjects.begin(); it != physObjects.end(); it++) 
	{
		if (it._Ptr->_Myval->fallRigidBody->getUserIndex() != -1) 
		{
			struct MyContactResultCallback : public btDiscreteDynamicsWorld::ContactResultCallback
			{
				bool m_connected;
				MyContactResultCallback() 
				{
					m_connected = false;
				}
				
				virtual btScalar   addSingleResult(btManifoldPoint& cp,	
					const btCollisionObjectWrapper* colObj0Wrap,int partId0,
					int index0,const btCollisionObjectWrapper* colObj1Wrap,
					int partId1,int index1)  
				{
					m_connected = true; 
					return 0;
				}
			};

			MyContactResultCallback result;
			_world->contactPairTest(mWorld->mPlayer->getDynamicObject()->fallRigidBody, it._Ptr->_Myval->fallRigidBody, result);

			if (result.m_connected) {

				if (it._Ptr->_Myval->fallRigidBody->getUserIndex() == 1) 
				{

					remove = true;
					objToRm = it._Ptr->_Myval;

					mWorld->display->incrementScore();
					break; 
				}

				else if (it._Ptr->_Myval->fallRigidBody->getUserIndex() == 2)
				{
					mWorld->display->displayEnding(true);
				}
			}
		}
		it._Ptr->_Myval->synchWithBullet();
	}
	
	if (remove)
	{
		// removes from bullet 
		_world->removeRigidBody(objToRm->fallRigidBody);
		physObjects.remove(objToRm);

		// removes from world so it's no longer visible
		mWorld->SceneManager()->destroyEntity(objToRm->ent->getName().c_str()); 
	}

}


// Simon wrote this. 
bool
PhysicsManager::checkIntersect(btRigidBody *A, btRigidBody *B)
{
	btVector3 Amin;
	btVector3 Amax;
	btVector3 Bmin;
	btVector3 Bmax;

	A->getAabb(Amin, Amax);
	B->getAabb(Bmin, Bmax);

	OutputDebugString("\n Checking intersect \n");

	btScalar AmX, AmY, AmZ, AMX, AMY, AMZ, BmX, BmY, BmZ, BMX, BMY, BMZ;
	AmX = Amin.getX();
	AmY = Amin.getY();
	AmZ = Amin.getZ();

	AMX = Amax.getX();
	AMY = Amax.getY();
	AMZ = Amax.getZ();

	BmX = Bmin.getX();
	BmY = Bmin.getY();
	BmZ = Bmin.getZ();

	BMX = Bmax.getX();
	BMY = Bmax.getY();
	BMZ = Bmax.getZ();


	if ((((BmX <= AMX) && (BmY <= AMY ) && (BmZ <= AMZ )) &&
	     ((AMX <= BMX) && (AMY <= BMY ) && (AMZ <= BMZ) )) ||

		(((AmX <= BMX  ) && (AmY <= BMY ) && (AmZ <= BMZ) ) &&
		 ((BMX <= AMX  ) && (BMY <= AMY ) && (BMZ <= AMZ) )) ||

		 // B is inside of A
		(((AmX <= BmX) && (AmY <= BmY) && (AmX <= BmY)) &&
		 ((BMX <= AMX) && (BMY <= AMY) && (BMX <= AMY))) ||
		 // A is inside of B
		(((BmX <= AmX) && (BmY <= AmY) && (BmZ <= AmZ) ) &&
		 ((AMX <= BMX) && (AMY <= BMY) && (AMZ <= BMZ))))
		return true;
	else 
		return false;

}
