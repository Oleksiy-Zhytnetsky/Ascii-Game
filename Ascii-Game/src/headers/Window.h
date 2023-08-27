#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "Player.h"
#include "Enemy.h"
#include "CoordinatePair.h"

#include <array>
#include <fstream>
#include <vector>

class Window {
public:
    Window() : initial_player_x(0), initial_player_y(0), level_width(0), level_height(0) {}
    
    ~Window() = default;

public:
    void print(const Player &player) const;
    void load_level();
    void create_game();
    void move_entities(Player &player, std::list<Enemy> &enemies, const char player_direction);

    inline uint16_t get_initial_player_x() const { return initial_player_x; }
    inline uint16_t get_initial_player_y() const { return initial_player_y; }
    inline uint16_t get_level_width() const { return level_width; }
    inline uint16_t get_level_height() const { return level_height; }
    inline uint16_t get_level_size() const { return level_width * level_height; }
    inline std::vector<CoordinatePair> get_initial_enemy_locations() const { return initial_enemy_locations; }
    inline std::vector<char> get_level_state() const { return level_state; }

    inline void set_level_state(const uint16_t position, const char symbol) { level_state[position] = symbol; }

private:
    void create_game_file(const std::string &newfile_name);
    void init_game_level();
    void wallfill_line(const uint16_t width, const uint16_t y_index);
    void wallfill_column(const uint16_t height, const uint16_t x_index, const uint16_t width);
    bool move_entity(Entity &entity, const char direction);
    void update_level_state_on_entity_move(Entity &entity, const uint16_t previous_index, const uint16_t current_index);
    std::array<uint8_t, DIRECTIONS_ARRAY_SIZE> get_entity_directions_legality(Entity &entity) const;
    char map_direction_to_char(const uint8_t direction) const;

private:
    uint16_t level_width;
    uint16_t level_height;
    uint16_t initial_player_x;
    uint16_t initial_player_y;
    std::vector<CoordinatePair> initial_enemy_locations;
    std::vector<char> level_state;
};

#endif // !WINDOW_H
