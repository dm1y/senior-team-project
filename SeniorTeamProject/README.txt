Content (models / materials / overlays/ fonts / images / etc) are stored in TeamProject/Content
Game Data (JSON files / etc) are stored in TeamProject/GameData

Configuration files are stored in TeamProject/Content, and are copied into the 
ouput directory as a post-build step.

If you change directory structure, be sure to modify resources.cfg and resources_d.cfg
to point at the correct places.

-----------------------------------------------------------------------

Starter Code: 
Kinect.cpp/h, Menu.cpp/h, Logger.cpp/h, LoginWrapper.cpp/h, Receivers.cpp/h,
TeamProject.cpp/h, MainListener.cpp/h

Simon
Filenames:
 World.cpp/h, Player.cpp/h, Kinect.cpp/h
World - createWater(), doWaterStuff()
Player - movement related to Kinect, createHitBox(), drawHitBox(), 
		 drawSkeleton(), createLine(), drawLine(), clearLine(),
		 playAnimation(), finishAnimation(), stopAnimation(), disable()
Kinect - getSkeletonNodes(), modified initSensor for standing,
		 callibrate(), update(), performCalibration(), updateKinectSkeleton(),
		 detectSway(), detectLean(), detectArm(), detectTurn(), detectJump(),
		 getSkeletonAngles();
Number of Files - 8
Lines of Code (SLOC) - 925
Content (Mesh/Material) - Player, Animations, Water
Number of Files - 4
Lines of Code (SLOC) - 46

Diana
Filenames: 
 World.cpp/h, TeamProject.cpp/h, MainListener.cpp/h, Player.cpp/h
 GameLibrary.cpp, HUD.cpp/h, Camera.cpp/h, HUD.overlay, HUD.material, 
 Menu.material, StaticScenery.cpp/h, DynamicObject.cpp/h, iPhysObject.h,
 PhysicsManager.cpp 
My parts from starter code/overlapping code: 
 Pause menu, addition of the player, setup of the camera in World
 Setup of start game and menu in TeamProject
 Adding pause/quit capability in MainListener 
 Player constructor/setup, setAnimation function, keyboard input in Player
 Interaction capability in GameLibrary
 Added more materials in Menu.material  
 Adding interaction for StaticScenery and DynamicObjects
 Adding an entity for iPhysObject.h 
 stepSimulation function in PhysicsManager
Number of files: 22
Number of lines (SLOC): 873

Jordan 
Filenames:
World.cpp/h, TeamProject.cpp/h, GameLibrary.cpp/h, StaticScenery.cpp/h, DynamicObject.cpp/h,
iPhysObject.h, PhysicsManager.cpp/h, Console.cpp/h

GameLibrary - 349 lines of code
StaticScenery - 133
DynamicObject - 126
PhysicsManager - 60
Console - 260

868 lines of code in total

Models created:
	Island
	PalmTree1
	PalmTree2
	TreasureChest
	Banana
	Bridge
	InfoSign
