#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

/* BEGIN */

#define MOVE_UP 'w'
#define UP_INDEX 2
#define MOVE_DOWN 's'
#define DOWN_INDEX 3
#define MOVE_LEFT 'a'
#define LEFT_INDEX 0
#define MOVE_RIGHT 'd'
#define RIGHT_INDEX 1
#define INVALID_DIRECTION 0
#define DIRECTIONS_ARRAY_SIZE 4

#define PLAYER_SYMBOL '@'
#define PLAYER_HEALTH 50
#define PLAYER_DAMAGE 10
#define ENEMY_SYMBOL 'E'
#define ENEMY_HEALTH 25
#define ENEMY_DAMAGE 4
#define WALL_SYMBOL '#'
#define AIR_SYMBOL '.'

#define OPTIMAL_ENEMY_COUNT 3

/* END */

#endif // !CONSTANTS_H
