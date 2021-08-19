#include "libchess/move.h"

namespace libchess {

Move::Move(const std::string& move_str) {
    if (move_str.size() != 4) {
        // TODO:
    }

    _starting_x = move_str[0] + kOffsetX;
    _starting_y = kOffsetY - move_str[1];
    _ending_x = move_str[2] + kOffsetX;
    _ending_y = kOffsetY - move_str[3];
}

Move::Move(int starting_x, int starting_y, int ending_x, int ending_y) {
    _starting_x = starting_x;
    _starting_y = starting_y;
    _ending_x = ending_x;
    _ending_y = ending_y;
}

int Move::GetStartingX() const {
    return _starting_x;
}

int Move::GetStartingY() const {
    return _starting_y;
}

int Move::GetEndingX() const {
    return _ending_x;
}

int Move::GetEndingY() const {
    return _ending_y;
}

bool Move::Valid() const {
    if (_starting_x < 0 || _starting_x > 7) {
        return false;
    }
    if (_starting_y < 0 || _starting_y > 7) {
        return false;
    }
    if (_ending_x < 0 || _ending_x > 7) {
        return false;
    }
    if (_ending_y < 0 || _ending_y > 7) {
        return false;
    }
    return true;
}

}
