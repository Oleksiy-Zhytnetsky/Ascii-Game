#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Constants.h"

#include <cstdint>

class Entity {
public:
    Entity() : xpos(0), ypos(0), healthpoints(0), damage(0), symbol('\0') {}

    Entity(const uint16_t xpos, const uint16_t ypos, const uint16_t healthpoints, 
           const uint16_t damage, const char symbol) : 
        xpos(xpos), ypos(ypos), healthpoints(healthpoints), damage(damage), symbol(symbol) {}

    virtual ~Entity() = default;

public:
    void attack(Entity &other);

    inline uint16_t get_xpos() const { return xpos; }
    inline uint16_t get_ypos() const { return ypos; }
    inline char get_symbol() const { return symbol; }
    inline uint16_t get_healthpoints() const { return healthpoints; }
    inline uint16_t get_damage() const { return damage; }

    inline void set_xpos(const uint16_t xpos) { this->xpos = xpos; }
    inline void set_ypos(const uint16_t ypos) { this->ypos = ypos; }
    inline void set_healthpoints(const uint16_t healthpoints) { this->healthpoints = healthpoints; }

private:
    uint16_t xpos;
    uint16_t ypos;
    uint16_t healthpoints;
    const uint16_t damage;
    const char symbol;
};

#endif // !ENTITY_H
