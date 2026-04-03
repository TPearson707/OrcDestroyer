/**
 * Title: Orc.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Orc.h"
#include <iostream>

Orc::Orc() 
: Entity(AssetManager::getInstance().getTexture(CharacterType::ORC, Action::IDLE), CharacterType::ORC)
{
    // set first frame to idle animation
    std::vector<sf::IntRect> idleFrames = AssetManager::getInstance().getFrames(CharacterType::ORC, Action::IDLE);
    sprite.setTextureRect(idleFrames[0]);

    animator.setFrames(idleFrames);

    sprite.setOrigin({100.f, 0.f});  // Assuming frame width is 100
    sprite.setScale({-1.f, 1.f});
    sprite.setPosition({400.f, 300.f});  // Now this position is where you expect
}

void Orc::update(sf::Time dt) {
    // State machine function here
    Entity::update(dt);
}