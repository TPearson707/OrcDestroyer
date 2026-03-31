/**
 * Title: Orc.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Orc {
    public:
        Orc();
        
        void update(float);

        void setSprite(sf::Texture&);
        void setHP(int);
        void setAttackDamage(int);

        sf::Sprite& getSprite();

        int getHP();
        int getAttackDamage(); 

        void printOrcInfo();
    private:
    private:
        sf::Sprite sprite;  
        int hp;
        int attackDamage;

        Action currentAction = Action::IDLE;
        int currentFrame = 0;
        float animTimer = 0.f;
        float frameInterval = 0.1f;
};