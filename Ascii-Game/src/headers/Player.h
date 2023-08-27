#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"

#include <list>

class Player : public Entity {
public:
    Player() : Entity() {}

    Player(const uint16_t xpos, const uint16_t ypos) : 
        Entity(xpos, ypos, PLAYER_HEALTH, PLAYER_DAMAGE, PLAYER_SYMBOL) {}

    ~Player() override = default;

public:
    void fight(std::list<Enemy> &enemies);

private:
    bool is_within_engagement_range(const Enemy &enemy);
};

#endif // PLAYER_H
