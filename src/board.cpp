#include "libchess/board.h"

#include <sstream>
#include <iostream>

namespace libchess {

std::string Board::FenToHumanReadableString(const std::string& fen) {
    std::stringstream human_readable_string;

    std::string board = fen.substr(0, fen.find(" "));

    std::size_t current_slash_index = board.find("/");
    while (current_slash_index != std::string::npos) {
        board[current_slash_index] = '\n';

        current_slash_index = board.find("/", current_slash_index + 1);
    }

    for (std::size_t i = 0; i < board.size(); i++) {
        const char c = board[i];

        if (std::isdigit(c)) {
            for (std::size_t k = 0; k < static_cast<std::size_t>(c) - '0'; k++) {
                human_readable_string << ".";
            }
        } else {
            human_readable_string << c;
        }
    }

    return human_readable_string.str();
}

Board::Board() {
    _fen = kStartingFen;
}

const std::string& Board::GetFen() {
    return _fen;
}

std::string Board::GetPrintableString() const {
    return Board::FenToHumanReadableString(_fen);
}

}
