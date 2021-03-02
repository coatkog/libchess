#include "libchess/move.h"
#include <exception>
#include <stdexcept>

namespace libchess {

Move::Move(const std::string& move_str) {
    // TODO: Inherit move_error from runtime_error and throw it instead

    if (move_str.size() != 4) {
        throw std::runtime_error("Invalid move."); 
    }
    if (move_str[0] < 'a' || move_str[0] > 'h') {
        throw std::runtime_error("Invalid move.");
    }
    if (move_str[1] < '1' || move_str[1] > '8') {
        throw std::runtime_error("Invalid move.");
    }
    if (move_str[2] < 'a' || move_str[2] > 'h') {
        throw std::runtime_error("Invalid move.");
    }
    if (move_str[3] < '1' || move_str[3] > '8') {
        throw std::runtime_error("Invalid move.");
    }

    _starting_x = 7 - (move_str[1] - '1');
    _starting_y = move_str[0] - 'a';
    _ending_x = 7 - (move_str[3] - '1');
    _ending_y = move_str[2] - 'a';
}

std::size_t Move::GetStartingX() const {
    return _starting_x;
}

std::size_t Move::GetStartingY() const {
    return _starting_y;
}

std::size_t Move::GetEndingX() const {
    return _ending_x;
}

std::size_t Move::GetEndingY() const {
    return _ending_y;
}

}
