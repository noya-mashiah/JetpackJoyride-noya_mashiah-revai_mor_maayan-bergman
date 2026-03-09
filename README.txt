Oop2 project - Jetpack Joyride
=================================
Written by: revai mor, id = 209070655
Written by: noya mashiah, id = 211997994
Written by: maayan bergman, id = 212014526

general explanation :
=========================
This program implements the game Jetpack Joyride.

Game Goal
---------
The goal of the game is to reach the greatest possible distance, 
measured in meters, without dying from an enemie or obstacle.

Game Objects
------------
1. Player:
   - Moves using the space key.Pressing the key makes the player jump up, 
     releasing it brings the player back to the ground.
   - Must avoid enemies and obstacles that can kill him.
   - Can collect gifts, some of which change his state and grant special powers.

2. Enemies:
   1. Missiles - Coming from the right side of the screen. There is an alarm image 
                 and sound alerting from missile incoming.
   2. Bat - That emits sonic waves. the bat itself is harmless, but the waves
            are dangerous.
   3. Chicken - That lays eggs, which are hazards for the player. 
                The Chicken himself is harmless.
   4. Piranha - An enemy present only in the special sea mode, throws electric
                balls at the player. The piranha itself is harmless.
   5. Shark - An enemy appearing only in the special sea mode.
   6. Crab - An enemy appearing only in the special sea mode.
   
3. Obstacles:
   - Lasers of various sizes that electrify the player upon contact.
  
4. Gifts :
   1. PowerUpBox:
      Collecting the Power-up box changes the player's state to one of the following:
      1. Robot mode - movement same as regular player, has a special gift (gasTank) 
	                  if collected by the player gives imunity from hitting for
					  10 seconds
	  2. Bird mode - movement same as regular player. Collecting a coin in this 
	                 mode double its value.
	  3. Dinosaur mode - In this mode you can move by jumping (every pressing 
	                     on the spacebar is one jump).  has a special gift 
						 (steak) that flies rapidly the player across the board
						 for 10 seconds.
	  4. UpsideDown mode - Can walk on the floor or the ceiling. Each press of 
	                       the spacebar switches the walking direction to the 
						   opposite side.
	  5. Surf mode - Changes the game to be in a sea state , has special 
	                 enemies and gifts. The player moves along the wave line.
                     A long press on the spacebar attaches the player to the 
					 floor, releasing it moves him to the ceiling, then back
					 to the wave line. The shorter the press on the spacebar, 
					 the smaller the vertical movement up or down. 
					 This mode has a timer of 60 seconds.
					 
	  Note: If the player is in some mode and collects another PowerUpBox he 
	        will change to one of the listed modes. Unless he's in Robot or 
            Dinosaur mode and taken their special gift - then collecting the 
			PowerUpBox will grant him nothing.
	  Note: When the power-up box is collected, the player lands on the floor 
	        from their current position. If the player collides with a deadly
			object during the landing, he wont die.
	  Note: Collecting a special gift for a specific mode while the player is 
	        in a different mode will not grant its power. 	  
    2. Coins 
	3. Shell:
	   collecting a shell displays pearls on the screen, with each pearl worth 
	   5 coins.  

5. Decorations:
   - Scientists 
   - Light balls
   - Fish (in sea state)
   - Jellyfish (in sea state)

Info Bar
--------
Displayes during the game:
- The distance in meters
- Number of coins collected

Screens and buttons
---------------------
1. Main screen: 
   has 4 buttons
   1. Play - start the game
   2. Quit - closes the program 
   3. Help - has information about how to play the game 
   4. highScoreList - Located at the top left side of the screen.
                      Pressing it displays a screen with a list of
					  up to the top 5 best player scores.
   5. Mute 
2. Gear button:
   pressing it pauses the game.
   has 3 buttons:
   1. resume - returns to the game 
   2. Quit - returns to main screen
   3. Mute
