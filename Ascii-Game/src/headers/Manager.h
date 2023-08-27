#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "Window.h"

class Manager {
public:
    Manager() = delete;
    ~Manager() = delete;

public:
    static void begin_game(const char control_char, Window &window);
    static void run_main_loop(Window &window);

private:
    static void quit_game();
    static void init_enemies(Window &window, std::list<Enemy> &enemies);
    static void update_entities(Window &window, Player &player, std::list<Enemy> &enemies);
    static void update_player(Window &window, Player &player);
    static void update_enemies(Window &window, std::list<Enemy> &enemies);
    static bool game_is_over(Player &player, std::list<Enemy> &enemies);
};

#endif // !MANAGER_H
