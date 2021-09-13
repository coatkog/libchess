#pragma once

#include "libchess/piece.h"

#include <cstdint>
#include <memory>

namespace libchess {

enum class SquareColor : std::uint8_t
{
    WHITE = 0,
    BLACK
};

class Square {
  public:
    Square(SquareColor square_color);
    Square(SquareColor square_color, PieceType piece_type, PieceColor piece_color);

    void SwapPieces(Square& square);

    [[nodiscard]] SquareColor GetColor() const;

    [[nodiscard]] PieceColor GetPieceColor() const;
    [[nodiscard]] PieceType GetPieceType() const;
    [[nodiscard]] bool Empty() const;

    [[nodiscard]] bool IsPieceFirstMove() const;

    [[nodiscard]] std::string ToString() const;

  private:
    SquareColor m_color;
    std::shared_ptr<Piece> m_piece;
};

}
