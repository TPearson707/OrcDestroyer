# Orc Destroyer

A simple 2D dungeon crawler where the player fights waves of orcs. Built to explore the inner workings of a game engine using SFML and C++.

---

## main.cpp — Intentional Spaghetti

`main.cpp` was written on day one and is frozen. It will not be modified.

This was a deliberate choice by me. Before I began designing a game with proper architecture, I first needed to understand what I was working with. I had no experience with SFML, and I hadn't written a program in C++ in about a year, so I started with a brain dump in one file. The file contains global maps, free functions, hardcoded string keys, magic numbers, the works; I did this to practice the basics: loading textures, slicing sprite sheets, building state machines, and properly structuring a game loop. Through this I actually found that writing messy code that worked was the fastest way to learn what I was building. The result was a game that I wanted to continue working on. Every refactor and every change since then has been a direct response to sometihng that hurt from that original file. 

---

## Day One Refactor — Architecture Concepts Learned

### `AssetManager` — Resource Manager as a Singleton

The first real architectural component. Replaces the two global `unordered_map<string, sf::Texture>` maps and the free `loadTexture` / `getFrames` functions scattered across `main.cpp`.

**What I built:**

- A `struct AssetKey` with `CharacterType` and `Action` enum fields as a composite map key, replacing magic strings like `"IDLE"` and `"WALK"`
- `operator<` implemented on the struct to satisfy `std::map`'s ordering requirement — a lexicographic comparison that sorts by character first, then action
- A `std::map<AssetKey, sf::Texture>` and `std::map<AssetKey, std::vector<sf::IntRect>>` as the backing caches
- `populateFramesMap()` driven by iterating the already-loaded texture map — so frames can never exist without a corresponding texture, and adding a new character to `populateTexturesMap()` automatically generates its frames for free
- The Meyers singleton pattern: a `static AssetManager instance` inside `getInstance()`, which is a lazy, thread-safe solution in C++11+, and automatically destroyed at program exit
- Deleted copy constructor and assignment operator to prevent duplication

**Why singleton here:** An asset manager owns a single global cache. Multiple instances would mean multiple copies of the same textures in memory, and every system in the game (Player, Orc, UI) needs to pull from the same source. The singleton enforces this at the type level.

**Where industry has a leg up:** Production engines use asset handles (lightweight IDs) instead of direct references, reference counting for unloading, async background loading, and data-driven manifests instead of hardcoded paths. The hardcoded `frameWidth = 100` is the most obvious gap — a real solution maps frame dimensions per asset key.

---

### `Player` and `Orc` — Entities Consuming the Asset Manager

- Initializes `sf::Sprite` from `AssetManager::getInstance().getTexture()` in the member initializer list
- Sets `textureRect` to the first idle frame immediately on construction
- Owns animation state: `currentAction`, `currentFrame`, `animTimer`, `frameInterval`
- `update(float deltaTime)` advances the frame on a timer and calls back into `AssetManager::getFrames()` — the player doesn't own or copy frame data, it just reads from the cache

**Duplication is obvious**: Both Player and Orc have identical animation logic copy-pasted between them. This is the next thing that will be pulled out.

**Next step — `Animator` class:**

- Will own all animation states (`currentAction`, `currentFrame`, `animationTimer`, `frameInterval`)
- Entities will delegate animation responsibly: `animator.animate(sprite, deltaTime)` inside `Player::update()` or `Orc::update()`
- Later, Orc will gain a behavior state machine (idle, patrol, chase, attack, die) while Player remains input-driven. However, both will share the same animation infrastructure. 

---

### `Game` — The Loop

Owns the window, the delta time clock, the player, and the orc. The loop is: restart clock → `processEvents()` → `update(dt)` → `render()`. Delta time is passed down so all update logic is frame-rate independent.

---

## Concepts Learned

- **Singleton pattern** and when it's appropriate vs. when it becomes a liability
- **Composite struct keys** with custom `operator<` for `std::map`
- **Enum classes** as type-safe identifiers instead of magic strings
- **Meyers singleton** as the modern C++ approach to lazy, safe static initialization
- **Separation of loading, caching, and serving** as distinct responsibilities
- **Member initializer lists** for constructing objects that can't be default-initialized (`sf::Sprite` requires a texture)
- **Delta time** as the foundation of frame-rate independent game logic
- The general game loop structure: **Input → Update State → Render**

---

## References

**SFML Documentation**  
https://www.sfml-dev.org/

**C++ Reference**  
https://en.cppreference.com/w/

**SFML Game Development**  
Jan Haller, Henrik Vogelius Hansson, and Artur Moreira  
Packt Publishing, 2013