#include "headers/IO.h"

#include <cctype>
#include <conio.h>

#pragma region Constants
#define LOADFILE_MODE 0
#define WIDTH_MODE 0

#define MIN_LEVEL_SIZE 3
#pragma endregion

#pragma region Input

char IO::in_game_mode() {
    std::cout << "Would you like to:"
        << "\n\t-- Begin a new game (n)"
        << "\n\t-- Load an existing game (l)"
        << "\n\t-- Quit the game (q)\n" << std::endl;

    char input = '\0';
    while (true) {
        std::cout << "Enter 'n', 'l' or 'q': ";

        input = (char)std::tolower(_getch());
        if (input != 'n' && input != 'l' && input != 'q') {
            IO::out_err_invalid_input();
            continue;
        }
        else return input;
    }
}

char IO::in_move_direction() {
    std::cout << "\nYOUR TURN!"
        << "\n  'W' - Move Up"
        << "\n  'S' - Move Down"
        << "\n  'A' - Move Left"
        << "\n  'D' - Move Right\n" << std::endl;

    char input = '\0';
    while (true) {
        std::cout << "Enter 'W', 'S', 'A' or 'D': ";

        input = (char)std::tolower(_getch());
        if (input != 'w' && input != 's' && input != 'a' && input != 'd') {
            IO::out_err_invalid_input();
            continue;
        }
        else return input;
    }
}

std::string IO::in_player_name() {
    std::string player_name;
    do {
        std::cout << "\nEnter your name: ";
        std::getline(std::cin, player_name);
        if (player_name.empty()) IO::out_err_invalid_input();
    }
    while (player_name.empty());

    return player_name;
}

std::string IO::in_file_name(const uint8_t mode) {
    std::string file_name;
    do {
        (mode == LOADFILE_MODE) ? std::cout << "\nEnter the game you want to load: " : 
            std::cout << "\nEnter the name of the new game: ";
        std::getline(std::cin, file_name);
        if (file_name.empty()) IO::out_err_invalid_input();
    }
    while (file_name.empty());

    return file_name;
}

bool IO::in_newfile_override() {
    std::cout << "A file with this name already exists, do you want to override it?" << std::endl;
    while (true) {
        char input = '\0';
        while (true) {
            std::cout << "(Y/N): ";

            input = (char)std::tolower(_getch());
            if (input != 'y' && input != 'n') { 
                IO::out_err_invalid_input(); 
                continue; 
            }
            else return (input == 'y');
        }
    }
}

uint16_t IO::in_level_size(const uint8_t mode) {
    uint16_t size = 0;
    std::string input;

    do {
        (mode == WIDTH_MODE) ? std::cout << "\nEnter the width of the level: " :
            std::cout << "\nEnter the height of the level: ";

        std::getline(std::cin, input);
        if (input.empty()) IO::out_err_invalid_input();
        for (const char symbol : input) {
            if (!isdigit(symbol)) { 
                IO::out_err_invalid_input(); 
                input.clear();
                break;
            }
        }

        if (!input.empty()) {
            size = (uint16_t)std::stoul(input);
            if (size < MIN_LEVEL_SIZE) {
                IO::out_err_min_limit_exceeded(MIN_LEVEL_SIZE);
                input.clear();
            }
        }
    }
    while (input.empty());

    return size;
}

#pragma endregion
