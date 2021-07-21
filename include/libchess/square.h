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

    [[nodiscard]] std::string GetPrintableString() const;

    void SwapPieces(Square& square);

  private:
    SquareColor _color;
    std::shared_ptr<Piece> _piece;
};

}
