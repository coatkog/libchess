#include "libchess/board_rep.h"

#include <sstream>

namespace libchess {

board_rep::board_rep(const board_state& state)
    : m_rep(k_empty_rep) {
    update(state);
}

const square& board_rep::get_square(std::size_t x, std::size_t y) const {
    return m_rep[x][y];
}

void board_rep::update(const board_state& state) {
    for (std::size_t x = 0; x < 8; x++) {
        for (std::size_t y = 0; y < 8; y++) {
            m_rep[x][y].set_piece(state.get_piece(x, y));
        }
    }
}

std::string board_rep::to_string() const {
    std::stringstream ss;

    ss << "  ABCDEFGH\n";

    for (std::size_t y = 0; y < 8; y++) {
        ss << 8 - y << " ";
        for (std::size_t x = 0; x < 8; x++) {
            ss << get_square(x, y).to_string();
        }
        ss << "\n";
    }

    return ss.str();
}

const board_rep::rep board_rep::k_empty_rep = { { { square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black) },

                                                  { square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white) },

                                                  { square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black) },

                                                  { square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white) },

                                                  { square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black) },

                                                  { square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white) },

                                                  { square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black) },

                                                  { square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white),
                                                    square(square::color::black),
                                                    square(square::color::white) } } };

}
