#include "libchess/move.h"

namespace libchess {

Move::Move(const std::string& move_str) {
    if (move_str.size() != 4) {
        // TODO:
    }

    m_starting_x = move_str[0] + kOffsetX;
    m_starting_y = kOffsetY - move_str[1];
    m_ending_x = move_str[2] + kOffsetX;
    m_ending_y = kOffsetY - move_str[3];
}

Move::Move(int starting_x, int starting_y, int ending_x, int ending_y)
    : m_starting_x(starting_x)
    , m_starting_y(starting_y)
    , m_ending_x(ending_x)
    , m_ending_y(ending_y) {
}

int Move::GetStartingX() const {
    return m_starting_x;
}

int Move::GetStartingY() const {
    return m_starting_y;
}

int Move::GetEndingX() const {
    return m_ending_x;
}

int Move::GetEndingY() const {
    return m_ending_y;
}

bool Move::Valid() const {
    if (m_starting_x < 0 || m_starting_x > 7) {
        return false;
    }
    if (m_starting_y < 0 || m_starting_y > 7) {
        return false;
    }
    if (m_ending_x < 0 || m_ending_x > 7) {
        return false;
    }
    if (m_ending_y < 0 || m_ending_y > 7) {
        return false;
    }
    return true;
}

bool Move::Compare(const Move& move) const {
    if (m_starting_x != move.m_starting_x) {
        return false;
    }

    if (m_starting_y != move.m_starting_y) {
        return false;
    }

    if (m_ending_x != move.m_ending_x) {
        return false;
    }

    if (m_ending_y != move.m_ending_y) {
        return false;
    }

    return true;
}

bool Move::IsShortCastle() const {
    bool black_short_castle =
        m_starting_x == 4 && m_starting_y == 0 && m_ending_x == 6 && m_ending_y == 0;
    bool white_short_castle =
        m_starting_x == 4 && m_starting_y == 7 && m_ending_x == 6 && m_ending_y == 7;

    return black_short_castle || white_short_castle;
}

bool Move::IsLongCastle() const {
    bool black_long_castle =
        m_starting_x == 4 && m_starting_y == 0 && m_ending_x == 2 && m_ending_y == 0;
    bool white_long_castle =
        m_starting_x == 4 && m_starting_y == 7 && m_ending_x == 2 && m_ending_y == 7;

    return black_long_castle || white_long_castle;
}

}
