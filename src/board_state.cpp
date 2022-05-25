#include "libchess/board_state.h"

#include "libchess/internal/log.h"
#include "libchess/internal/constants.h"
#include "libchess/move.h"

#include <algorithm>
#include <chrono>

namespace libchess {

board_state::board_state()
    : m_position(k_start_position_white | k_start_position_black)
    , m_position_white(k_start_position_white)
    , m_position_white_pawns(k_start_position_white_pawns)
    , m_position_white_knights(k_start_position_white_knights)
    , m_position_white_bishops(k_start_position_white_bishops)
    , m_position_white_rooks(k_start_position_white_rooks)
    , m_position_white_queen(k_start_position_white_queen)
    , m_position_white_king(k_start_position_white_king)
    , m_position_black(k_start_position_black)
    , m_position_black_pawns(k_start_position_black_pawns)
    , m_position_black_knights(k_start_position_black_knights)
    , m_position_black_bishops(k_start_position_black_bishops)
    , m_position_black_rooks(k_start_position_black_rooks)
    , m_position_black_queen(k_start_position_black_queen)
    , m_position_black_king(k_start_position_black_king) {
}

piece board_state::get_piece(std::size_t x, std::size_t y) const {
    return get_piece(bb_index(x, y));
}

piece board_state::get_piece(std::uint64_t bb_index) const {
    if (is_set(m_position, bb_index)) {
        if (is_set(m_position_white, bb_index)) {
            if (is_set(m_position_white_pawns, bb_index)) {
                return piece(piece::type::pawn, piece::color::white);
            }
            if (is_set(m_position_white_knights, bb_index)) {
                return piece(piece::type::knight, piece::color::white);
            }
            if (is_set(m_position_white_bishops, bb_index)) {
                return piece(piece::type::bishop, piece::color::white);
            }
            if (is_set(m_position_white_rooks, bb_index)) {
                return piece(piece::type::rook, piece::color::white);
            }
            if (is_set(m_position_white_queen, bb_index)) {
                return piece(piece::type::queen, piece::color::white);
            }
            if (is_set(m_position_white_king, bb_index)) {
                return piece(piece::type::king, piece::color::white);
            }
        } else if (is_set(m_position_black, bb_index)) {
            if (is_set(m_position_black_pawns, bb_index)) {
                return piece(piece::type::pawn, piece::color::black);
            }
            if (is_set(m_position_black_knights, bb_index)) {
                return piece(piece::type::knight, piece::color::black);
            }
            if (is_set(m_position_black_bishops, bb_index)) {
                return piece(piece::type::bishop, piece::color::black);
            }
            if (is_set(m_position_black_rooks, bb_index)) {
                return piece(piece::type::rook, piece::color::black);
            }
            if (is_set(m_position_black_queen, bb_index)) {
                return piece(piece::type::queen, piece::color::black);
            }
            if (is_set(m_position_black_king, bb_index)) {
                return piece(piece::type::king, piece::color::black);
            }
        }
    }

    return piece(piece::type::none, piece::color::white);
}

bool board_state::validate_move(const move& mv) const {
    std::size_t starting_bb_index = bb_index(mv.starting_x, mv.starting_y);
    std::size_t ending_bb_index = bb_index(mv.ending_x, mv.ending_y);

    if (starting_bb_index == ending_bb_index) {
        error("Invalid move: No move");
        return false;
    }

    if (is_unset(m_position_white, starting_bb_index) &&
        is_unset(m_position_black, starting_bb_index)) {
        error("Invalid move: No piece");
        return false;
    }

    // if (is_set(m_position_white, starting_index) && !m_white_to_move) {
    //     error("Invalid move: Black to move");
    //     return false;
    // }

    // if (is_set(m_position_black, starting_index) && m_white_to_move) {
    //     error("Invalid move: White to move");
    //     return false;
    // }

    std::vector<move> available_moves = get_available_moves(starting_bb_index);
    return std::any_of(available_moves.begin(),
                       available_moves.end(),
                       [&mv](const move& available_move) {
                           return mv == available_move;
                       });
}

std::vector<move> board_state::get_available_moves(std::size_t x, std::size_t y) const {
    return get_available_moves(bb_index(x, y));
}

std::vector<move> board_state::get_available_moves(std::uint64_t bb_index) const {
    auto start = std::chrono::steady_clock::now();

    std::vector<move> moves;

    piece piece = get_piece(bb_index);

    switch (piece.get_type()) {
        case piece::type::pawn:
            if (piece.get_color() == piece::color::white) {
                get_available_moves_pawn_white(moves, bb_index);
            } else {
                get_available_moves_pawn_black(moves, bb_index);
            }
            break;
        case piece::type::knight:
            get_available_moves_knight(
                moves,
                bb_index,
                piece.get_color() == piece::color::white ? m_position_white : m_position_black);
            break;
        case piece::type::bishop:
            get_available_moves_bishop(
                moves,
                bb_index,
                piece.get_color() == piece::color::white ? m_position_white : m_position_black);
            break;
        case piece::type::none:
            [[fallthrough]];
        default:
            return {};
    }

    auto end = std::chrono::steady_clock::now();

    debug(
        "Took [{}] μs to calculate available moves.",
        std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));

    return moves;
}

void board_state::get_available_moves_pawn_white(std::vector<move>& available_moves,
                                                 std::uint64_t bb_index) const {
    if (in_range(bb_index << 8) && is_unset(m_position, bb_index << 8)) {
        auto [x, y] = coords(bb_index);
        available_moves.emplace_back(x, y, x, y - 1);
    }
}

