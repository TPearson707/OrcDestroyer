/**
 * Title: Orc.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Orc.h"
#include <iostream>

Orc::Orc() 
: sprite(AssetManager::getInstance().getTexture(CharacterType::ORC, Action::IDLE))
{
    hp = 1;
    attackDamage = 1;

    // set first frame to idle animation
    std::vector<sf::IntRect> idleFrames = AssetManager::getInstance().getFrames(CharacterType::ORC, Action::IDLE);
    sprite.setTextureRect(idleFrames[0]);

    orcAnimator.setFrames(idleFrames);

    sprite.setOrigin({100.f, 0.f});  // Assuming frame width is 100
    sprite.setScale({-1.f, 1.f});
    sprite.setPosition({400.f, 300.f});  // Now this position is where you expect
}

void Orc::update(sf::Time dt) {
    orcAnimator.setFrames(AssetManager::getInstance().getFrames(CharacterType::ORC, currentAction));
    orcAnimator.animate(sprite, dt);
}

void Orc::setSprite(sf::Texture& newSprite) {
    sprite.setTexture(newSprite);
}

// Using sentinel/assert - enforce minimum 0
void Orc::setHP(int hp) {
    this->hp = std::max(0, hp);
}

void Orc::setAttackDamage(int attackDamage) {
    this->attackDamage = std::max(0, attackDamage);
}

sf::Sprite& Orc::getSprite() {
    return sprite;
}

int Orc::getHP() {
    return hp;
}

int Orc::getAttackDamage() {
    return attackDamage;
}

void Orc::printOrcInfo() {
    std::cout << "HP: " << hp << std::endl;
    std::cout << "AD: " << attackDamage << std::endl;
}