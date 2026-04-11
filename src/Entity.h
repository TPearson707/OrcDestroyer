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
        void setSpriteAnimation(CharacterType, Action);
        void setHP(int);
        void setAttackDamage(int);
        void setSpeed(float);

        sf::Sprite& getSprite();

        int getHP();
        int getAttackDamage(); 
        float getSpeed();


        void printEntityInfo();
    
    protected:
        sf::Sprite sprite;  
        Animator animator;

        CharacterType character;
        Action currentAction = Action::IDLE;

        int hp;
        int attackDamage;
        float speed;
};