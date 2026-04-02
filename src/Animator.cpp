#include <iostream>
#include "Animator.h"

Animator::Animator() {
    currentFrame = 0;
    animTimer = 0.f;
    frameInterval = 0.1f;
}

void Animator::setFrames(const std::vector<sf::IntRect>& frames) {
    this->frames = frames;
}

void Animator::animate(sf::Sprite& sprite, sf::Time dt) {
    animTimer += dt.asSeconds();
    if (animTimer >= frameInterval) {
        auto& currentFrames = frames;
        sprite.setTextureRect(currentFrames[currentFrame]);
        currentFrame = (currentFrame + 1) % currentFrames.size();
        animTimer = 0.f;
    }
}