void board_state::get_available_moves_pawn_black(std::vector<move>& available_moves,
                                                 std::uint64_t bb_index) const {
    if (in_range(bb_index >> 8) && is_unset(m_position, bb_index >> 8)) {
        const auto [x, y] = coords(bb_index);
        available_moves.emplace_back(x, y, x, y + 1);
    }
}

void board_state::get_available_moves_knight(std::vector<move>& available_moves,
                                             std::uint64_t bb_index,
                                             std::uint64_t position) const {
    std::size_t pos = 63;
    while (bb_index != 1) { // TODO: Can be optimized
        pos--;
        bb_index >>= 1;
    }
    if (pos > 60) {
        std::uint64_t possible_moves = constants::knight_moves.at(pos).possible_moves;
        std::uint64_t available_moves = ~(~possible_moves | position);
        // TODO: Now extract coords from available_moves
    }

    if (in_range(bb_index << 10) && !is_set(position, bb_index << 10)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x - 2, y - 1)) {
            available_moves.emplace_back(x, y, x - 2, y - 1);
        }
    }

    if (in_range(bb_index << 17) && !is_set(position, bb_index << 17)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x - 1, y - 2)) {
            available_moves.emplace_back(x, y, x - 1, y - 2);
        }
    }

    if (in_range(bb_index << 15) && !is_set(position, bb_index << 15)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x + 1, y - 2)) {
            available_moves.emplace_back(x, y, x + 1, y - 2);
        }
    }

    if (in_range(bb_index << 6) && !is_set(position, bb_index << 6)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x + 2, y - 1)) {
            available_moves.emplace_back(x, y, x + 2, y - 1);
        }
    }

    if (in_range(bb_index >> 6) && !is_set(position, bb_index >> 6)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x - 2, y + 1)) {
            available_moves.emplace_back(x, y, x - 2, y + 1);
        }
    }

    if (in_range(bb_index >> 15) && !is_set(position, bb_index >> 15)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x - 1, y + 2)) {
            available_moves.emplace_back(x, y, x - 1, y + 2);
        }
    }

    if (in_range(bb_index >> 17) && !is_set(position, bb_index >> 17)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x + 1, y + 2)) {
            available_moves.emplace_back(x, y, x + 1, y + 2);
        }
    }

    if (in_range(bb_index >> 10) && !is_set(position, bb_index >> 10)) {
        const auto [x, y] = coords(bb_index);
        if (coords_in_range(x + 2, y + 1)) {
            available_moves.emplace_back(x, y, x + 2, y + 1);
        }
    }
}

void board_state::get_available_moves_bishop(std::vector<move>& available_moves,
                                             std::uint64_t bb_index,
                                             std::uint64_t position) const {
}

void board_state::get_available_moves_rook(std::vector<move>& available_moves,
                                           std::uint64_t bb_index) const {
}

void board_state::get_available_moves_queen(std::vector<move>& available_moves,
                                            std::uint64_t bb_index) const {
}

void board_state::get_available_moves_king(std::vector<move>& available_moves,
                                           std::uint64_t bb_index) const {
}

void board_state::do_move(const move& move) {
    std::size_t starting_bb_index = bb_index(move.starting_x, move.starting_y);
    std::size_t ending_bb_index = bb_index(move.ending_x, move.ending_y);

    // debug("Position before move: {}", std::bitset<64>(m_position).to_string());

    reset(m_position_white, ending_bb_index);
    reset(m_position_white_pawns, ending_bb_index);
    reset(m_position_white_knights, ending_bb_index);
    reset(m_position_white_bishops, ending_bb_index);
    reset(m_position_white_rooks, ending_bb_index);
    reset(m_position_white_queen, ending_bb_index);
    reset(m_position_white_king, ending_bb_index);
    reset(m_position_black, ending_bb_index);
    reset(m_position_black_pawns, ending_bb_index);
    reset(m_position_black_knights, ending_bb_index);
    reset(m_position_black_bishops, ending_bb_index);
    reset(m_position_black_rooks, ending_bb_index);
    reset(m_position_black_queen, ending_bb_index);
    reset(m_position_black_king, ending_bb_index);

    piece starting_piece = get_piece(starting_bb_index);

    // TODO: Can be optimized
    switch (starting_piece.get_color()) {
        case piece::color::white: {
            reset_n_set(m_position_white, starting_bb_index, ending_bb_index);
            switch (starting_piece.get_type()) {
                case piece::type::pawn:
                    reset_n_set(m_position_white_pawns, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::knight:
                    reset_n_set(m_position_white_knights, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::bishop:
                    reset_n_set(m_position_white_bishops, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::rook:
                    reset_n_set(m_position_white_rooks, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::queen:
                    reset_n_set(m_position_white_queen, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::king:
                    reset_n_set(m_position_white_king, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::none:
                default:
                    break;
            }
            break;
        }
        case piece::color::black:
            reset_n_set(m_position_black, starting_bb_index, ending_bb_index);
            switch (starting_piece.get_type()) {
                case piece::type::pawn:
                    reset_n_set(m_position_black_pawns, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::knight:
                    reset_n_set(m_position_black_knights, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::bishop:
                    reset_n_set(m_position_black_bishops, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::rook:
                    reset_n_set(m_position_black_rooks, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::queen:
                    reset_n_set(m_position_black_queen, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::king:
                    reset_n_set(m_position_black_king, starting_bb_index, ending_bb_index);
                    break;
                case piece::type::none:
                default:
                    break;
            }
            break;
    }

    m_position = m_position_white | m_position_black;

    // debug("Position after move:  {}", std::bitset<64>(m_position).to_string());

    m_white_to_move = !m_white_to_move;
}

}
