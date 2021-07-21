#include "libchess/square.h"
#include <type_traits>

namespace libchess {

Square::Square() = default;

Square::Square(SquareColor square_color)
    : _color(square_color)
    , _piece(nullptr) {
}

Square::Square(SquareColor square_color, PieceType piece_type, PieceColor piece_color)
    : _color(square_color)
    , _piece(std::make_shared<Piece>(piece_type, piece_color)) {
}

std::string Square::GetPrintableString() const {
    if (_piece != nullptr) {
        return _piece->GetPrintableString();
    }
    return ".";
}

void Square::SwapPieces(Square& square) {
    std::swap(_piece, square._piece);
}

}
