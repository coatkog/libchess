#include "libchess/board.h"
#include "libchess/internal/log.h"
#include "libchess/piece.h"

#include <sstream>

namespace libchess {

board::board()
    : m_board_rep(m_board_state) {
}

std::string board::get_fen() {
    return "fen";
}

const square& board::get_square(std::size_t x, std::size_t y) const {
    return m_board_rep.get_square(x, y);
}

std::string board::to_string() const {
    return m_board_rep.to_string();
}

void board::do_move(const std::string& move_str) {
    do_move(move(move_str));
}

void board::do_move(int starting_x, int starting_y, int ending_x, int ending_y) {
    do_move(move(starting_x, starting_y, ending_x, ending_y));
}

void board::do_move(const move& move) {
    info("Received move [{}]", move.to_string());

    // TODO: Test if the move is valid?

    if (!m_board_state.validate_move(move)) {
        error("Invalid move [{}]", move.to_string());
        return;
    }

    m_board_state.do_move(move);
    m_board_rep.update(m_board_state);

    m_move_history.push_back(move);
}

std::vector<move> board::get_available_moves(int starting_x, int starting_y) {
    std::vector<move> moves = m_board_state.get_available_moves(starting_x, starting_y);

    std::stringstream ss;
    for (const auto& move : moves) {
        ss << move.to_string() << ' ';
    }
    info("Available moves: {}", ss.str());

    return moves;
}

}
