#include "libchess/square.h"

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

void Square::SwapPieces(Square& square) {
    // TODO: Should this be here?
    if (!square.Empty()) {
        square._piece = nullptr;
    }

    std::swap(_piece, square._piece);
}

SquareColor Square::GetColor() const {
    return _color;
}

PieceColor Square::GetPieceColor() const {
    if (!_piece) {
        // TODO: throw exception
    }

    return _piece->GetColor();
}

PieceType Square::GetPieceType() const {
    if (_piece) {
        // TODO: throw exception
    }

    return _piece->GetType();
}

bool Square::Empty() const {
    return _piece == nullptr;
}

std::string Square::ToString() const {
    if (_piece != nullptr) {
        return _piece->ToString();
    }
    return ".";
}

}
