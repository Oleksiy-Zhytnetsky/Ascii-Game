#pragma once
#ifndef COORDINATE_PAIR_H
#define COORDINATE_PAIR_H

#include <cstdint>

struct CoordinatePair {
    const uint16_t xpos;
    const uint16_t ypos;

    CoordinatePair() : xpos(0), ypos(0) {}
    CoordinatePair(const uint16_t xpos, const uint16_t ypos) : xpos(xpos), ypos(ypos) {}
};

#endif // !COORDINATE_PAIR_H
