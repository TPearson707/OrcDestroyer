#include "Entity.h"
#include <iostream>

Entity::Entity(sf::Texture& texture, CharacterType character) 
: sprite(texture)
{
    this->character = character;
    hp = 1;
    attackDamage = 1;
    speed = 3;
}

void Entity::update(sf::Time dt) {
    animator.setFrames(AssetManager::getInstance().getFrames(character, currentAction));
    animator.animate(sprite, dt);
}

void Entity::setSprite(sf::Texture& newSprite) {
    sprite.setTexture(newSprite);
}

void Entity::setSpriteAnimation(CharacterType character, Action action) {
    setSprite(AssetManager::getInstance().getTexture(character, action));
    std::vector<sf::IntRect> characterFrames = AssetManager::getInstance().getFrames(character, action);
    sprite.setTextureRect(characterFrames[0]);
    animator.setFrames(characterFrames);
}

// Using sentinel/assert - enforce minimum 0
void Entity::setHP(int hp) {
    this->hp = std::max(0, hp);
}

void Entity::setAttackDamage(int attackDamage) {
    this->attackDamage = std::max(0, attackDamage);
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}

int Entity::getHP() {
    return hp;
}

int Entity::getAttackDamage() {
    return attackDamage;
}

float Entity::getSpeed() {
    return speed;
}

void Entity::printEntityInfo() {
    std::cout << "HP: " << hp << std::endl;
    std::cout << "AD: " << attackDamage << std::endl;
}