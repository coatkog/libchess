#include "libchess/board.h"

#include <csignal>
#include <exception>
#include <iostream>

#define log(x) std::cout << x << std::endl

bool running = true;

void my_handler(int /*s*/) {
    log("\nExiting...");
    running = false;
}

int main() {
    struct sigaction sig_int_handler;

    sig_int_handler.sa_handler = my_handler;
    sigemptyset(&sig_int_handler.sa_mask);
    sig_int_handler.sa_flags = 0;

    sigaction(SIGINT, &sig_int_handler, NULL);

    libchess::board board;

    do {
        log("\n");
        log(board.to_string());

        try {
            log("Enter move: ");

            std::string move_str;
            std::cin >> move_str;

            board.do_move(move_str);
        } catch (const std::exception& e) {
            log(e.what());
        }
    } while (running);

    return 0;
}
