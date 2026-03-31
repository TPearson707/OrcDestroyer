/**
 * Title: main.cpp
 * Author: Thomas Pearson
 * Date Created: 03/24/2026
 * Date of Last Update: 03/24/2026
 * 
 * Purpose: Day one brain dump. This file was written to learn SFML basics
 * and C++ game loop structure without worrying about architecture. It contains
 * global state, magic strings, hardcoded values, and tight coupling between
 * systems, all choices were intential to prioritize learning over clean code.
 * 
 * This file is frozen and will not be modified. Every refactor since has been
 * a direct response to something that hurt in this original implementation.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


enum class OrcState { IDLE, WALKING, ATTACKING, DEAD };
OrcState orcState = OrcState::IDLE;
sf::Clock orcClock;
sf::Clock spawnClock;
float spawnCooldown = 2.f;

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

void setWindowProperties(sf::RenderWindow& window);
void startGame();
sf::Texture loadTexture(const std::string& filePath);
std::vector<sf::IntRect> getFrames(sf::Texture& texture, int frameWidth, int frameHeight);
void drawSprite(sf::RenderWindow& window, sf::Sprite& sprite);
void spawnOrc(sf::RenderWindow& window, sf::Sprite& sprite);
void checkPlayerMovement(const std::optional<sf::Event>& event, sf::Sprite& sprite);
void setSpriteToWalk(sf::Sprite& sprite);
void setSpriteToAttack(sf::Sprite& sprite);
void setSpriteToIdle(sf::Sprite& sprite);

std::unordered_map<std::string, sf::Texture> soldierSpritesheets;
std::unordered_map<std::string, sf::Texture> orcSpritesheets;

void populateSoldierSpritesMap(std::unordered_map<std::string, sf::Texture>& soldierSpritesheets);
void populateOrcSpritesMap(std::unordered_map<std::string, sf::Texture>& orcSpritesheets);

void updateOrc(sf::Sprite& orcSprite, sf::Sprite& playerSprite, OrcState& orcState);
void renderFrame(sf::RenderWindow& window, sf::Sprite& playerSprite, sf::Sprite& orcSprite);

int main() {
    srand(time(0));
    populateSoldierSpritesMap(soldierSpritesheets);
    populateOrcSpritesMap(orcSpritesheets);
    startGame();
}

void setWindowProperties(sf::RenderWindow& window) {
    window.setPosition({10, 50});
    window.setTitle("Hikikomori Resurrected");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void startGame() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hikikomori Resurrected");
    setWindowProperties(window);

    // Load texture ONCE outside the loop
    // sf::Texture spritesheet = loadTexture("assets/Soldier/Soldier/Soldier-Attack01.png");

    sf::Texture spritesheet = soldierSpritesheets.at("IDLE");
    std::vector<sf::IntRect> frames = getFrames(spritesheet, 100, 100);
    sf::Sprite sprite(spritesheet);

    sf::Texture orcSpritesheet = orcSpritesheets.at("IDLE");
    std::vector<sf::IntRect> orcFrames = getFrames(orcSpritesheet, 100, 100);
    sf::Sprite orcSprite(orcSpritesheet);

    sprite.setScale({2.f, 2.f});
    orcSprite.setScale({2.f, 2.f});

    int currentFrame = 0;
    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            checkPlayerMovement(event, sprite);
        }

        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTextureRect(frames[currentFrame]);
            orcSprite.setTextureRect(frames[currentFrame]);
            clock.restart();
        }

        
        if (spawnClock.getElapsedTime().asSeconds() > spawnCooldown) {
            spawnOrc(window, orcSprite);
            spawnClock.restart();
        }
        
        updateOrc(orcSprite, sprite, orcState);
        renderFrame(window, sprite, orcSprite);

    }
}

sf::Texture loadTexture(const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return texture;
}

std::vector<sf::IntRect> getFrames(sf::Texture& texture, int frameWidth, int frameHeight) {
    std::vector<sf::IntRect> frames;
    sf::Vector2u textureSize = texture.getSize();
    int cols = textureSize.x / frameWidth;
    int rows = textureSize.y / frameHeight;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            frames.push_back(sf::IntRect(
                {col * frameWidth, row * frameHeight},
                {frameWidth, frameHeight}
            ));
        }
    }
    return frames;
}

void drawSprite(sf::RenderWindow& window, sf::Sprite& sprite) {
    // window.clear();

    // float x = window.getSize().x / 2;
    // float y = window.getSize().y / 2;

    // sf::Vector2f position = {x, y};

    // sprite.setPosition(position);

    window.draw(sprite);
    window.display();
}

void spawnOrc(sf::RenderWindow& window, sf::Sprite& sprite) {
    float spawnX, spawnY;
    int wall = rand() % 4 + 1;

    if (wall == 1) {          // spawn left wall
        spawnX = 0.f;
        spawnY = rand() % (int)window.getSize().y;
    } else if (wall == 2) {   // spawn top wall
        spawnX = rand() % (int)window.getSize().x;
        spawnY = 0.f;
    } else if (wall == 3) {   // spawn right wall
        spawnX = window.getSize().x;
        spawnY = rand() % (int)window.getSize().y;
    } else if (wall == 4) {   // spawn bottom wall
        spawnX = rand() % (int)window.getSize().x;
        spawnY = window.getSize().y;
    }

    sprite.setPosition({spawnX, spawnY});
}

// checkPlayerMovement now just receives the event, no polling
void checkPlayerMovement(const std::optional<sf::Event>& event, sf::Sprite& sprite) {
    if (event->is<sf::Event::KeyPressed>()) {
        auto& key = event->getIf<sf::Event::KeyPressed>()->code;

        if (key == sf::Keyboard::Key::Left) {
            setSpriteToWalk(sprite);
            sprite.setScale({-2.f, 2.f}); // Flip sprite
            sprite.setOrigin({100.0f, 0.f}); // offset so it doesn't flip off screen
            sprite.move({-5.f, 0.f});
        } else if (key == sf::Keyboard::Key::Right) {
            setSpriteToWalk(sprite);
            sprite.setScale({2.f, 2.f});
            sprite.setOrigin({0.f, 0.f});
            sprite.move({5.f, 0.f});
        } else if (key == sf::Keyboard::Key::Up) {
            setSpriteToWalk(sprite);
            sprite.move({0.f, -5.f});
        } else if (key == sf::Keyboard::Key::Down) {
            // future implementation: crouch
            setSpriteToWalk(sprite);
            sprite.move({0.f, 5.f});
        } else if (key == sf::Keyboard::Key::Z) {
            setSpriteToAttack(sprite);
        } else {
            setSpriteToIdle(sprite);
        }
    }

    if (event->is<sf::Event::MouseButtonPressed>()) {
        // future implementation: mouse click action
    }
}

void setSpriteToWalk(sf::Sprite& sprite) {
    sprite.setTexture(soldierSpritesheets.at("WALK"));
}

void setSpriteToAttack(sf::Sprite& sprite) {

    sprite.setTexture(soldierSpritesheets.at("ATTACK"));

}

void setSpriteToIdle(sf::Sprite& sprite) {
    sprite.setTexture(soldierSpritesheets.at("IDLE"));
}

void populateSoldierSpritesMap(std::unordered_map<std::string, sf::Texture>& soldierSpritesheets) {
    soldierSpritesheets["ATTACK"] = loadTexture("assets/Soldier/Soldier/Soldier-Attack01.png");
    soldierSpritesheets["WALK"] = loadTexture("assets/Soldier/Soldier/Soldier-Walk.png");
    soldierSpritesheets["IDLE"] = loadTexture("assets/Soldier/Soldier/Soldier-Idle.png");
}

void populateOrcSpritesMap(std::unordered_map<std::string, sf::Texture>& orcSpritesheets) {

    std::string urlPrefix = "assets/Orc/Orc/";

    orcSpritesheets["ATTACK"] = loadTexture(urlPrefix + "Orc-Attack01.png");
    orcSpritesheets["WALK"] = loadTexture(urlPrefix + "Orc-Walk.png");
    orcSpritesheets["IDLE"] = loadTexture(urlPrefix + "Orc-Idle.png");
}

// Orc state machine implementation
void updateOrc(sf::Sprite& orcSprite, sf::Sprite& playerSprite, OrcState& orcState) {
    sf::Vector2f orcPos = orcSprite.getPosition();
    sf::Vector2f playerPos = playerSprite.getPosition();

    // Get distance between orc and player
    sf::Vector2f diff = playerPos - orcPos;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    switch (orcState) {
        case OrcState::IDLE:
            orcSprite.setTexture(orcSpritesheets.at("IDLE"));
            if (distance < 400.f)
                orcState = OrcState::WALKING;
            break;

        case OrcState::WALKING:
            orcSprite.setTexture(orcSpritesheets.at("WALK"));
            // Normalize and move toward player
            if (distance != 0) {
                sf::Vector2f direction = diff / distance;
                orcSprite.move(direction * 1.5f);
                // Flip orc to face player
                if (diff.x < 0) orcSprite.setScale({-2.f, 2.f});
                else orcSprite.setScale({2.f, 2.f});
            }
            if (distance < 50.f)
                orcState = OrcState::ATTACKING;
            break;

        case OrcState::ATTACKING:
            orcSprite.setTexture(orcSpritesheets.at("ATTACK"));
            if (distance > 50.f)
                orcState = OrcState::WALKING;
            // future implementation: deal damage to player
            break;

        case OrcState::DEAD:
            // future implementation: death animation then remove
            break;
    }    
}

void renderFrame(sf::RenderWindow& window, sf::Sprite& playerSprite, sf::Sprite& orcSprite) {
    window.clear();
    window.draw(playerSprite);
    window.draw(orcSprite);
    window.display();
}