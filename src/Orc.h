/**
 * Title: Orc.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include "Entity.h"

class Orc : public Entity {
    public:
        Orc();
        virtual void update(sf::Time);
};