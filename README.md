# Jetpack Joyride - OOP Game Project

[cite_start]**Developed by:** Revai Mor, Noya Mashiah, and Maayan Bergman [cite: 1]

## 📖 Overview

Jetpack Joyride is an exhilarating action-runner game built entirely in 
**C++** using the **SFML** (Simple and Fast Multimedia Library). Players 
control a character equipped with a jetpack, navigating through dynamically 
generated environments, collecting coins, avoiding hazardous obstacles, and 
[cite_start]striving to reach the greatest distance possible[cite: 2, 4, 5].

The game features an endless mode where players compete for the highest 
[cite_start]score by surviving as long as possible[cite: 2]. A key focus during 
development was ensuring a smooth, responsive user experience, utilizing 
optimized resource loading for textures, fonts, music, and sound effects 
during the game's initialization phase.

## 🚀 Key Features

* **Intuitive Player Control:** Navigate the character using the keyboard. 
  Press and hold the `Space` key to control the jetpack's thrust and fly 
  [cite_start]upwards; release to descend[cite: 3].
* **Dynamic Collision Detection:** Advanced handling of interactions between 
  [cite_start]the player, moving obstacles, and collectible items[cite: 4, 5].
* **Diverse Game Objects & Hazards:**
  * **Enemies:** Avoid incoming **Missiles** (with visual/audio alarms), 
    [cite_start]sonic waves from **Bats**, and electrifying **Lasers**[cite: 6, 7, 8, 13].
  * **Special Sea Mode:** Survive encounters with **Piranhas**, **Sharks**, 
    [cite_start]and **Crabs** in a unique surfing environment[cite: 10, 11, 12, 20].
* **Exciting Power-Ups & State Changes:** Collecting a Power-Up Box 
  [cite_start]transforms the player into unique modes for 60 seconds[cite: 14, 23]:
  * 🤖 **Robot Mode:** Grants an optional gas tank for 10s of 
    [cite_start]immunity[cite: 14].
  * [cite_start]🐦 **Bird Mode:** Doubles the value of all collected coins[cite: 14, 15].
  * 🦖 **Dinosaur Mode:** Jump-based movement with a rapid-flight 
    [cite_start]"steak"[cite: 16, 17].
  * [cite_start]🙃 **Upside-Down Mode:** Defy gravity and run on the ceiling[cite: 18].
  * [cite_start]🌊 **Surf Mode:** Transforms the environment into a sea state[cite: 20].
* [cite_start]**Scoring System & UI:** Real-time distance and coin tracking[cite: 29]. 
  The interface includes Start, Pause, High-Score leaderboard, and Help 
  [cite_start]menus[cite: 29, 30, 32].
* **Sound & Music:** Integrated sounds for jetpack thrust, collision 
  [cite_start]effects, and a togglable background music system[cite: 31, 32].

## 💻 Technical Architecture & Design

This project was developed adhering to strict Object-Oriented Programming 
(OOP) principles and robust design patterns:

* **Design Patterns Used:**
  * **State Pattern:** Manages game flows (`MainMenuState`, `RunGameState`) 
    and dynamic player behaviors (`BirdPlayerState`, 
    [cite_start]`DinosaurPlayerState`)[cite: 38, 50, 54, 73, 74].
  * **Command Pattern:** Decouples user input from character actions (e.g., 
    [cite_start]`JumpCommand`, `DieCommand`, `WaveSurfCommand`)[cite: 45, 48, 70, 105].
  * **Factory Pattern:** Uses `GameObjectFactory` with an 
    `std::unordered_map` for O(1) creation of game objects by name without 
    [cite_start]modifying core logic[cite: 55, 56, 57].
* **Smart Collision Handling:** Utilizes a Double-Dispatch approach 
  with `std::map` to efficiently route and process collisions between 
  [cite_start]different object types, avoiding long `if-else` chains[cite: 42, 43, 44].
* **Data Structures:** * `std::list`: Used to store active game objects for O(1) 
    [cite_start]insertion/removal[cite: 59, 60].
  * `std::unordered_map`: Used in the `ResourcesManager` to prevent 
    [cite_start]duplicate loading of assets and allow fast retrieval[cite: 91, 92].


## 📊 UML Class Diagrams

Visual documentation of the project's class hierarchy and design patterns:

### Complete Class Diagram
![Complete Class Diagram](resources/Images/inharitance_trees_uml/entireClassDiagram.png)

### Key Inheritance Trees

<details>
<summary>Click to view all inheritance diagrams</summary>

#### GameObject Hierarchy
![GameObject Tree](resources/Images/inharitance_trees_uml/GameObjectTree.png)

#### Player State Pattern
![Player State](resources/Images/inharitance_trees_uml/PlayerState.png)

#### Game State Pattern
![Game State](resources/Images/inharitance_trees_uml/GameState.png)

#### Moving Objects
![Moving Object Tree](resources/Images/inharitance_trees_uml/MovingObjectTree.png)

#### Obstacles
![Obstacles Tree](resources/Images/inharitance_trees_uml/ObstaclesTree.png)

#### Pickables
![Pickables Tree](resources/Images/inharitance_trees_uml/PickablesTree.png)

#### Button Hierarchy
![Button](resources/Images/inharitance_trees_uml/Button.png)

#### Command Patterns
![Button Command](resources/Images/inharitance_trees_uml/ButtonCommand.png)
![Player Command](resources/Images/inharitance_trees_uml/PlayerCommand.png)

#### Managers
![Managers](resources/Images/inharitance_trees_uml/Managers.png)

#### Expanded View
![Expanded Class Diagram](resources/Images/inharitance_trees_uml/ExpandedClassDiagram.png)

</details>

## 🛠️ Installation & Build Instructions

1. **Install SFML:** Ensure the SFML library is installed on your system.
2. **Clone the Repository:**
```bash
git clone [https://github.com/yourusername/Jetpack-Joyride-OOP.git](https://github.com/yourusername/Jetpack-Joyride-OOP.git)
cd Jetpack-Joyride-OOP

```

3. **Build Using CMake:**

```bash
mkdir build
cd build
cmake ..
make

```

*(For Windows users, open the generated solution file in Visual
Studio and build).*

4. **Run the Game:** Launch the game executable from your IDE or terminal.

## 🎓 Conclusion & Acknowledgements

Jetpack Joyride was a challenging yet rewarding project. We dedicated
ourselves to crafting engaging gameplay, refining mechanics, and
integrating immersive elements like sound and visuals. This journey pushed
our skills in C++ game development and teamwork, resulting in a game we're
truly proud to share.

Thank you for exploring our game—we hope you enjoy playing it as much
as we enjoyed creating it!

**Credits:**

* During the development of the project, we faced a challenge with
identifying collisions accurately. We ended up finding a GitHub
repository that helped us solve this efficiently. We also received
approval via email from the teaching assistant to use this
file.
GitHub link: [SFML Simple Collision Detection Wiki](https://github.com/SFML/SFML/wiki/Source%3A-Simple-Collision-Detection-for-SFML-2)



## 📄 License

This project was developed as an academic project. All rights are
reserved to the Hadassah Academic College students: Noya
Mashiah, Revai Mor, and Maayan Bergman.