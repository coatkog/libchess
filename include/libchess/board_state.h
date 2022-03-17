#pragma once

#include "libchess/move.h"
#include "libchess/piece.h"

#include <bitset>
#include <cstdint>
#include <string>
#include <vector>

namespace libchess {

class board_state {
  public:
    board_state();

    [[nodiscard]] piece get_piece(std::size_t x, std::size_t y) const;

    [[nodiscard]] bool validate_move(const move& move) const;

    [[nodiscard]] std::vector<move> get_available_moves(std::size_t x, std::size_t y) const;

    void do_move(const move& move);

  private:
    std::uint64_t m_position;

    std::uint64_t m_position_white;
    std::uint64_t m_position_white_pawns;
    std::uint64_t m_position_white_knights;
    std::uint64_t m_position_white_bishops;
    std::uint64_t m_position_white_rooks;
    std::uint64_t m_position_white_queen;
    std::uint64_t m_position_white_king;

    std::uint64_t m_position_black;
    std::uint64_t m_position_black_pawns;
    std::uint64_t m_position_black_knights;
    std::uint64_t m_position_black_bishops;
    std::uint64_t m_position_black_rooks;
    std::uint64_t m_position_black_queen;
    std::uint64_t m_position_black_king;

    bool m_white_to_move = true;

    static inline std::uint64_t index(std::size_t x, std::size_t y) {
        return static_cast<std::uint64_t>(1) << (63 - x - y * 8);
    };

    static inline std::pair<std::size_t, std::size_t> coords(std::uint64_t index) {
        std::size_t pos = 63;
        while (index != 1) { // TODO: Can be optimized
            pos--;
            index >>= 1;
        }
        return std::make_pair(pos % 8, pos / 8);
    };

    static inline bool is_set(std::uint64_t bitboard, std::uint64_t index) {
        return (bitboard & index) != 0;
    };

    static inline bool is_unset(std::uint64_t bitboard, std::uint64_t index) {
        return (~bitboard & index) != 0;
    };

    static inline void set(std::uint64_t& bitboard, std::uint64_t index) {
        bitboard |= index;
    }

    static inline void reset(std::uint64_t& bitboard, std::uint64_t index) {
        bitboard &= ~index;
    }

    static inline void reset_n_set(std::uint64_t& bitboard,
                                   std::uint64_t reset_index,
                                   std::uint64_t set_index) {
        reset(bitboard, reset_index);
        set(bitboard, set_index);
    }

    [[nodiscard]] piece get_piece(std::uint64_t index) const;

    [[nodiscard]] std::vector<move> get_available_moves(std::uint64_t index) const;

    void get_available_moves_pawn_white(std::vector<move>& available_moves,
                                        std::uint64_t index) const;
    void get_available_moves_pawn_black(std::vector<move>& available_moves,
                                        std::uint64_t index) const;
    void get_available_moves_knight(std::vector<move>& available_moves, std::uint64_t index) const;
    void get_available_moves_bishop(std::vector<move>& available_moves, std::uint64_t index) const;
    void get_available_moves_rook(std::vector<move>& available_moves, std::uint64_t index) const;
    void get_available_moves_queen(std::vector<move>& available_moves, std::uint64_t index) const;
    void get_available_moves_king(std::vector<move>& available_moves, std::uint64_t index) const;

    static constexpr std::uint64_t k_start_position_white = 0x000000000000ffff;
    static constexpr std::uint64_t k_start_position_white_pawns = 0x000000000000ff00;
    static constexpr std::uint64_t k_start_position_white_knights = 0x0000000000000042;
    static constexpr std::uint64_t k_start_position_white_bishops = 0x0000000000000024;
    static constexpr std::uint64_t k_start_position_white_rooks = 0x0000000000000081;
    static constexpr std::uint64_t k_start_position_white_queen = 0x0000000000000010;
    static constexpr std::uint64_t k_start_position_white_king = 0x0000000000000008;

    static constexpr std::uint64_t k_start_position_black = 0xffff000000000000;
    static constexpr std::uint64_t k_start_position_black_pawns = 0x00ff000000000000;
    static constexpr std::uint64_t k_start_position_black_knights = 0x4200000000000000;
    static constexpr std::uint64_t k_start_position_black_bishops = 0x2400000000000000;
    static constexpr std::uint64_t k_start_position_black_rooks = 0x8100000000000000;
    static constexpr std::uint64_t k_start_position_black_queen = 0x1000000000000000;
    static constexpr std::uint64_t k_start_position_black_king = 0x0800000000000000;
};

}
