/**
 * Title: AssetManager.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

/*
 * This class is a resource manager
 * Could build towards an actual game engine
 * Currently handles loading -> chaching -> serving assets
 * 
 */

#pragma once

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.hpp"

enum class CharacterType { SOLDIER, ORC };
enum class Action { IDLE, WALK, ATTACK };

struct AssetKey {
    CharacterType character;
    Action action;

    // Need A < B functionality when comparing key values
    bool operator<(const AssetKey& other) const {
        if (character != other.character)
            return character < other.character;
        return action < other.action;
    }
};

class AssetManager {
    public:
        static AssetManager& getInstance() {
            static AssetManager instance;
            return instance;
        }

        sf::Texture& getTexture(CharacterType, Action);
        std::vector<sf::IntRect>& getFrames(CharacterType, Action);
        // Delete copy/move so no one can duplicate (singleton)
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

    private:
        AssetManager();
        void compileAssets();

        void populateTexturesMap();
        sf::Texture loadTexture(const std::string&);

        void populateFramesMap();
        std::vector<sf::IntRect> loadFrames(sf::Texture&, int, int);

    private:
        std::map<AssetKey, sf::Texture> textures;
        std::map<AssetKey, std::vector<sf::IntRect>> frames;

};