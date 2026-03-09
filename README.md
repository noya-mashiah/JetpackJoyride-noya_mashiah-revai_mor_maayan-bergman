# Jetpack Joyride - OOP Game Project

**Developed by:** Revai Mor, Noya Mashiah, and Maayan Bergman

## 📖 Overview

Jetpack Joyride is an exhilarating action-runner game built entirely in 
**C++** using the **SFML** (Simple and Fast Multimedia Library). Players 
control a character equipped with a jetpack, navigating through dynamically 
generated environments, collecting coins, avoiding hazardous obstacles, and 
striving to reach the greatest distance possible.

The game features an endless mode where players compete for the highest 
score by surviving as long as possible. A key focus during 
development was ensuring a smooth, responsive user experience, utilizing 
optimized resource loading for textures, fonts, music, and sound effects 
during the game's initialization phase.

## 🚀 Key Features

* **Intuitive Player Control:** Navigate the character using the keyboard. 
  Press and hold the `Space` key to control the jetpack's thrust and fly 
  upwards; release to descend.
* **Dynamic Collision Detection:** Advanced handling of interactions between 
  the player, moving obstacles, and collectible items.
* **Diverse Game Objects & Hazards:**
  * **Enemies:** Avoid incoming **Missiles** (with visual/audio alarms), 
    sonic waves from **Bats**, and electrifying **Lasers**.
  * **Special Sea Mode:** Survive encounters with **Piranhas**, **Sharks**, 
    and **Crabs** in a unique surfing environment.
* **Exciting Power-Ups & State Changes:** Collecting a Power-Up Box 
  transforms the player into unique modes for 60 seconds:
  * 🤖 **Robot Mode:** Grants an optional gas tank for 10s of 
    immunity.
  * 🐦 **Bird Mode:** Doubles the value of all collected coins.
  * 🦖 **Dinosaur Mode:** Jump-based movement with a rapid-flight 
    "steak".
  * 🙃 **Upside-Down Mode:** Defy gravity and run on the ceiling.
  * 🌊 **Surf Mode:** Transforms the environment into a sea state.
* **Scoring System & UI:** Real-time distance and coin tracking. 
  The interface includes Start, Pause, High-Score leaderboard, and Help 
  menus.
* **Sound & Music:** Integrated sounds for jetpack thrust, collision 
  effects, and a togglable background music system.

## 💻 Technical Architecture & Design

This project was developed adhering to strict Object-Oriented Programming 
(OOP) principles and robust design patterns:

* **Design Patterns Used:**
  * **State Pattern:** Manages game flows (`MainMenuState`, `RunGameState`) 
    and dynamic player behaviors (`BirdPlayerState`, 
    `DinosaurPlayerState`).
  * **Command Pattern:** Decouples user input from character actions (e.g., 
    `JumpCommand`, `DieCommand`, `WaveSurfCommand`).
  * **Factory Pattern:** Uses `GameObjectFactory` with an 
    `std::unordered_map` for O(1) creation of game objects by name without 
    modifying core logic.
* **Smart Collision Handling:** Utilizes a Double-Dispatch approach 
  with `std::map` to efficiently route and process collisions between 
  different object types, avoiding long `if-else` chains.
* **Data Structures:** * `std::list`: Used to store active game objects for O(1) 
    insertion/removal.
  * `std::unordered_map`: Used in the `ResourcesManager` to prevent 
    duplicate loading of assets and allow fast retrieval.

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
