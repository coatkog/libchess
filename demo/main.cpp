#include "libchess/board.h"

#include <csignal>
#include <exception>
#include <iostream>

bool running = true;

void my_handler(int /*s*/) {
    std::cout << "\nExiting..." << std::endl;
    exit(0);
}

int main() {
    struct sigaction sig_int_handler;

    sig_int_handler.sa_handler = my_handler;
    sigemptyset(&sig_int_handler.sa_mask);
    sig_int_handler.sa_flags = 0;

    sigaction(SIGINT, &sig_int_handler, NULL);

    libchess::Board b;
    std::cout << std::endl << b.GetPrintableString() << std::endl;

    while (true) {
        try {
            std::cout << "Enter move: ";

            std::string move_str;
            std::cin >> move_str;

            libchess::Move move(move_str);

            b.DoMove(move);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << std::endl << b.GetPrintableString() << std::endl;
    }

    return 0;
}
