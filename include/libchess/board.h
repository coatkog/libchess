#pragma once

#include "libchess/move.h"
#include "libchess/square.h"

#include <array>
#include <memory>
#include <string>

namespace libchess {

class Board {
  public:
    static constexpr std::size_t kBoardHeight = 8;
    static constexpr std::size_t kBoardWidth = 8;
    using BoardMatrix = std::array<std::array<Square, kBoardWidth>, kBoardHeight>;

    Board();

    static std::string GetFen();

    [[nodiscard]] BoardMatrix GetBoard() const;

    void DoMove(const Move& move);

    [[nodiscard]] std::string ToString() const;

  private:
    static const BoardMatrix kStartingBoard;

    BoardMatrix _board;
    bool _white_to_move;

    void ValidateMove(const Move& move);
};

}
