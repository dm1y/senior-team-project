#include "StaticScenery.h"

<<<<<<< HEAD
=======
/* (TO: OLGA)
 * (From: Jordan)
 *
 * This class is written entirely by me except for ogreToBulletMesh,
 *
 * I modified this code to work in our game:
 * http://tutorialsdl.googlecode.com/svn/trunk/Lab3/Lab3/OgreToBtMeshConverter.cpp
 */

>>>>>>> origin/Moscow
/* Static scenery represents a drawable mesh that is collidable
 * but does not move, such as level geometry.
 */
StaticScenery::StaticScenery(Ogre::Vector3 position, Ogre::String meshName, Ogre::SceneManager *sceneManager, PhysicsManager *physManager) {
	
	// create the scene node
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->setPosition(position);
	
	// attach the model entity
	Ogre::Entity *mEntity = sceneManager->createEntity(meshName);
	mEntity->setCastShadows(true);
	mSceneNode->attachObject(mEntity);


	// generate a collision shape from the mesh
	btTriangleMesh* btMesh = ogreToBulletMesh(mEntity->getMesh());
    btBvhTriangleMeshShape* btTriMeshShape = new btBvhTriangleMeshShape(btMesh, true, true);

	btCollisionObject* btObj = new btCollisionObject();
    btObj->setCollisionShape(btTriMeshShape);

	physManager->_world->addCollisionObject(btObj);


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