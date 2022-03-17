#include "libchess/piece.h"

namespace libchess {

piece::piece(type piece_type, color piece_color)
    : m_type(piece_type)
    , m_color(piece_color) {
}

piece::type piece::get_type() const {
    return m_type;
}

piece::color piece::get_color() const {
    return m_color;
}

std::string piece::to_string() const {
    switch (m_color) {
        case color::black: {
            switch (m_type) {
                case type::none:
                    return " ";
                case type::pawn:
                    return "p";
                case type::knight:
                    return "n";
                case type::bishop:
                    return "b";
                case type::rook:
                    return "r";
                case type::queen:
                    return "q";
                case type::king:
                    return "k";
            }
            break;
        }
        case color::white: {
            switch (m_type) {
                case type::none:
                    return " ";
                case type::pawn:
                    return "P";
                case type::knight:
                    return "N";
                case type::bishop:
                    return "B";
                case type::rook:
                    return "R";
                case type::queen:
                    return "Q";
                case type::king:
                    return "K";
            }
            break;
        }
    };
    return "";
}

}
