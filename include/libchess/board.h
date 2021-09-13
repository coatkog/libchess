#pragma once

#include "libchess/move.h"
#include "libchess/square.h"

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace libchess {

class Board {
  public:
    using BoardMatrix = std::array<std::array<Square, 8>, 8>;

    Board();

    static std::string GetFen();

    [[nodiscard]] BoardMatrix GetBoard() const;

    std::vector<Move> GetAvailableMoves(int starting_x, int starting_y);

    void GetAvailableMovesPawn(const Square& starting_square,
                               std::vector<Move>& available_moves,
                               int starting_x,
                               int starting_y);
    void GetAvailableMovesKnight(std::vector<Move>& available_moves,
                                 int starting_x,
                                 int starting_y);
    void GetAvailableMovesBishop(std::vector<Move>& available_moves,
                                 int starting_x,
                                 int starting_y);
    void GetAvailableMovesRook(std::vector<Move>& available_moves, int starting_x, int starting_y);
    void GetAvailableMovesQueen(std::vector<Move>& available_moves, int starting_x, int starting_y);
    void GetAvailableMovesKing(std::vector<Move>& available_moves, int starting_x, int starting_y);

    void DoMove(const std::string& move_str);
    void DoMove(int starting_x, int starting_y, int ending_x, int ending_y);

    [[nodiscard]] std::string ToString() const;

  private:
    static const BoardMatrix kStartingBoard;

    BoardMatrix m_board;
    bool m_white_to_move;

    std::vector<Move> m_move_history;

    void ValidateMove(const Move& move);
    void DoMove(const Move& move);

    void CheckPossibleMovePawn(std::vector<Move>& available_moves,
                               Move&& move,
                               bool is_diagonal_move);
    bool CheckPossibleMove(std::vector<Move>& available_moves, Move&& move);

    Square& GetStartingSquare(const Move& move);
    Square& GetEndingSquare(const Move& move);
};

}
