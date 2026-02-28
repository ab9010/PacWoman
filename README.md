# PacWoman 🟡

A **Pac-Man-inspired** arcade game built with **SFML** and **modern C++17**.

---

## Game Concept

PacWoman is a classic maze-chase game where the player navigates a maze, eating
pellets while avoiding four ghosts. Eating a **power pellet** temporarily turns
the ghosts blue and lets the player eat them for bonus points.

### Key Features

| Feature | Description |
|---------|-------------|
| **Tile-based maze** | 28×31 grid with walls, pellets, power pellets, and tunnels |
| **Four unique ghosts** | Blinky (red), Pinky (pink), Inky (cyan), Clyde (orange) |
| **Ghost AI modes** | Chase → pursues player, Scatter → retreats to corner, Frightened → edible |
| **Power pellets** | Temporarily make all ghosts vulnerable |
| **Tunnel wrap** | Player and ghosts wrap around the left/right edges |
| **Score & lives** | Classic scoring system with 3 starting lives |
| **Multiple levels** | Clearing all pellets advances to the next level |

---

## Code Structure

```
PacWoman/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── LICENSE                     # MIT licence
├── assets/                     # Game assets (fonts, textures, sounds)
├── include/PacWoman/           # Public header files
│   ├── Constants.hpp           # Compile-time game settings
│   ├── Entity.hpp              # Abstract base class for moving objects
│   ├── Game.hpp                # Main game loop & state machine
│   ├── Ghost.hpp               # Ghost entity with AI behaviour
│   ├── HUD.hpp                 # Score / lives / messages overlay
│   ├── Maze.hpp                # Tile-based level layout
│   ├── PacWoman.hpp            # Player-controlled character
│   └── Pellet.hpp              # Collectible pellet item
└── src/                        # Implementation files
    ├── main.cpp                # Entry point
    ├── Game.cpp                # Game loop, events, collision logic
    ├── Ghost.cpp               # Ghost movement & AI
    ├── HUD.cpp                 # HUD rendering
    ├── Maze.cpp                # Maze loading & rendering
    ├── PacWoman.cpp            # Player movement & animation
    └── Pellet.cpp              # Pellet rendering
```

### Architecture Overview

```
┌──────────────────────────────────────────────────┐
│                    Game (owns everything)         │
│  ┌──────┐  ┌──────────┐  ┌───────┐  ┌─────┐    │
│  │ Maze │  │ PacWoman │  │ Ghost │×4│ HUD │    │
│  │(tiles)│  │ (player) │  │ (AI)  │  │(UI) │    │
│  └──┬───┘  └────┬─────┘  └───┬───┘  └──┬──┘    │
│     │           │             │          │        │
│     └───────────┴─────────────┴──────────┘        │
│         All share the SFML RenderWindow           │
└──────────────────────────────────────────────────┘
```

### Design Patterns & Concepts Used

1. **Entity base class** — `Entity` provides position, direction, speed, and
   bounding-box collision shared by `PacWomanEntity` and `Ghost`.
2. **Game state machine** — `Game::State` enum (`Ready → Playing → GameOver`)
   cleanly separates logic for each phase.
3. **Tile-based collision** — The `Maze` stores a character grid; wall checks
   convert pixel positions to tile coordinates for O(1) lookups.
4. **Ghost AI personalities** — Each ghost has a *scatter target* corner and
   a *chase target* derived from the player's position, producing emergent
   behaviour with minimal code.
5. **Buffered input** — The player can press a direction key before reaching
   a junction; the turn is applied as soon as it becomes valid.
6. **Fixed-timestep-ready** — `dt` is passed through update so the game can
   be extended to a fixed-timestep loop easily.

---

## Building

### Prerequisites

* **C++17** compiler (GCC 9+, Clang 10+, MSVC 2019+)
* **CMake** ≥ 3.16
* **SFML** ≥ 2.5 (install via your system package manager)

```bash
# Ubuntu / Debian
sudo apt install libsfml-dev cmake g++

# macOS (Homebrew)
brew install sfml cmake

# Windows (vcpkg)
vcpkg install sfml
```

### Build & Run

```bash
mkdir build && cd build
cmake ..
cmake --build .
./PacWoman
```

---

## Controls

| Key | Action |
|-----|--------|
| **↑ / W** | Move up |
| **↓ / S** | Move down |
| **← / A** | Move left |
| **→ / D** | Move right |
| **Esc** | Quit |
| *Any key* | Restart (on Game Over screen) |

---

## Extending the Game

Ideas for further development:

* **Sprite-based rendering** — Replace shape primitives with sprite sheets for
  PacWoman, ghosts, and the maze.
* **Sound effects** — Add SFML audio for waka-waka, ghost eat, death, and
  level-complete jingles.
* **Fruit bonus items** — Spawn fruit at the centre of the maze for bonus
  points.
* **Advanced ghost AI** — Implement Pinky's ambush (4 tiles ahead), Inky's
  vector-based targeting, and Clyde's distance-based toggle.
* **Animated sprites** — Use sprite sheets with frame animation for smoother
  character visuals.
* **High-score persistence** — Save high scores to a local file.
* **Level editor** — Load maze layouts from external files to support custom
  levels.

---

## License

MIT — see [LICENSE](LICENSE).
