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

  private:
    static constexpr int kOffsetX = -'a';
    static constexpr int kOffsetY = 8 + '0';

    int _starting_x;
    int _starting_y;
    int _ending_x;
    int _ending_y;
};

}
