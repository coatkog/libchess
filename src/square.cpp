#include "libchess/square.h"

namespace libchess {

square::square(color color)
    : m_color(color)
    , m_piece(piece::type::none, piece::color::white) {
}

void square::set_piece(piece piece) {
    m_piece = piece;
}

square::color square::get_color() const {
    return m_color;
}

piece square::get_piece() const {
    return m_piece;
}

bool square::empty() const {
    return m_piece.get_type() == piece::type::none;
}

std::string square::to_string() const {
    return m_piece.to_string();
}

}
