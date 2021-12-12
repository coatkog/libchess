#pragma once

#include <iostream>
#include <string>

namespace libchess {

class Move {
  public:
    Move(const std::string& move_str);
    Move(int starting_x, int starting_y, int ending_x, int ending_y);

    [[nodiscard]] int GetStartingX() const;
    [[nodiscard]] int GetStartingY() const;
    [[nodiscard]] int GetEndingX() const;
    [[nodiscard]] int GetEndingY() const;

    [[nodiscard]] bool Valid() const;

    [[nodiscard]] bool Compare(const Move& move) const;

    [[nodiscard]] bool IsShortCastle() const;
    [[nodiscard]] bool IsLongCastle() const;

  private:
    static constexpr int kOffsetX = -'a';
    static constexpr int kOffsetY = 8 + '0';

    int m_starting_x;
    int m_starting_y;
    int m_ending_x;
    int m_ending_y;
};

}
