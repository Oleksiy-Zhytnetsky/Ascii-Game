#include "headers/Manager.h"
#include "headers/IO.h"

#define NEW_GAME 'n'
#define LOAD_GAME 'l'
#define QUIT_GAME 'q'

#pragma region Public Methods

void Manager::begin_game(const char control_char, Window &window) {
    switch (control_char) {
        case NEW_GAME: window.create_game(); break;
        case LOAD_GAME: window.load_level(); break;
        case QUIT_GAME: quit_game();
    }
}

void Manager::run_main_loop(Window &window) {
    // Initialise game objects
    Player player(window.get_initial_player_x(), window.get_initial_player_y());
    std::list<Enemy> enemies;
    init_enemies(window, enemies);

    window.print(player);
    while (true) {
        // Move game entities
        window.move_entities(player, enemies, IO::in_move_direction());

        // Redraw game level
        window.print(player);

        // Handle combat
        player.fight(enemies);
        update_entities(window, player, enemies);

        // Check for game over conditions
        if (game_is_over(player, enemies)) {
            window.print(player);
            IO::out_end_game();
            break;
        }
    }
}

#pragma endregion

#pragma region Private Methods

void Manager::quit_game() {
    IO::out_end_game();
    std::exit(0);
}

void Manager::init_enemies(Window &window, std::list<Enemy> &enemies) {
    for (const CoordinatePair &pair : window.get_initial_enemy_locations()) {
        enemies.emplace_back(pair.xpos, pair.ypos);
    }
}

void Manager::update_entities(Window &window, Player &player, std::list<Enemy> &enemies) {
    update_player(window, player);
    update_enemies(window, enemies);
}

void Manager::update_player(Window &window, Player &player) {
    if (player.get_healthpoints() == 0) {
        window.set_level_state(player.get_ypos() * window.get_level_width() + player.get_xpos(), AIR_SYMBOL);
    }
}

void Manager::update_enemies(Window &window, std::list<Enemy> &enemies) {
    using iterator = std::list<Enemy>::iterator;
    for (iterator it = enemies.begin(); it != enemies.end();) {
        if (it->get_healthpoints() == 0) {
            window.set_level_state(it->get_ypos() * window.get_level_width() + it->get_xpos(), AIR_SYMBOL);
            it = enemies.erase(it);
        }
        else ++it;
    }
}

bool Manager::game_is_over(Player &player, std::list<Enemy> &enemies) {
    return player.get_healthpoints() == 0 || enemies.empty();
}

#pragma endregion
