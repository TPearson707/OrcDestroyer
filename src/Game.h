/**
 * Title: Game.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Orc.h"

class Game {
    public:
        Game();
        Game(Player);
        void run();
    private:
        void processEvents();
        void update(float);
        void render();
    private:
        sf::Clock dtClock;
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;
        Player player;
        Orc orc;
};