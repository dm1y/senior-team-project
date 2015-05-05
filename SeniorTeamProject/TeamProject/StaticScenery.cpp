#include "StaticScenery.h"

/* (TO: OLGA)
 * (From: Jordan)
 *
 * This class is written entirely by me except for ogreToBulletMesh,
 *
 * I modified this code to work in our game:
 * http://tutorialsdl.googlecode.com/svn/trunk/Lab3/Lab3/OgreToBtMeshConverter.cpp
 */

/* Static scenery represents a drawable mesh that is collidable
 * but does not move, such as level geometry.
 */

StaticScenery::StaticScenery(Ogre::Entity *mEntity) {
	
	mSceneNode = NULL;

	// save for later when we want to add it to the ogre scene
	this->mEntity = mEntity;

	// generate a collision shape from the mesh
	btTriangleMesh* btMesh = ogreToBulletMesh(mEntity->getMesh());
    btBvhTriangleMeshShape* btTriMeshShape = new btBvhTriangleMeshShape(btMesh, true, true);

	// save collion shape for later when we to add it the bullet world
	btObj = new btCollisionObject();
    btObj->setCollisionShape(btTriMeshShape);

	/* Save as btRigidBody */
	btDefaultMotionState* groundMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, btTriMeshShape, btVector3(0, 0, 0));

    mRigidBody = new btRigidBody(groundRigidBodyCI);

	// init position and rotation
	position = Ogre::Vector3(0, 0, 0);
	rotation = Ogre::Quaternion(1, 0, 0, 0);
}


StaticScenery::StaticScenery(Ogre::Entity *mEntity, btCollisionObject *colObject) {
	
	// save for later when we want to add it to the ogre scene
	this->mEntity = mEntity;

	// save collion shape for later when we to add it the bullet world
	btObj = colObject;
	
	/* Save as btRigidBody */
	btDefaultMotionState* groundMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, btObj->getCollisionShape(), btVector3(0, 0, 0));

    mRigidBody = new btRigidBody(groundRigidBodyCI);
}




btTriangleMesh* StaticScenery::ogreToBulletMesh(Ogre::MeshPtr mesh) {
	btTriangleMesh* btMesh = new btTriangleMesh();
	Ogre::Mesh::SubMeshIterator j = mesh->getSubMeshIterator();
    while (j.hasMoreElements()) {
        Ogre::SubMesh* submesh = j.getNext(); 
        
        int idxStart = submesh->indexData->indexStart;
        int nIdx = submesh->indexData->indexCount;
        
        Ogre::HardwareIndexBuffer* idxBuffer 
            = submesh->indexData->indexBuffer.get();
            
        Ogre::HardwareVertexBufferSharedPtr virtBuffer;
        Ogre::VertexDeclaration* virtDecl;
        
        if (submesh->useSharedVertices) {
            virtDecl = mesh->sharedVertexData->vertexDeclaration;
            assert(mesh->sharedVertexData->vertexBufferBinding->getBufferCount() > 0);
            virtBuffer = mesh->sharedVertexData->vertexBufferBinding->getBuffer(0);
        } else {
            virtDecl = submesh->vertexData->vertexDeclaration;
            assert(submesh->vertexData->vertexBufferBinding->getBufferCount() > 0);
            virtBuffer = submesh->vertexData->vertexBufferBinding->getBuffer(0);
        }
        
        unsigned char* pVert = static_cast<unsigned char*>(virtBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

        // need to lock the buffer since vertex data resides on GPU
        // and we need synchronization
        unsigned short* sindices = NULL;
        unsigned long* lindices = NULL;
        
        if (idxBuffer->getType() == Ogre::HardwareIndexBuffer::IT_16BIT) {
            sindices = static_cast<unsigned short*>(idxBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        } else if (idxBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT) {
            lindices = static_cast<unsigned long*>(idxBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        } else {
            assert(true == false);
        }
        
        const Ogre::VertexElement* elm = virtDecl->findElementBySemantic(Ogre::VES_POSITION, 0);
        int offset = elm->getOffset();
        // assert(elm->getType() == VET_FLOAT3);
        
        for (int k = idxStart; k < idxStart + nIdx; k += 3) {
            unsigned int indices[3];
            btVector3 vertices[3];
            
            if (idxBuffer->getType() == Ogre::HardwareIndexBuffer::IT_16BIT) {
                for (int l = 0; l < 3; ++l) {
                    indices[l] = sindices[k + l];
                }
            } else {
                for (int l = 0; l < 3; ++l) {
                    indices[l] = lindices[k + l];
                }
            }
            
            for (int l = 0; l < 3; ++l) { // for each vertex
                Ogre::Real* posVert = (Ogre::Real*)(pVert + indices[l] * virtBuffer->getVertexSize() + offset);
                for (int m = 0; m < 3; ++m) { // for each vertex component
                    vertices[l][m] = posVert[m];
                }
            }
            btMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
        }
            
        idxBuffer->unlock();
        virtBuffer->unlock();
    }

	return btMesh;
}

void StaticScenery::addToOgreScene(Ogre::SceneManager *sceneManager) {
	/* create a new scene node */
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mEntity);	// attach entity to the new scene node
	synchWithBullet();
}

void StaticScenery::addToBullet(PhysicsManager *physmanager) {
	// physmanager->_world->addCollisionObject(btObj);
	physmanager->_world->addRigidBody(this->mRigidBody);
}

void StaticScenery::setPosition(Ogre::Vector3 newPos) {

	// update bullet
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
	//mRigidBody->setCenterOfMassTransform(trans);
	mRigidBody->setWorldTransform(trans);
}

void StaticScenery::setOrientation(Ogre::Quaternion newRot) {
	
	// update bullet
	btTransform trans = mRigidBody->getCenterOfMassTransform();
	trans.setRotation(btQuaternion(newRot.x, newRot.y, newRot.z, newRot.w));
	//mRigidBody->setCenterOfMassTransform(trans);
	mRigidBody->setWorldTransform(trans);
}


void StaticScenery::synchWithBullet() {
	btTransform trans;
    mRigidBody->getMotionState()->getWorldTransform(trans);	
	Ogre::Real x = trans.getOrigin().getX();
	Ogre::Real y = trans.getOrigin().getY();
	Ogre::Real z = trans.getOrigin().getZ();

	Ogre::Real Qx = trans.getRotation().getX();
	Ogre::Real Qy = trans.getRotation().getY();
	Ogre::Real Qz = trans.getRotation().getZ();
	Ogre::Real Qw = trans.getRotation().getW();
	mSceneNode->setPosition(Ogre::Vector3(x, y, z));
	mSceneNode->setOrientation(Qw, Qx, Qy, Qz);
}




StaticScenery * StaticScenery::clone() {
	return new StaticScenery(this->mEntity, this->btObj);
}