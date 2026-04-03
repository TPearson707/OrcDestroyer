/**
 * Title: Player.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include "Entity.h"

class Player : public Entity {
    public:
        Player();
        void handleInput();
        virtual void update(sf::Time);
};