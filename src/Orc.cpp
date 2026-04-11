/**
 * Title: Orc.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Orc.h"
#include <iostream>
#include <cmath>

Orc::Orc() 
: Entity(AssetManager::getInstance().getTexture(CharacterType::ORC, Action::IDLE), CharacterType::ORC)
{
    // set first frame to idle animation
    setSpriteAnimation(CharacterType::ORC, Action::IDLE);

    sprite.setOrigin({100.f, 0.f});  // Assuming frame width is 100
    sprite.setScale({-1.f, 1.f});
    sprite.setPosition({400.f, 300.f});  // Now this position is where you expect

    currentState = States::IDLE;
    isDead = false;
}

void Orc::setState(States newState) {
    if (currentState == newState) return; // The gatekeeper

    currentState = newState;
    std::vector<sf::IntRect> newFrames;

    // We switch on the NEW state to set up the entry logic
    switch(currentState) {
        case States::CHASING:
            std::cout << "WE GOT TO THE CHASING ANIMATION CASE CHUD" << std::endl;
            setSpriteAnimation(CharacterType::ORC, Action::WALK);
            break;
            
        case States::ATTACK:
            setSpriteAnimation(CharacterType::ORC, Action::ATTACK);
            // Reset attack timer/cooldown here
            break;
            
        case States::DEATH:
            setSpriteAnimation(CharacterType::ORC, Action::DEATH);
            isDead = true;
            break;

        case States::IDLE:
            setSpriteAnimation(CharacterType::ORC, Action::IDLE);
            break;
    }
}

void Orc::processState(Entity& player, sf::Time dt) {
    if (isDead) return; // Exit early if the orc is dead

    sf::Vector2f orcPos = sprite.getPosition();
    sf::Vector2f playerPos = player.getSprite().getPosition();
    sf::Vector2f diff = playerPos - orcPos;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    switch(currentState) {
        case States::IDLE:
            if (distance < 400.0f) {
                setState(States::CHASING); // Use the function!
            }
            break;

        case States::CHASING:
            if (distance != 0) {
                sf::Vector2f direction = diff / distance;
                sprite.move(direction * 1.5f);
                
                // Handling flipping and origin
                if (diff.x < 0) {
                    sprite.setScale({-1.f, 1.f});
                    sprite.setOrigin({100.f, 0.f});
                } else { 
                    sprite.setScale({1.f, 1.f});
                    sprite.setOrigin({0.f, 0.f});
                }
            }

            if (distance < 20.f) {
                setState(States::ATTACK);
            }
            break;

        case States::ATTACK:
            // The attack logic is handled by the animator/timers
            // We only check if we should LEAVE the attack state
            if (distance > 30.f) { // Added a bit of 'padding' to prevent stutter
                setState(States::CHASING);
            }
            break;

        case States::DEATH:
            // Nothing to do here, update() is effectively short-circuited by isDead
            break;
    }
}

void Orc::update(Entity& entity, sf::Time dt) {
    processState(entity, dt);
    Entity::update(dt);
}