3. Mute Button:
   Pressing it toggles mute for the game music (not the sound effects).
   Each press switches to the opposite mute state.

file list:
============
Animation.h  
Animation.cpp  
BackgroundManager.h  
BackgroundManager.cpp  
BaseButton.h  
BaseButton.cpp  
BirdPlayerState.h  
BirdPlayerState.cpp  
Chicken.h  
Chicken.cpp  
Coin.h  
Coin.cpp  
Collision.h  
Collision.cpp  
CollisionManager.h  
CollisionManager.cpp  
CommandButton.h  
CommandButton.cpp  
Consts.h  
Consts.cpp  
Controller.h  
Controller.cpp  
Crab.h  
Crab.cpp  
DecorativeMovingObject.h  
DecorativeMovingObject.cpp  
DieCommand.h  
DieCommand.cpp  
DiePlayerState.h  
DiePlayerState.cpp  
DinosaurPlayerState.h  
DinosaurPlayerState.cpp  
Egg.h  
Egg.cpp  
Enemy.h  
Enemy.cpp  
Exceptions.h  
Exceptions.cpp  
FlyCommand.h  
FlyCommand.cpp  
GameManager.h  
GameManager.cpp  
GameObject.h  
GameObject.cpp  
GameObjectFactory.h  
GameObjectFactory.cpp  
GameObjectManager.h  
GameObjectManager.cpp  
GameObjectParams.h  
GameObjectParams.cpp  
GameOverState.h  
GameOverState.cpp  
GameState.h  
GameState.cpp  
GasTank.h  
GasTank.cpp  
GeometryPhysicsUtilities.h  
GeometryPhysicsUtilities.cpp  
GraphicUtilities.h  
GraphicUtilities.cpp  
HallAnimation.h  
HallAnimation.cpp  
HelpCommand.h  
HelpCommand.cpp  
HelpLeftCommand.h  
HelpLeftCommand.cpp  
HelpRightCommand.h  
HelpRightCommand.cpp  
HelpState.h  
HelpState.cpp  
HighScoresManager.h  
HighScoresManager.cpp  
HighScoresState.h  
HighScoresState.cpp  
Hourglass.h  
Hourglass.cpp  
HoverButton.h  
HoverButton.cpp  
InfoBar.h  
InfoBar.cpp  
JumpCommand.h  
JumpCommand.cpp  
LaserComponent.h  
LaserComponent.cpp  
LaserConfig.h  
LaserConfig.cpp  
LaserObstacle.h  
LaserObstacle.cpp  
LandGameState.h  
LandGameState.cpp  
MainMenuState.h  
MainMenuState.cpp  
Meat.h  
Meat.cpp  
Missile.h  
Missile.cpp  
MissileAlarm.h  
MissileAlarm.cpp  
MovingObject.h  
MovingObject.cpp  
MuteCommand.h  
MuteCommand.cpp  
Obstacles.h  
Obstacles.cpp  
PauseCommand.h  
PauseCommand.cpp  
PauseState.h  
PauseState.cpp  
Pearl.h  
Pearl.cpp  
Pickables.h  
Pickables.cpp  
PlayCommandButton.h  
PlayCommandButton.cpp  
Player.h  
Player.cpp  
PlayerCommand.h  
PlayerCommand.cpp  
PlayerEffect.h  
PlayerEffect.cpp  
PlayerState.h  
PlayerState.cpp  
PowerUpBox.h  
PowerUpBox.cpp  
Projectile.h  
Projectile.cpp  
ProjectileEnemy.h  
ProjectileEnemy.cpp  
QuitButtonCommand.h  
QuitButtonCommand.cpp  
RegularPlayerState.h  
RegularPlayerState.cpp  
ResourcesManager.h  
ResourcesManager.cpp  
ReturnToMenuCommand.h  
ReturnToMenuCommand.cpp  
RobotPlayerState.h  
RobotPlayerState.cpp  
RunGameState.h  
RunGameState.cpp  
SeaGameState.h  
SeaGameState.cpp  
Shark.h  
Shark.cpp  
Shell.h  
Shell.cpp  
ShowHighScoresCommand.h  
ShowHighScoresCommand.cpp  
SimpleButton.h  
SimpleButton.cpp  
SoundState.h  
SoundState.cpp  
StaticObject.h  
StaticObject.cpp  
SurferPlayerState.h  
SurferPlayerState.cpp  
SwirlItem.h  
SwirlItem.cpp  
ToggleButton.h  
ToggleButton.cpp  
UnmuteCommand.h  
UnmuteCommand.cpp  
UpsideDownPlayerState.h  
UpsideDownPlayerState.cpp  
UpsideDownWalkCommand.h  
UpsideDownWalkCommand.cpp  
WalkCommand.h  
WalkCommand.cpp  
WallLamp.h  
WallLamp.cpp  
WaveSurfCommand.h
WaveSurfCommand.cpp
WindowUtilities.h
WindowUtilities.cpp

