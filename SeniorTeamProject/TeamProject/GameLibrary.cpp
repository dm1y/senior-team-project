#include "GameLibrary.h"

/* (TO: OLGA)
 * (From: Jordan)
 *
 * All of the code is written by me, except for the JSON parser (rapidjson).
 */


/* A library of content that can be put into the game.
 *
 *	Glossary:
 *		Part 1: Loading things into the library from JSON files
 *		Part 2: Getting things from the library into the game
 *
 * ############################################################
 * # Part 1: Loading things in to the library from JSON files #
 * ############################################################

 * Data in the library is loaded from json files which specify class and how 
 * configurations for what you are putting in the library.
 *
 * For example:
 * To make a coin you could make the following Coin.json file:
 *
 * __________________________________________________________
 *	{
 *		"DynamicObject" : 
 *		{
 *			"meshName" : "Coin.MESH.mesh",
 *			"mass" : 1,
 *			"collisionShape" : "btBoxShape",
 *			"collisionShapeSize" : [1,1,1],
 *			"restitution" : 1
 *		}
 *	}
 * ____________________________________________________________
 *
 * The class you use depends on what you want the object to do, for the coin I
 * chose DynamicObject because I wanted it to have collision and physics.
 *
 *
 *
 * Rules for writing .json library files:
 *
 *		1. Use this format: { {"CLASSNAME" : <PROPERTIES> } }
 *		The CLASSNAME let's the GameLibrary loader know how to parse the PROPERTIES
 *		part. You can define the properties however you like to describe a class.
 *
 *		2. The filename is important!
 *		   The file name is used for lazy loading of object.
 *         Rather than having a seperate mapping of object names to the files that 
 *		   describe them, the file name simply is the same as the object name.
 *   	   For example: if the program calls getDynamicObject("Coin") and it has not 
 *		   been loaded into the Library yet, Library will look for and load a file 
 *		   called Coin.json.
 *
 *
 * #########################################################
 * # Part 2: Getting things from the library into the game #
 * #########################################################
 *
 * To load an object from the library simply use the method corresponding to
 * the object type you want to load. For example, loading a dynamic object
 * might looks like this:
 *
 * DynamicObject *d = gameLibrary->getDynamicObject("Box");
 *
 * To actually put the object into the game you must add it to
 * the bullet and ogre world, for example:
 *
 * d->addToOgreScene(mSceneManager);
 * d->addToBullet(physManager);
 */
DynamicObject * GameLibrary::getDynamicObject(string name) {

	// polymorphic maps in c++ scare me, so for now
	// the gamelibrary has a seperate map for each type.
	// Maybe talk to gallas about polymorphic data structures in c++.

	// see if an instance of the object exists in dynamicObjects map.
	// if not load it in from memory, create it, and put it in the map.

	// TODO: if no value is found for key handle error gracefully.

	unordered_map<string, DynamicObject*> ::iterator it = dynamicObjects.find(name);

	DynamicObject *dynObj;
 	if(it != dynamicObjects.end())
	{
		//element found;
		dynObj = it->second;

		// create a clone of it.
		return dynObj->clone();

	} else {
		// element was not found.
		// load it in and create instance 

		std::string fileName = "../TeamProject/GameData/DynamicObjects/" + name +".json";
		FILE* pFile = fopen(fileName.c_str(), "rb");
		
		if(pFile != NULL) {
			char buffer[65536];
			rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
			rapidjson::Document document;
			document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

			// File was opened successfully and parsed into JSON,
			// now we create the instance

			std::list<std::string> meshNames;

			for (int i=0; i < document["meshNames"].Size(); i++)
				meshNames.push_back(document["meshNames"][i].GetString());
			double restitution = document["restitution"].GetDouble();
			int mass = document["mass"].GetInt();
			
			string collisionShape = document["collisionShape"].GetString();


			btCollisionShape *colShape;

			if(collisionShape.compare("btCapsuleShape") == 0) {

				// set colShape to btCapsuleShape here!
				double colDimX = document["collisionShapeSize"][0].GetDouble();
				double colDimY = document["collisionShapeSize"][1].GetDouble();
				colShape = new btCapsuleShape(colDimX, colDimY);


			} else {

				// assume every other collision shape takes 3 paramters,
				// we can add in additional conditions for handling other shapes
				// as needed.

				// for now since most collision shapes take 3 params we parse all of them in this
				// else block.
				double colDimX = document["collisionShapeSize"][0].GetDouble();
				double colDimY = document["collisionShapeSize"][1].GetDouble();
				double colDimZ = document["collisionShapeSize"][2].GetDouble();
				btVector3 colDim = btVector3(colDimX, colDimY, colDimZ); 


						
			// figure out collision shape and parse its dimensions
			if(collisionShape.compare("btSphereShape") == 0) {
				// TODO: implement btSphereShape
			} else if(collisionShape.compare("btBoxShape") == 0) {
				colShape = new btBoxShape(colDim);
			} else if(collisionShape.compare("btCylinderShape") == 0) {
				colShape = new btCylinderShape(colDim);
			} else if(collisionShape.compare("btConeShape") == 0) {
				// TODO: implement btConeShape
			} else if(collisionShape.compare("btMultiSphereShape") == 0) {
				// TODO: implement btMultiSphereShape
			} else if(collisionShape.compare("btConvexHullShape") == 0) {
				// TODO: implement btConvexHullShape
			} else if(collisionShape.compare("btConvexTriangleMeshShape") == 0) {
				// TODO: implement btConvexTriangleMeshShape
			} else if(collisionShape.compare("btCompoundShape") == 0) {
				// TODO: implement btCompoundShape
			}

			}


			

			



			// CREATE DYNAMICOBJECT OBJECT with default position at 0,0,0
			// position can be changed later.
			DynamicObject *newD = new DynamicObject(meshNames, colShape, Ogre::Vector3(0,0,0));


			// put it into the library
			dynamicObjects.emplace(name, newD);

			fclose(pFile);

			return newD->clone();

		} else {
			// no file was found
			// TODO: HANDLE GRACEFULLY!
			DynamicObject * x;
			x->clone();
		}
	}
}
