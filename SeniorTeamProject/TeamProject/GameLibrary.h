#ifndef GameLibrary_H
#define GameLibrary_H
#include <unordered_map>
#include "DynamicObject.h"
#include "string"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <stdio.h>
#include "btBulletDynamicsCommon.h"
#include "Stage.h"

using namespace std;

class GameLibrary {
private:
	unordered_map<string, DynamicObject*> dynamicObjects;
	unordered_map<string, StaticScenery*> staticScenery;
	unordered_map<string, Stage*> stages;
	btTriangleMesh* ogreToBulletMesh(Ogre::MeshPtr mesh);
public:
	GameLibrary(Ogre::SceneManager *sceneManager);
	DynamicObject * getDynamicObject(string name);
	StaticScenery * getStaticScenery(string name);
	Stage * getStage(string name);
	Ogre::SceneManager *mSceneManager;	
	Ogre::Vector3 parseVector3(const rapidjson::Value& x);
	btVector3 ogreToBulletVector3(Ogre::Vector3 x);
};

#endif