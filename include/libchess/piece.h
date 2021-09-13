#pragma once

#include <string>

namespace libchess {

enum class PieceType : std::uint8_t
{
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class PieceColor : std::uint8_t
{
    WHITE = 0,
    BLACK
};

class Piece {
  public:
    Piece(PieceType piece_type, PieceColor piece_color);

    [[nodiscard]] PieceType GetType() const;
    [[nodiscard]] PieceColor GetColor() const;

    [[nodiscard]] bool GetFirstMove() const;
    void SetFirstMove(bool first_move);

    [[nodiscard]] std::string ToString() const;

  private:
    PieceType m_type;
    PieceColor m_color;

    bool m_first_move;
};

}
