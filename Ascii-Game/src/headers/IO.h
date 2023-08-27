#pragma once
#ifndef IO_H
#define IO_H

#include "Player.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>

class IO {
public:
    IO() = delete;
    ~IO() = delete;

public:

#pragma region Output

    static inline void out_greeting() {
        std::cout << "<!---------------------------------------------!>" << std::endl;
        std::cout << "\tWelcome to Ascii Roguelike v1.0!" << std::endl;
    }

    static inline void out_load_file_failed() {
        std::cout << "ERROR: unable to load specified file. Please try again." << std::endl;
    }

    static inline void out_game_legend() {
        std::cout << "\nGAME LEGEND:"
            << "\n  '#' - walls"
            << "\n  '.' - air"
            << "\n  '@' - player"
            << "\n  'T' - enemy" << std::endl;
    }

    static inline void out_window_caption() { std::cout << "\nGAME WINDOW:" << std::endl; }

    static inline void out_window_symbol(const char symbol) { std::cout << ' ' << symbol << ' '; }

    static inline void out_player_healthpoints(const Player &player) {
        std::cout << "\nPlayer health: " << player.get_healthpoints() << std::endl;
    }

    static inline void out_newline() { std::cout << '\n'; }

    static inline void out_end_game() { 
        std::cout << "\n\nBye!" << std::endl; 
        std::system("pause");
    }

    static inline void out_err_invalid_input(const bool insert_newline = true) {
        std::cout << "Invalid input! Please try again.";
        if (insert_newline) std::cout << '\n';
    }

    static inline void out_err_min_limit_exceeded(const int32_t limit, 
                                                  const bool insert_newline = true) {
        std::cout << "Invalid input! Please enter a value that is above or equal to " 
            << limit << ".";
        if (insert_newline) std::cout << '\n';
    }

#pragma endregion

#pragma region Input

    static char in_game_mode();
    static char in_move_direction();
    static std::string in_player_name();
    static std::string in_file_name(const uint8_t mode);
    static bool in_newfile_override();
    static uint16_t in_level_size(const uint8_t mode);

#pragma endregion

};

#endif // !IO_H
