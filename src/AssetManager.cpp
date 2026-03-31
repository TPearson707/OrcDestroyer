/**
 * Title: AssetManager.cpp
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager() {
    compileAssets();
}

void AssetManager::compileAssets() {
    populateTexturesMap();
    populateFramesMap();
}

void AssetManager::populateTexturesMap() {
    std::string urlPrefix = "assets/Soldier/Soldier/";

    textures[{ CharacterType::SOLDIER, Action::IDLE }] = loadTexture(urlPrefix + "Soldier-Idle.png");
    textures[{ CharacterType::SOLDIER, Action::WALK }] = loadTexture(urlPrefix + "Soldier-Walk.png");
    textures[{ CharacterType::SOLDIER, Action::ATTACK }] = loadTexture( urlPrefix + "Soldier-Attack01.png");

    urlPrefix = "assets/Orc/Orc/";

    textures[{ CharacterType::ORC, Action::IDLE }] = loadTexture(urlPrefix + "Orc-Idle.png");
    textures[{ CharacterType::ORC, Action::WALK }] = loadTexture(urlPrefix + "Orc-Walk.png");
    textures[{ CharacterType::ORC, Action::ATTACK  }] = loadTexture(urlPrefix + "Orc-Attack01.png");

}

sf::Texture AssetManager::loadTexture(const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load texture!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return texture;
}

sf::Texture& AssetManager::getTexture(CharacterType character, Action action) {
    return textures.at({ character, action });
}

void AssetManager::populateFramesMap() {
    int frameWidth = 100;
    int frameHeight = 100;

    for (auto& texture : textures) {
        frames[texture.first] = loadFrames(texture.second, frameWidth, frameHeight);
    }
}

std::vector<sf::IntRect> AssetManager::loadFrames(sf::Texture& texture, int frameWidth, int frameHeight) {
    std::vector<sf::IntRect> frames;
    sf::Vector2u textureSize = texture.getSize();
    int cols = textureSize.x / frameWidth;
    int rows = textureSize.y / frameHeight;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            frames.push_back(sf::IntRect(
                {col * frameWidth, row * frameHeight},
                {frameWidth, frameHeight}
            ));
        }
    }
    return frames;
}

std::vector<sf::IntRect>& AssetManager::getFrames(CharacterType character, Action action) {
    return frames.at({ character, action });
}