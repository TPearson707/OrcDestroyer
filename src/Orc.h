/**
 * Title: Orc.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include "Entity.h"

enum class States {IDLE, CHASING, ATTACK, DEATH};

class Orc : public Entity {
    public:
        Orc();
        virtual void update(Entity&, sf::Time);
    private:
        void setState(States);
        void processState(Entity&, sf::Time);
    private:
        States currentState;
        bool isDead;
};