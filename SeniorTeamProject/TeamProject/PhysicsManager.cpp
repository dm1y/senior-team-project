#include "PhysicsManager.h"
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


void PhysicsManager::stepSimulation(float time) {
	_world->stepSimulation(time, 10);

	/* update all physics objects */
	for (std::list<IPhysObject*>::iterator it = physObjects.begin(); it != physObjects.end(); it++) {
		it._Ptr->_Myval->synchWithBullet();
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

	if ((((Bmin.getX() <= Amax.getX()) && (Bmin.getY() <= Amax.getY()) && (Bmin.getZ() <= Amax.getZ())) &&
		((Amax.getX() <= Bmax.getX()) && (Amax.getY() <= Bmax.getY()) && (Amax.getZ() <= Bmax.getZ()))) ||
		(((Amin.getX() <= Bmax.getX()) && (Amin.getY() <= Bmax.getY()) && (Amin.getZ() <= Bmax.getZ())) &&
		((Bmax.getX() <= Amax.getX()) && (Bmax.getY() <= Amax.getY()) && (Bmax.getZ() <= Amax.getZ()))))
		return true;
	else 
		return false;
}