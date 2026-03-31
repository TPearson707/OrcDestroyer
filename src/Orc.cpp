/**
 * Title: Orc.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Orc.h"
#include <iostream>

Orc::Orc() {
    hp = 1;
    attackDamage = 1;
}

// Using sentinel/assert - enforce minimum 0
void Orc::setHP(int hp) {
    this->hp = std::max(0, hp);
}

void Orc::setAttackDamage(int attackDamage) {
    this->attackDamage = std::max(0, attackDamage);
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