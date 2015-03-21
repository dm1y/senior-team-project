#ifndef PhysicsManager_H
#define PhysicsManager_H
#include "btBulletDynamicsCommon.h"
#include <iostream>
 
class PhysicsManager
{
private:

public:
	PhysicsManager();
	~PhysicsManager();
	void addBall(btVector3* initialPos);
	void addPlane();
	void stepSimulation(float time);
	btBroadphaseInterface*                  _broadphase;
    btDefaultCollisionConfiguration*        _collisionConfiguration;
    btCollisionDispatcher*                  _dispatcher;
    btSequentialImpulseConstraintSolver*    _solver;
    btDiscreteDynamicsWorld*                _world;
};


#endif
