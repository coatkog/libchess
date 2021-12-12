#include "libchess/piece.h"

namespace libchess {

Piece::Piece(PieceType piece_type, PieceColor piece_color)
    : m_type(piece_type)
    , m_color(piece_color)
    , m_moved(false) {
}

PieceType Piece::GetType() const {
    return m_type;
}

PieceColor Piece::GetColor() const {
    return m_color;
}

bool Piece::GetMoved() const {
    return m_moved;
}

void Piece::SetMoved(bool moved) {
    m_moved = moved;
}

std::string Piece::ToString() const {
    switch (m_color) {
        case PieceColor::BLACK: {
            switch (m_type) {
                case PieceType::PAWN:
                    return "p";
                case PieceType::KNIGHT:
                    return "n";
                case PieceType::BISHOP:
                    return "b";
                case PieceType::ROOK:
                    return "r";
                case PieceType::QUEEN:
                    return "q";
                case PieceType::KING:
                    return "k";
            }
            break;
        }
        case PieceColor::WHITE: {
            switch (m_type) {
                case PieceType::PAWN:
                    return "P";
                case PieceType::KNIGHT:
                    return "N";
                case PieceType::BISHOP:
                    return "B";
                case PieceType::ROOK:
                    return "R";
                case PieceType::QUEEN:
                    return "Q";
                case PieceType::KING:
                    return "K";
            }
            break;
        }
    };
    return "";
}

}
