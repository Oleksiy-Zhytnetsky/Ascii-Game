#include "headers/Window.h"
#include "headers/IO.h"

#pragma region Constants

#define LOADFILE_LEVEL_SIZE_LINE_LENGTH 3
#define LOADFILE_LEVEL_WIDTH_INDEX 0
#define LOADFILE_LEVEL_HEIGHT_INDEX 2
#define LOADFILE_LEVEL_STATE_ROW_INDEX 0
#define LOADFILE_LEVEL_STATE_COLUMN_INDEX 2
#define LOADFILE_LEVEL_STATE_CHAR_INDEX 5

#define LOADFILE_MODE 0
#define NEWFILE_MODE 1

#define WIDTH_MODE 0
#define HEIGHT_MODE 1

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

#pragma endregion

#pragma region Public Methods

void Window::print(const Player &player) const {
    std::system("cls");
    IO::out_game_legend();
    IO::out_window_caption();
    for (uint16_t i = 0; i < get_level_size(); i++) {
        IO::out_window_symbol(level_state[i]);
        if ((i + 1) % level_width == 0) IO::out_newline();
    }
    IO::out_player_healthpoints(player);
}

void Window::load_level() {
    std::ifstream loadfile;

    do {
        std::string loadfile_name = "saves/" + IO::in_file_name(LOADFILE_MODE);
        loadfile_name.append(".save");

        loadfile.open(loadfile_name, std::ios_base::in);
        if (loadfile.fail()) IO::out_load_file_failed();
    }
    while (loadfile.fail());

    std::string loaded_data;
    while (std::getline(loadfile, loaded_data)) {
        if (loaded_data.length() == LOADFILE_LEVEL_SIZE_LINE_LENGTH) {
            level_width = (loaded_data[LOADFILE_LEVEL_WIDTH_INDEX] - '0');
            level_height = (loaded_data[LOADFILE_LEVEL_HEIGHT_INDEX] - '0');

            level_state.resize(level_width * level_height);
        }
        else {
            if (loaded_data == "") break;
            uint16_t curr_row = (loaded_data[LOADFILE_LEVEL_STATE_ROW_INDEX] - '0');
            uint16_t curr_column = (loaded_data[LOADFILE_LEVEL_STATE_COLUMN_INDEX] - '0');
            level_state[curr_row * level_width + curr_column] = 
                loaded_data[LOADFILE_LEVEL_STATE_CHAR_INDEX];

            if (loaded_data[LOADFILE_LEVEL_STATE_CHAR_INDEX] == PLAYER_SYMBOL) {
                initial_player_x = curr_column;
                initial_player_y = curr_row;
            }
            else if (loaded_data[LOADFILE_LEVEL_STATE_CHAR_INDEX] == ENEMY_SYMBOL) {
                initial_enemy_locations.push_back(CoordinatePair(curr_column, curr_row));
            }
        }
    }
}

void Window::create_game() {
    std::string newfile_name;

    do {
        newfile_name = "saves/" + IO::in_file_name(NEWFILE_MODE) + ".save";
        std::string temp_loadfile_name = newfile_name;

        std::ifstream temp_loadfile;
        bool override_file = false;

        temp_loadfile.open(temp_loadfile_name, std::ios_base::in);
        if (!temp_loadfile.fail()) {
            override_file = IO::in_newfile_override();
            if (override_file) break;
        }
        else break;
    }
    while (true);

    level_width = IO::in_level_size(WIDTH_MODE);
    level_height = IO::in_level_size(HEIGHT_MODE);
    level_state.resize(level_width * level_height);
    init_game_level();

    create_game_file(newfile_name);
}

void Window::move_entities(Player &player, std::list<Enemy> &enemies, const char player_direction) {
    move_entity(player, player_direction);
    for (Enemy &enemy : enemies) {
        move_entity(enemy, map_direction_to_char(Enemy::direction_roll(Enemy::rgen)));
    }
}

#pragma endregion

#pragma region Private Methods

void Window::create_game_file(const std::string &newfile_name) {
    std::ofstream newfile;
    newfile.open(newfile_name, std::ios_base::out);

    newfile << (std::to_string(level_width) + "x" + std::to_string(level_height)) << '\n';
    for (uint16_t y = 0; y < level_height; y++) {
        for (uint16_t x = 0; x < level_width; x++) {
            newfile << (std::to_string(y) + "-" + std::to_string(x) + ": " + 
                        level_state[x + y * level_width]);
            newfile << '\n';
        }
    }
}