Main Data Structures and Their Roles:
======================================
classes
sound and music 
Design patterns
stl containers : the explenation for choosing each container is in the class
				 information his in.

Notable Algorithms:
=====================
- Calculating a heart shape for coins, perals and etc.


UML Class Diagrams:
=====================
Visual documentation of the project's class hierarchy and relationships
is available in resources/Images/inharitance_trees_uml/.

The following UML diagrams illustrate the inheritance structure:
- Button.png - Button class hierarchy (BaseButton and its implementations)
- ButtonCommand.png - Command Pattern for buttons
- GameState.png - Game state hierarchy (menu, play, pause, etc.)
- GameObjectTree.png - Complete GameObject inheritance tree
- MovingObjectTree.png - MovingObject subclass hierarchy
- ObstaclesTree.png - Obstacle types and their relationships
- PickablesTree.png - Pickable items hierarchy
- PlayerCommand.png - Command Pattern for player actions
- PlayerState.png - State Pattern for player modes
- Managers.png - Manager classes and their relationships
- entireClassDiagram.png - Complete project class diagram
- ExpandedClassDiagram.png - Detailed expanded class diagram


Design :                  
===============
Animation -
-------------
Handles sprite sheet animation for game objects.

BackgroundManager -
--------------------
Manages parallax backgrounds, scrolling, and wave effects.

BaseButton -
--------------
Abstract base class for all UI buttons.

BirdPlayerState -
-------------------
Implements the “bird” state for the player (flying, collecting coins in the air).
Inherits from PlayerState.

Chicken -
----------
Enemy class representing a chicken that can drop eggs. Inherits from Enemy.

Coin -
---------
Pickable coin object. Inherits from Pickables.

Collision -
------------
Utility functions for collision detection between objects. This class we didnt 
write - we received approval via email from the teaching assistant to use this
file.

CollisionManager -
-------------------
Handles dispatching and processing of collisions between game objects.
We use a std::map to map pairs of object types to their specific collision 
functions. This allows clean and efficient runtime dispatch based on object
types, avoiding long if elses and making the system easy to extend.

CommandButton -
----------------
Button that executes a command (Command Pattern) when clicked. 
Inherits from BaseButton.

Consts -
---------
Defines global constants for the game.

Controller -
--------------
Main gameplay controller: manages the player, game objects, input, and updates.
Composes a GameObjectManager.

Crab -
--------
Enemy class representing a crab. Inherits from Enemy.

DecorativeMovingObject -
-------------------------
Represents decorative moving objects (e.g., fish, scientist) in the background.
Inherits from MovingObject.

DieCommand -
--------------
Command for handling player death (Command Pattern). Inherits from PlayerCommand.

DiePlayerState -
-----------------
Implements the “dying” state for the player. Inherits from PlayerState.

