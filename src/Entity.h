#pragma once

#include <SFML/Graphics.hpp>
#include "Animator.h"
#include "AssetManager.h"

class Entity {
    public:
        Entity(sf::Texture&, CharacterType);
        virtual ~Entity() = default;
        
        virtual void update(sf::Time);

        void setSprite(sf::Texture&);
        void setHP(int);
        void setAttackDamage(int);

        sf::Sprite& getSprite();

        int getHP();
        int getAttackDamage(); 

        void printEntityInfo();
    
    protected:
        sf::Sprite sprite;  
        Animator animator;
        int hp;
        int attackDamage;
        CharacterType character;
        Action currentAction = Action::IDLE;
};