/**
 * Title: Orc.h
 * Author: Thomas Pearson
 * Date Created: 03/31/2026
 * Date of Last Update: 03/31/2026
 */

#pragma once

#include <SFML/Graphics.hpp>

class Orc {
    public:
        Orc();

        void setHP(int);
        void setAttackDamage(int);

        int getHP();
        int getAttackDamage(); 

        void printOrcInfo();
    private:
    private:
        int hp;
        int attackDamage;
};