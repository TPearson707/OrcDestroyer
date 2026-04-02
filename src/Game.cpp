/**
 * Title: Game.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "Game.h"
#include <iostream>

Game::Game()
: mWindow(sf::VideoMode({640, 480}), "Orc Destroyer")
, player()
, orc()
{

    mWindow.setPosition({10, 50});
    mWindow.setVerticalSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    mPlayer.setRadius(40.f);
    mPlayer.setPosition({100.f, 100.f});
    mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() {
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }

}

void Game::processEvents() {

    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            mWindow.close();
        
    }

}

void Game::update(sf::Time dt) {
    player.update(dt);
    orc.update(dt);

    
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(player.getSprite());
    mWindow.draw(orc.getSprite());
    mWindow.display();
}