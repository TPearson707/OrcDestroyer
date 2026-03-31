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
, mPlayer()
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

    while (mWindow.isOpen()) {
        float dt = dtClock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }

}

void Game::processEvents() {

    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            mWindow.close();

    }

}

void Game::update(float deltaTime) {
    player.update(deltaTime);
    orc.update(deltaTime);
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(player.getSprite());
    mWindow.draw(orc.getSprite());
    mWindow.display();
}