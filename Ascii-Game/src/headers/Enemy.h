#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#include <random>
#include <ctime>

class Enemy : public Entity {
public:
    Enemy() : Entity() {}
    
    Enemy(const uint16_t xpos, const uint16_t ypos) : 
        Entity(xpos, ypos, ENEMY_HEALTH, ENEMY_DAMAGE, ENEMY_SYMBOL) {}
    
    ~Enemy() override = default;

public:
    static inline std::default_random_engine rgen = std::default_random_engine((uint32_t)clock());
    static inline std::uniform_int_distribution<uint16_t> direction_roll = 
        std::uniform_int_distribution<uint16_t>(1, 4);
};

#endif // !ENEMY_H
