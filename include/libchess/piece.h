#include <string>

namespace libchess {

enum class PieceType : unsigned int {
    PAWN = 0,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class PieceColor : unsigned int {
    WHITE = 0,
    BLACK
};

class Piece {
  public:
    Piece(PieceType piece_type, PieceColor piece_color);

    [[nodiscard]] std::string GetPrintableString() const;

  private:
    PieceType _type;
    PieceColor _color;
};

}
