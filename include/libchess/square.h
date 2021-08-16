#pragma once

#include "libchess/piece.h"

#include <memory>

namespace libchess {

enum class SquareColor : unsigned int
{
    WHITE = 0,
    BLACK
};

class Square {
  public:
    Square();
    Square(SquareColor square_color);
    Square(SquareColor square_color, PieceType piece_type, PieceColor piece_color);

    void SwapPieces(Square& square);

    [[nodiscard]] PieceColor GetPieceColor() const;
    [[nodiscard]] PieceType GetPieceType() const;
    [[nodiscard]] bool ContainsPiece() const;

    [[nodiscard]] std::string ToString() const;

  private:
    SquareColor _color;
    std::shared_ptr<Piece> _piece;
};

}