DinosaurPlayerState -
----------------------
Implements the “dinosaur” state for the player (invincible, special moves).
Inherits from PlayerState.

Egg -
------
Egg object (dropped by the Chicken enemy). Inherits from Pickables.

Enemy -
---------
Abstract base class for all enemy types. Inherits from MovingObject.

Exceptions -
-------------
Custom exception classes for error handling, inheriting from std::exception.

FlyCommand  -
--------------
Command for handling player flying (Command Pattern).
Inherits from PlayerCommand.

GameManager -
--------------
Central class for managing the main game loop, states, and core systems.
Composes a Controller, uses the State Pattern.

GameObject -
-------------
Abstract base class for all interactive/drawable game objects.

GameObjectFactory -
---------------------
Factory for creating game objects by name. Uses std::Unorderedmap and function 
pointers: Maintains a map of creation functions by string name enabling easy 
addition of new object types without modifying core logic.  
Also, enables fast O(1) object creation by name or ID.

GameObjectManager -
--------------------
Manages creation, updating, rendering, and cleanup of all game objects.
We use std::list to manage game objects because they are consistently added to
the back and removed from the front. This usage pattern benefits from the list's
O(1) insertion and removal at both ends, making it more efficient than a vector. 

GameObjectParams -
-------------------
Struct for passing parameters to game object constructors.

GameOverState -
----------------
Manages the game over screen and its UI. Inherits from GameState.

GameState -
-------------
Abstract base class for all game states (menu, play, pause, etc.).

GasTank - 
----------
Pickable gas tank object. Inherits from Pickables.

GeometryPhysicsUtilities -
----------------------------
Utility functions for geometry and physics calculations.

GraphicUtilities -
--------------------
Utility functions for graphics (scaling, bounds, etc.).

HallAnimation -
---------------- 
Handles the animated hall background and its sound effect.
Inherits from StaticObject.

HelpCommand / HelpLeftCommand / HelpRightCommand -
---------------------------------------------------
Commands for help navigation (Command Pattern).Inherit from PlayerCommand.

HelpState -
-----------
Manages the help screen and its navigation. Inherits from GameState.

HighScoresManager -
--------------------
Manages high scores: loading, saving, and updating. Uses std::vector and file I/O:

HighScoresState -
--------------------
Manages the high scores screen and its UI. Inherits from GameState.

Hourglass -
------------
Static hourglass object - to indicate timer of special gifts. 
Inherits from StaticObject.

HoverButton -
---------------
Button with a hover effect. Inherits from BaseButton.

InfoBar -
----------
Displays game information (score, coins, etc.) on screen.

JumpCommand -
--------------
Command for handling player jump (Command Pattern).Inherits from PlayerCommand.

LaserComponent -
-----------------
Represents a part of a laser obstacle (head or beam).Inherits from Obstacles.

LaserConfig -
--------------
Struct for configuring laser obstacle parameters.

LaserObstacle -
-----------------
Composite obstacle made of multiple LaserComponent parts. Inherits from Obstacles.
Manages ownership and lifetime of laser parts safely and efficiently.

LandGameState -
-----------------
Game state for land gameplay. Inherits from RunGameState.

MainMenuState -
----------------
Manages the main menu screen and its UI. Inherits from GameState.

Meat -
-------
Pickable meat object. Inherits from Pickables.

Missile -
-----------
Enemy missile object. Inherits from Enemy.

MissileAlarm -
---------------
Visual/sound alarm for incoming missiles. Inherits from StaticObject.

MovingObject -
----------------
Abstract base class for all moving objects. Inherits from GameObject.

MuteCommand -
--------------
Command for muting sound (Command Pattern). Inherits from PlayerCommand.

Obstacles -
-------------
Abstract base class for all obstacles. Inherits from StaticObject.

PauseCommand -
---------------
Command for pausing the game (Command Pattern). Inherits from PlayerCommand.

