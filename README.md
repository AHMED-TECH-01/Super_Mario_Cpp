# 🎮 Retro Wonder Engine

An original 2D platformer game built with **C++17 and SFML 3.1**, featuring custom pixel-art graphics, animated characters, tile-based environments, enemy interactions, collectibles, and Data Structures and Algorithms (DSA) integration.

The project aims to demonstrate how core DSA concepts, object-oriented programming, game physics, collision detection, and graphics programming can come together in an interactive desktop game.

> Inspired by the creativity and gameplay depth of modern platformers, Retro Wonder Engine is an original project with its own characters, environments, mechanics, and assets.

---

## ✨ Features

### 🎨 Graphics and Rendering
- Original pixel-art character sprites.
- Animated character sprite sheet.
- Idle, running, jumping, and landing animations.
- Custom environment tiles and background.
- Scrolling camera system.
- Tile-based level rendering.
- Animated enemy sprites.

### 🕹️ Gameplay
- Left and right character movement.
- Acceleration and friction-based movement.
- Jumping and gravity.
- Tile collision detection.
- Collectible coins.
- Score tracking.
- Pause and resume functionality.

### 🧠 Data Structures and Algorithms

The project is designed to integrate practical DSA concepts into gameplay and game systems.

| Data Structure / Algorithm | Planned Application |
|---|---|
| 2D Arrays | Tile-based level maps |
| Dynamic Arrays | Game entities and collectibles |
| Linked Lists | Temporary effects and animations |
| Stacks | Undo and reversible actions |
| Circular Queues | Game event management |
| Priority Queues | Event scheduling |
| Graphs | World and level connectivity |
| BFS | Level navigation |
| DFS | World exploration |
| Hash Tables | Collectible and entity lookup |
| Merge Sort | Leaderboard sorting |
| Binary Search | Player and score lookup |
| AABB Collision | Collision detection |

---

## 🛠️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core programming language |
| SFML 3.1 | Graphics, window, input and audio |
| CMake | Build configuration |
| Ninja | Build system |
| GCC | C++ compiler |
| MSYS2 UCRT64 | Windows development environment |
| Visual Studio Code | Code editor |

---

## 📁 Project Structure

```text
RetroWonderEngine/
│
├── CMakeLists.txt
├── README.md
│
├── assets/
│   ├── audio/
│   │   ├── jump.wav
│   │   ├── collect.wav
│   │   ├── stomp.wav
│   │   └── greenwood_theme.wav
│   │
│   ├── backgrounds/
│   │   └── greenwood.png
│   │
│   ├── sprites/
│   │   ├── hero_sheet.png
│   │   └── enemies_sheet.png
│   │
│   └── tiles/
│       └── tiles.png
│
├── include/
│   ├── Player.hpp
│   └── GameWorld.hpp
│
├── src/
│   ├── main.cpp
│   ├── Player.cpp
│   └── GameWorld.cpp
│
├── levels/
│
└── docs/
    └── ROADMAP.md
```

---

## ⚙️ Installation and Setup

### 1. Install prerequisites

Make sure the following tools are installed:

- Visual Studio Code
- MSYS2 UCRT64
- GCC compiler
- CMake
- Ninja
- SFML 3.1

Install SFML through the MSYS2 UCRT64 terminal:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### 2. Verify installation

Run these commands in PowerShell:

```powershell
g++ --version
cmake --version
ninja --version
```

### 3. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/RetroWonderEngine.git
```

Navigate into the project:

```bash
cd RetroWonderEngine
```

### 4. Configure the project

```powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64
```

### 5. Compile

```powershell
cmake --build build
```

### 6. Run the game

```powershell
.\build\RetroWonderEngine.exe
```

---

## 🎮 Controls

| Key | Action |
|---|---|
| A | Move left |
| D | Move right |
| Left Arrow | Move left |
| Right Arrow | Move right |
| Space | Jump |
| W / Up Arrow | Jump |
| ESC | Pause / Resume |

---

## 🗺️ Planned Game Worlds

The long-term goal is to develop multiple unique worlds, each with its own visual identity, challenges, enemies, and gameplay mechanics.

| World | Environment | Planned Theme |
|---|---|---|
| 01 | Greenwood Kingdom | Grasslands and forests |
| 02 | Mushroom Valley | Magical mushroom landscapes |
| 03 | Crystal Caverns | Underground crystal caves |
| 04 | Underground Ruins | Ancient structures |
| 05 | Frozen Peaks | Ice and snow |
| 06 | Lava Fortress | Fire and lava |
| 07 | Sky Islands | Floating islands |
| 08 | Wonder Dimension | Changing environments |

---

## 🚀 Planned Gameplay Systems

### Character Transformations
- Fire Form — projectile-based attacks.
- Bubble Form — bubble-based enemy interactions.
- Drill Form — underground movement.
- Heavy Form — powerful attacks and obstacle destruction.

### Wonder Events
- Gravity changes.
- Moving platforms.
- Floating obstacles.
- Enemy transformations.
- Environment modifications.
- Timed challenges.

### Additional Systems
- Multiple playable characters.
- Enemy AI and boss battles.
- Power-ups and collectibles.
- World map and level selection.
- Level unlocking and progression.
- Save and load functionality.
- Leaderboard.
- Audio and background music.
- DSA visualization dashboard.

---

## 🎯 Academic Objectives

This project is developed as a semester DSA project with the following objectives:

1. Apply data structures to practical game development.
2. Demonstrate object-oriented programming principles.
3. Implement algorithms for navigation, sorting, searching, and collision detection.
4. Understand game physics and real-time simulation.
5. Build a modular C++ desktop application.
6. Visualize the behavior and complexity of selected DSA algorithms.

---

## 📌 Development Status

**Current milestone:** Rendering and Character Foundation

| Component | Status |
|---|---|
| C++ / SFML project setup | Implemented |
| Custom pixel-art assets | Implemented |
| Character sprite animation | Implemented |
| Basic movement and jumping | Implemented |
| Camera following | Implemented |
| Tile-based level | Implemented |
| Collectibles and score | Implemented |
| Pause system | Implemented |
| Advanced enemy AI | Planned |
| Multiple playable levels | Planned |
| Character transformations | Planned |
| Wonder events | Planned |
| Boss battles | Planned |
| DSA dashboard | Planned |
| Save / Load | Planned |

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome.

1. Fork the repository.
2. Create a feature branch.
3. Implement your changes.
4. Test your changes.
5. Submit a pull request.

---

## 📜 License

This project is intended for educational and academic purposes. Original project code and assets are developed for Retro Wonder Engine. Third-party libraries retain their respective licenses.

---

**Built with C++, SFML, creativity, and Data Structures & Algorithms.**
