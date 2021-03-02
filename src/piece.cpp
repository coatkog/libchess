#include "libchess/piece.h"

namespace libchess {

Piece::Piece(PieceType piece_type, PieceColor piece_color)
    : _type(piece_type)
    , _color(piece_color) {}

std::string Piece::GetPrintableString() const {
    switch (_color) {
        case PieceColor::BLACK: {
            switch (_type) {
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
            switch (_type) {
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
