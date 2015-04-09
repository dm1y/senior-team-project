#ifndef GameLibrary_H
#define GameLibrary_H
#include <unordered_map>
#include "DynamicObject.h"
#include "string"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

using namespace std;

class GameLibrary {
private:
	unordered_map<string, DynamicObject*> dynamicObjects;
public:
	DynamicObject * getDynamicObject(string name);
};

#endif