void Window::init_game_level() {
    /* Background || Air */
    for (uint16_t i = 0; i < level_height; i++) {
        for (uint16_t j = 0; j < level_width; j++) {
            level_state[j + i * level_width] = AIR_SYMBOL;
        }
    }

    /* Outer Walls */
    wallfill_line(level_width, 0);
    wallfill_line(level_width, level_height - 1);
    wallfill_column(level_height, 0, level_width);
    wallfill_column(level_height, level_width - 1, level_width);

    /* Player Character */
    initial_player_x = 1;
    initial_player_y = 1;
    level_state[level_width + 1] = PLAYER_SYMBOL;

    /* Enemies */
    uint8_t added_entities_count = 0;
    for (uint16_t i = 0; i < level_state.size(); i++) {
        if (added_entities_count >= OPTIMAL_ENEMY_COUNT) break;

        const uint16_t current_index = level_state.size() - i - 1;
        if (level_state[current_index] == AIR_SYMBOL) {
            initial_enemy_locations.push_back(CoordinatePair(
                current_index % level_width,
                current_index / level_width
            ));
            level_state[current_index] = ENEMY_SYMBOL;
            ++added_entities_count;
        }
    }
}

void Window::wallfill_line(const uint16_t width, const uint16_t y_index) {
    for (uint16_t i = 0; i < width; i++) level_state[i + width * y_index] = WALL_SYMBOL;
}

void Window::wallfill_column(const uint16_t height, const uint16_t x_index, const uint16_t width) {
    for (uint16_t i = 0; i < height; i++) level_state[x_index + width * i] = WALL_SYMBOL;
}

bool Window::move_entity(Entity &entity, const char direction) {
#define CURRENT_STATE_INDEX entity.get_xpos() + entity.get_ypos() * level_width

    std::array<uint8_t, DIRECTIONS_ARRAY_SIZE> directions = get_entity_directions_legality(entity);

    switch (direction) {
        case MOVE_UP:
            if (directions[UP_INDEX] == INVALID_DIRECTION) return false;
            else {
                update_level_state_on_entity_move(entity, CURRENT_STATE_INDEX,
                                                  CURRENT_STATE_INDEX - level_width);
                entity.set_ypos(entity.get_ypos() - 1);
                return true;
            }
        case MOVE_DOWN:
            if (directions[DOWN_INDEX] == INVALID_DIRECTION) return false;
            else {
                update_level_state_on_entity_move(entity, CURRENT_STATE_INDEX, 
                                                  CURRENT_STATE_INDEX + level_width);
                entity.set_ypos(entity.get_ypos() + 1);
                return true;
            }
        case MOVE_LEFT:
            if (directions[LEFT_INDEX] == INVALID_DIRECTION) return false;
            else {
                update_level_state_on_entity_move(entity, CURRENT_STATE_INDEX, 
                                                  CURRENT_STATE_INDEX - 1);
                entity.set_xpos(entity.get_xpos() - 1);
                return true;
            }
        case MOVE_RIGHT:
            if (directions[RIGHT_INDEX] == INVALID_DIRECTION) return false;
            else {
                update_level_state_on_entity_move(entity, CURRENT_STATE_INDEX,
                                                  CURRENT_STATE_INDEX + 1);
                entity.set_xpos(entity.get_xpos() + 1);
                return true;
            }
    }

    return false;
}

void Window::update_level_state_on_entity_move(Entity &entity, const uint16_t previous_index, 
                                               const uint16_t current_index) {
    level_state[previous_index] = '.';
    level_state[current_index] = entity.get_symbol();
}

std::array<uint8_t, DIRECTIONS_ARRAY_SIZE> 
Window::get_entity_directions_legality(Entity &entity) const {
    std::array<uint8_t, DIRECTIONS_ARRAY_SIZE> directions{};

    std::array<uint16_t, DIRECTIONS_ARRAY_SIZE> neighbor_indices{};
    neighbor_indices[0] = CURRENT_STATE_INDEX - 1;
    neighbor_indices[1] = CURRENT_STATE_INDEX + 1;
    neighbor_indices[2] = CURRENT_STATE_INDEX - level_width;
    neighbor_indices[3] = CURRENT_STATE_INDEX + level_width;

    for (uint8_t i = 0; i < neighbor_indices.size(); i++) {
        if (level_state[neighbor_indices[i]] == AIR_SYMBOL) directions[i] = 1;
    }

    return directions;
}

char Window::map_direction_to_char(const uint8_t direction) const {
    switch (direction) {
        case DIRECTION_UP: return 'w';
        case DIRECTION_DOWN: return 's';
        case DIRECTION_LEFT: return 'a';
        case DIRECTION_RIGHT: return 'd';
    }
    return '\0';
}

#pragma endregion
