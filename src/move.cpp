#include "libchess/move.h"

namespace libchess {

move::move(const std::string& move_str) {
    if (move_str.size() != 4) {
        // TODO:
    }

    starting_x = move_str[0] - 'a';
    starting_y = '8' - move_str[1];
    ending_x = move_str[2] - 'a';
    ending_y = '8' - move_str[3];
}

move::move(int starting_x, int starting_y, int ending_x, int ending_y)
    : starting_x(starting_x)
    , starting_y(starting_y)
    , ending_x(ending_x)
    , ending_y(ending_y) {
}

std::string move::to_string() const {
    return { static_cast<char>('a' + starting_x),
             static_cast<char>('8' - starting_y),
             static_cast<char>('a' + ending_x),
             static_cast<char>('8' - ending_y) };
}

bool move::valid() const {
    if (starting_x < 0 || starting_x > 7) {
        return false;
    }
    if (starting_y < 0 || starting_y > 7) {
        return false;
    }
    if (ending_x < 0 || ending_x > 7) {
        return false;
    }
    if (ending_y < 0 || ending_y > 7) {
        return false;
    }
    return true;
}

bool move::is_short_castle() const {
    bool black_short_castle =
        starting_x == 4 && starting_y == 0 && ending_x == 6 && ending_y == 0;
    bool white_short_castle =
        starting_x == 4 && starting_y == 7 && ending_x == 6 && ending_y == 7;

    return black_short_castle || white_short_castle;
}

bool move::is_long_castle() const {
    bool black_long_castle =
        starting_x == 4 && starting_y == 0 && ending_x == 2 && ending_y == 0;
    bool white_long_castle =
        starting_x == 4 && starting_y == 7 && ending_x == 2 && ending_y == 7;

    return black_long_castle || white_long_castle;
}

bool move::operator==(const move& rhs) const {
    return starting_x == rhs.starting_x && starting_y == rhs.starting_y &&
           ending_x == rhs.ending_x && ending_y == rhs.ending_y;
}

}
