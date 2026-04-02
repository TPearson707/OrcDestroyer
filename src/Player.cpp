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
: sprite(AssetManager::getInstance().getTexture(CharacterType::SOLDIER, Action::IDLE))
{
    hp = 3;
    attackDamage = 5;

    // set first frame to idle animation
    std::vector<sf::IntRect> idleFrames = AssetManager::getInstance().getFrames(CharacterType::SOLDIER, Action::IDLE);
    sprite.setTextureRect(idleFrames[0]);

    // Set the initial player frames to animate
    playerAnimator.setFrames(idleFrames);
}

void Player::handleInput() {

}

// Player::Player(int hp, int attackDamage) {
//     this->hp = hp;
//     this->attackDamage = attackDamage;
// }

void Player::update(sf::Time dt) {
    playerAnimator.setFrames(AssetManager::getInstance().getFrames(CharacterType::SOLDIER, currentAction));
    playerAnimator.animate(sprite, dt);
}

void Player::setSprite(sf::Texture& newSprite) {
    sprite.setTexture(newSprite);
}

// Using sentinel/assert - enforce minimum 0
void Player::setHP(int hp) {
    this->hp = std::max(0, hp);
}

void Player::setAttackDamage(int attackDamage) {
    this->attackDamage = std::max(0, attackDamage);
}

sf::Sprite& Player::getSprite() {
    return sprite;
}

int Player::getHP() {
    return hp;
}

int Player::getAttackDamage() {
    return attackDamage;
}

void Player::printPlayerInfo() {
    std::cout << "HP: " << hp << std::endl;
    std::cout << "AD: " << attackDamage << std::endl;
}