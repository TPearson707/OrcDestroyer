/**
 * Title: Player.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Player.h"
#include <iostream>
#include <vector>
#include <cmath>

Player::Player()
: Entity(AssetManager::getInstance().getTexture(CharacterType::SOLDIER, Action::IDLE), CharacterType::SOLDIER)
{
    hp = 3;
    attackDamage = 5;

    // set first frame to idle animation
    std::vector<sf::IntRect> idleFrames = AssetManager::getInstance().getFrames(CharacterType::SOLDIER, Action::IDLE);
    sprite.setTextureRect(idleFrames[0]);

    // Set the initial player frames to animate
    animator.setFrames(idleFrames);
}

void Player::moveSprite() {
    sf::Vector2f direction{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction.y -= 1.f;
        facing = Direction::UP;
    }    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction.y += 1.f;
        facing = Direction::DOWN;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { 
        direction.x -= 1.f;
        facing = Direction::LEFT;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction.x += 1.f;
        facing = Direction::RIGHT;
    }

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.f) {
        direction /= length;
        sprite.move(direction * speed);
    }
}

// Takes if the player presses Space, dash in the direction the sprite is facing;
void Player::dash() {
    sf::Vector2f direction{0.f, 0.f};
    float dashSpeed = 50.0f;

    switch(facing) {
        case Direction::UP:
            direction.y -= 1.f;
            break;
        case Direction::DOWN:
            direction.y += 1.f;
            break;
        case Direction::LEFT:
            direction.x -= 1.f;
            break;
        case Direction::RIGHT:
            direction.x += 1.f;
            break;
    }

    sprite.move(direction * dashSpeed);
}

void Player::checkDash() {
    static bool fWasPressed = false;
    bool fIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);

    if (fIsPressed && !fWasPressed) {
        dash();
    }

    fWasPressed = fIsPressed;
}

void Player::handleInput() {
    moveSprite();
    checkDash();
}

void Player::update(sf::Time dt) {
    handleInput();
    Entity::update(dt);
}