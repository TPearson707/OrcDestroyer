#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animator {
    public:
        Animator();
        void setFrames(const std::vector<sf::IntRect>& frames);
        void animate(sf::Sprite& sprite, sf::Time dt);
    private:
        std::vector<sf::IntRect> frames;
        int currentFrame;
        float animTimer;
        float frameInterval;
};