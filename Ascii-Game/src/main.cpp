#include "headers/IO.h"
#include "headers/Manager.h"

int main() {
    IO::out_greeting();

    Window window;
    Manager::begin_game(IO::in_game_mode(), window);

    Manager::run_main_loop(window);

    return 0;
}
