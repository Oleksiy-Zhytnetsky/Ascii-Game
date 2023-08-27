#include "headers/Player.h"

#include <cmath>

#define ENGAGEMENT_RANGE 1

#pragma region Public Methods

void Player::fight(std::list<Enemy> &enemies) {
    bool player_has_attacked = false;
    for (Enemy &enemy : enemies) {
        if (is_within_engagement_range(enemy)) {
            if (!player_has_attacked) {
                attack(enemy);
                player_has_attacked = true;
            }
            enemy.attack(*this);
        }
    }
}

#pragma endregion

#pragma region Private Methods

bool Player::is_within_engagement_range(const Enemy &enemy) {
    return (std::abs(get_xpos() - enemy.get_xpos()) <= ENGAGEMENT_RANGE && 
            std::abs(get_ypos() - enemy.get_ypos()) <= ENGAGEMENT_RANGE);
}

#pragma endregion
