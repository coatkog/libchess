#pragma once

#include "libchess/board_rep.h"
#include "libchess/board_state.h"
#include "libchess/move.h"
#include "libchess/square.h"

#include <string>
#include <vector>

namespace libchess {

class board {
  public:
    board();

    static std::string get_fen();

    [[nodiscard]] const square& get_square(std::size_t x, std::size_t y) const;

    [[nodiscard]] std::string to_string() const;

    std::vector<move> get_available_moves(int starting_x, int starting_y);

    void do_move(const std::string& move_str);
    void do_move(int starting_x, int starting_y, int ending_x, int ending_y);

  private:
    board_state m_board_state {};
    board_rep m_board_rep;

    std::vector<move> m_move_history;

    void do_move(const move& move);
};

}
