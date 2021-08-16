#pragma once

#include <iostream>
#include <string>

namespace libchess {

class Move {
  public:
    Move(const std::string& move_str);

    [[nodiscard]] std::size_t GetStartingX() const;
    [[nodiscard]] std::size_t GetStartingY() const;
    [[nodiscard]] std::size_t GetEndingX() const;
    [[nodiscard]] std::size_t GetEndingY() const;

  private:
    std::size_t _starting_x;
    std::size_t _starting_y;
    std::size_t _ending_x;
    std::size_t _ending_y;
};

}
