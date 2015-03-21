#include "PhysicsManager.h"
using namespace std;

PhysicsManager::PhysicsManager() {
    //1
    _broadphase = new btDbvtBroadphase();
 
    //2
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);
 
    //3
    _solver = new btSequentialImpulseConstraintSolver();
 
    //4
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
 
    //5
    _world->setGravity(btVector3(0, -9.8, 0));
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
}