PauseState -
-------------
Manages the pause screen and its UI. Inherits from GameState.

Pearl -
---------
Pickable pearl object. Inherits from Pickables.

Pickables -
------------
Abstract base class for all pickable objects (coins, gifts, etc.).
Inherits from MovingObject.

PlayCommandButton -
--------------------
Button for starting the game (executes play command). Inherits from CommandButton.

Player -
----------
Main player character, manages state, input, and interactions.
Inherits from MovingObject.

PlayerCommand -
----------------
Abstract base class for player commands (Command Pattern).

PlayerEffect -
-----------------
Visual effect attached to the player (e.g., sparkles, flames, wings).

PlayerState - 
--------------
Abstract base class for player states (regular, bird, dino, etc.).

PowerUpBox -
--------------
Pickable power-up box object. Inherits from Pickables.
Uses std::unordered_map: Allows fast lookup of player effects or state data.
Map random integers to player state change functions for fast, direct access.
Ordering is not important here—only efficient key-based retrieval is needed, 
making an unordered map ideal.

Projectile -
-------------
Represents a projectile (light ball, wave, etc.).
Inherits from MovingObject.

ProjectileEnemy -
-------------------
Enemy that uses a projectile (bat, piranha, etc.). Inherits from Enemy.

QuitButtonCommand - 
--------------------
Command for quitting the game (Command Pattern). Inherits from PlayerCommand.

RegularPlayerState - 
---------------------
Implements the regular state for the player. Inherits from PlayerState.

ResourcesManager - 
---------------------
Singleton for managing all game resources (textures, sounds, fonts).
Uses std::Unorderedmap. Ensures only one instance manages resources, preventing
duplicate loads. Allows fast O(1) access to textures, sounds, and music by name,
making it the most efficient choice for key-based resource management where 
order doesn't matter.

ReturnToMenuCommand - 
-----------------------
Command for returning to the main menu (Command Pattern).
Inherits from PlayerCommand.

RobotPlayerState -
--------------------
Implements the robot state for the player (invincible, sparkles, etc.).
Inherits from PlayerState.

RunGameState -
---------------
Abstract base class for running gameplay states (land/sea).
Inherits from GameState.

SeaGameState -
---------------
Game state for sea gameplay. Inherits from RunGameState.

Shark -
----------
Enemy class representing a shark. Inherits from Enemy.

Shell -
--------
Pickable shell object. Inherits from Pickables.

ShowHighScoresCommand -
------------------------
Command for showing high scores (Command Pattern). Inherits from PlayerCommand.

SimpleButton - 
---------------
Basic button class for UI. Inherits from BaseButton.

SoundState -
------------
Utility class for managing sound playback and state. Wraps sf::Sound.

StaticObject -
---------------
Abstract base class for all static (non-moving) objects.
Inherits from GameObject.

SurferPlayerState -
--------------------
Implements the surfer state for the player (wave riding, etc.).
Inherits from PlayerState.

SwirlItem - 
------------
Pickable swirl item (special effect). Inherits from Pickables.

ToggleButton -
----------------
Button that toggles between two states (on/off). Inherits from BaseButton.

UnmuteCommand -
----------------
Command for unmuting sound (Command Pattern). Inherits from PlayerCommand.

UpsideDownPlayerState -
-------------------------
Implements the upside-down state for the player. Inherits from PlayerState.

UpsideDownWalkCommand -
-------------------------
Command for walking upside down (Command Pattern). Inherits from PlayerCommand.

WalkCommand -
--------------
Command for walking (Command Pattern). Inherits from PlayerCommand.

WallLamp -
-----------
Decorative static object (wall lamp). Inherits from StaticObject.

WaveSurfCommand -
------------------
Command for surfing on waves (Command Pattern). Inherits from PlayerCommand.

WindowUtilities -
------------------
Utility functions for window management and view handling

Known Bugs:
============

Other Notes:
=============
:)