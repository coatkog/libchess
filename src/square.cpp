#include "libchess/square.h"

namespace libchess {

Square::Square(SquareColor square_color)
    : m_color(square_color)
    , m_piece(nullptr) {
}

Square::Square(SquareColor square_color, PieceType piece_type, PieceColor piece_color)
    : m_color(square_color)
    , m_piece(std::make_shared<Piece>(piece_type, piece_color)) {
}

void Square::SwapPieces(Square& square) {
    // TODO: Should this be here?
    if (m_piece != nullptr) {
        m_piece->SetFirstMove(false);
    }

    // TODO: Should this be here?
    if (!square.Empty()) {
        square.m_piece = nullptr;
    }

    std::swap(m_piece, square.m_piece);
}

SquareColor Square::GetColor() const {
    return m_color;
}

PieceColor Square::GetPieceColor() const {
    if (m_piece == nullptr) {
        // TODO: throw exception
    }

    return m_piece->GetColor();
}

PieceType Square::GetPieceType() const {
    if (m_piece == nullptr) {
        // TODO: throw exception
    }

    return m_piece->GetType();
}

bool Square::Empty() const {
    return m_piece == nullptr;
}

bool Square::IsPieceFirstMove() const {
    if (m_piece == nullptr) {
        return false;
    }

    return m_piece->GetFirstMove();
}

std::string Square::ToString() const {
    if (m_piece != nullptr) {
        return m_piece->ToString();
    }
    return ".";
}

}
