#include "libchess/move.h"
#include "libchess/square.h"

#include <array>
#include <memory>
#include <string>

namespace libchess {

class Board {
  public:
    Board();

    static std::string GetFen();

    [[nodiscard]] std::string GetPrintableString() const;

    void DoMove(Move move);

  private:
    static constexpr std::size_t kBoardHeight = 8;
    static constexpr std::size_t kBoardWidth = 8;

    using BoardMatrix = std::array<std::array<Square, kBoardWidth>, kBoardHeight>;

    static const BoardMatrix kStartingBoard;

    BoardMatrix _board;
};

}
