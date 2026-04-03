/**
 * Title: Player.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include "Entity.h"

enum class Direction {UP, DOWN, LEFT, RIGHT};

class Player : public Entity {
    public:
        Player();
        virtual void update(sf::Time);

        private:
            void moveSprite();
            void dash();    
            void checkDash();       
            void attack();
            void takeDamage(int);
            void handleInput();
        private:
            Direction facing;
};