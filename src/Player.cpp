/**
 * Title: Player.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Player.h"
#include <iostream>
#include <vector>

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

void Player::handleInput() {

}

void Player::update(sf::Time dt) {
    handleInput();
    Entity::update(dt);
}