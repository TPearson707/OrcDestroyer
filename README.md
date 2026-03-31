# Orc Destroyer

A 2D dungeon crawler where you fight waves of orcs. Built to explore game engine architecture using SFML and C++.

---

## Build and Run

**Prerequisites:**
- C++17 or later
- SFML 3.0.2
- CMake 3.15+

**Build instructions:**
```bash
git clone https://github.com/yourusername/orc-destroyer.git
cd orc-destroyer
mkdir build && cd build
cmake ..
make
./OrcDestroyer
```

---

## Controls

- **WASD** — Move
- **Space** — Attack
- **ESC** — Quit

---

## Features

- Frame-independent movement using delta time
- Sprite animation system
- Enemy AI (basic orc behavior)
- Asset management with caching

---

## Screenshots

![Gameplay](screenshot.png)

---

## Development Notes

See [DEVELOPMENT.md](DEVELOPMENT.md) for architecture decisions, refactoring history, and learning notes.

---

## References

**SFML Documentation**  
https://www.sfml-dev.org/

**C++ Reference**  
https://en.cppreference.com/

**SFML Game Development**  
Jan Haller, Henrik Vogelius Hansson, and Artur Moreira  
Packt Publishing, 2013