#include "libchess/board.h"
#include "libchess/piece.h"

#include <algorithm>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace libchess {

Board::Board()
    : m_board(Board::kStartingBoard)
    , m_white_to_move(true) {
}

std::string Board::GetFen() {
    return "fen";
}

Board::BoardMatrix Board::GetBoard() const {
    return m_board;
}

std::vector<Move> Board::GetAvailableMoves(int starting_x, int starting_y) {
    std::vector<Move> available_moves;

    // TODO: Should this be checked here?
    if (starting_x < 0 || starting_x > 8 || starting_y < 0 || starting_y > 8) {
        return available_moves;
    }

    const Square& starting_square = m_board[starting_y][starting_x];

    // TODO: Should this be checked here?
    if (starting_square.Empty()) {
        return available_moves;
    }

    switch (starting_square.GetPieceType()) {
        case PieceType::PAWN:
            GetAvailableMovesPawn(available_moves, starting_x, starting_y);
            break;
        case PieceType::KNIGHT:
            GetAvailableMovesKnight(available_moves, starting_x, starting_y);
            break;
        case PieceType::BISHOP:
            GetAvailableMovesBishop(available_moves, starting_x, starting_y);
            break;
        case PieceType::ROOK:
            GetAvailableMovesRook(available_moves, starting_x, starting_y);
            break;
        case PieceType::QUEEN:
            GetAvailableMovesQueen(available_moves, starting_x, starting_y);
            break;
        case PieceType::KING:
            GetAvailableMovesKing(available_moves, starting_x, starting_y);
            break;
    }

    return available_moves;
}

void Board::GetAvailableMovesPawn(std::vector<Move>& available_moves,
                                  int starting_x,
                                  int starting_y) {
    const Square& starting_square = m_board[starting_y][starting_x];

    // TODO: En passant, promotion
    switch (starting_square.GetPieceColor()) {
        case PieceColor::WHITE:
            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x, starting_y - 1),
                                  false);

            if (!starting_square.DidPieceMove()) {
                CheckPossibleMovePawn(available_moves,
                                      Move(starting_x, starting_y, starting_x, starting_y - 2),
                                      false);
            }

            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x - 1, starting_y - 1),
                                  true);
            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x + 1, starting_y - 1),
                                  true);
            break;
        case PieceColor::BLACK:
            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x, starting_y + 1),
                                  false);

            if (!starting_square.DidPieceMove()) {
                CheckPossibleMovePawn(available_moves,
                                      Move(starting_x, starting_y, starting_x, starting_y + 2),
                                      false);
            }

            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x - 1, starting_y + 1),
                                  true);
            CheckPossibleMovePawn(available_moves,
                                  Move(starting_x, starting_y, starting_x - 1, starting_y + 1),
                                  true);
            break;
    }
}

void Board::GetAvailableMovesKnight(std::vector<Move>& available_moves,
                                    int starting_x,
                                    int starting_y) {
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 2, starting_y - 1));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 1, starting_y - 2));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 1, starting_y - 2));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 2, starting_y - 1));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 2, starting_y + 1));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 1, starting_y + 2));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 1, starting_y + 2));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 2, starting_y + 1));
}

void Board::GetAvailableMovesBishop(std::vector<Move>& available_moves,
                                    int starting_x,
                                    int starting_y) {
    // Top left direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x - i, starting_y - i));
        if (!keep_going) {
            break;
        }
    }

    // Top right direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x + i, starting_y - i));
        if (!keep_going) {
            break;
        }
    }

    // Bottom right direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x - i, starting_y + i));
        if (!keep_going) {
            break;
        }
    }

    // Bottom right direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x + i, starting_y + i));
        if (!keep_going) {
            break;
        }
    }
}

void Board::GetAvailableMovesRook(std::vector<Move>& available_moves,
                                  int starting_x,
                                  int starting_y) {
    // Top direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x - i, starting_y));
        if (!keep_going) {
            break;
        }
    }

    // Bottom direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x + i, starting_y));
        if (!keep_going) {
            break;
        }
    }

    // Left direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x, starting_y - i));
        if (!keep_going) {
            break;
        }
    }

    // Right direction
    for (int i = 1; i < 8; i++) {
        bool keep_going =
            CheckPossibleMove(available_moves,
                              Move(starting_x, starting_y, starting_x, starting_y + i));
        if (!keep_going) {
            break;
        }
    }
}

void Board::GetAvailableMovesQueen(std::vector<Move>& available_moves,
                                   int starting_x,
                                   int starting_y) {
    GetAvailableMovesBishop(available_moves, starting_x, starting_y);
    GetAvailableMovesRook(available_moves, starting_x, starting_y);
}

void Board::GetAvailableMovesKing(std::vector<Move>& available_moves,
                                  int starting_x,
                                  int starting_y) {
    CheckPossibleMoveShortCastle(available_moves, starting_x, starting_y);
    CheckPossibleMoveLongCastle(available_moves, starting_x, starting_y);

    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 1, starting_y - 1));
    CheckPossibleMove(available_moves, Move(starting_x, starting_y, starting_x - 1, starting_y));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x - 1, starting_y + 1));
    CheckPossibleMove(available_moves, Move(starting_x, starting_y, starting_x, starting_y - 1));
    CheckPossibleMove(available_moves, Move(starting_x, starting_y, starting_x, starting_y + 1));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 1, starting_y - 1));
    CheckPossibleMove(available_moves, Move(starting_x, starting_y, starting_x + 1, starting_y));
    CheckPossibleMove(available_moves,
                      Move(starting_x, starting_y, starting_x + 1, starting_y + 1));
}

void Board::CheckPossibleMovePawn(std::vector<Move>& available_moves,
                                  Move&& move,
                                  bool is_diagonal_move) {
    if (!move.Valid()) {
        return;
    }

    const Square& starting_square = GetStartingSquare(move);
    const Square& end_square = GetEndingSquare(move);

    if (is_diagonal_move) {
        if (!end_square.Empty()) {
            if (end_square.GetPieceColor() == starting_square.GetPieceColor()) {
                return;
            }
        } else {
            return;
        }
    } else {
        if (!end_square.Empty()) {
            return;
        }
    }

    // TODO: This ok?
    available_moves.emplace_back(move);
}

void Board::CheckPossibleMoveShortCastle(std::vector<Move>& available_moves,
                                         int starting_x,
                                         int starting_y) {
    // Checking if the king moved is sufficient
    // Since if the king moves back to the initial position, he still moved
    if (!GetStartingSquare(starting_x, starting_y).DidPieceMove()) {
        if (!GetStartingSquare(starting_x + 1, starting_y).Empty()) {
            return;
        }

        if (!GetStartingSquare(starting_x + 2, starting_y).Empty()) {
            return;
        }

        const Square& right_rook_square = GetStartingSquare(starting_x + 3, starting_y);

        // Same logic for checking as for the king
        if (!right_rook_square.Empty() && !right_rook_square.DidPieceMove()) {
            available_moves.emplace_back(starting_x, starting_y, starting_x + 2, starting_y);
        }
    }
}

void Board::CheckPossibleMoveLongCastle(std::vector<Move>& available_moves,
                                        int starting_x,
                                        int starting_y) {
    // Checking if the king moved is sufficient
    // Since if the king moves back to the initial position, he still moved
    if (!GetStartingSquare(starting_x, starting_y).DidPieceMove()) {
        if (!GetStartingSquare(starting_x - 1, starting_y).Empty()) {
            return;
        }

        if (!GetStartingSquare(starting_x - 2, starting_y).Empty()) {
            return;
        }

        if (!GetStartingSquare(starting_x - 3, starting_y).Empty()) {
            return;
        }

        const Square& left_rook_square = GetStartingSquare(starting_x - 4, starting_y);

        // Same logic for checking as for the king
        if (!left_rook_square.Empty() && !left_rook_square.DidPieceMove()) {
            available_moves.emplace_back(starting_x, starting_y, starting_x - 2, starting_y);
        }
    }
}

bool Board::CheckPossibleMove(std::vector<Move>& available_moves, Move&& move) {
    if (!move.Valid()) {
        return false;
    }

    const Square& starting_square = GetStartingSquare(move);
    const Square& end_square = GetEndingSquare(move);

    bool keep_going = true;

    if (!end_square.Empty()) {
        if (end_square.GetPieceColor() == starting_square.GetPieceColor()) {
            return false;
        }

        keep_going = false;
    }

    // TODO: This ok?
    available_moves.emplace_back(move);

    return keep_going;
}

void Board::DoMove(const std::string& move_str) {
    DoMove(Move(move_str));
}

void Board::DoMove(int starting_x, int starting_y, int ending_x, int ending_y) {
    DoMove(Move(starting_x, starting_y, ending_x, ending_y));
}

void Board::DoMove(const Move& move) {
    ValidateMove(move);

    Square& starting_square = GetStartingSquare(move);

    // Check if the move is castling and do the rook move
    if (starting_square.GetPieceType() == PieceType::KING) {
        std::unique_ptr<Move> rook_move;
        int y = starting_square.GetPieceColor() == PieceColor::WHITE ? 7 : 0;

        if (move.IsShortCastle()) {
            rook_move = std::make_unique<Move>(7, y, 5, y);
        }

        if (move.IsLongCastle()) {
            rook_move = std::make_unique<Move>(0, y, 3, y);
        }

        if (rook_move) {
            GetStartingSquare(*rook_move).SwapPieces(GetEndingSquare(*rook_move));
        }
    }

    starting_square.SwapPieces(GetEndingSquare(move));

    m_white_to_move = !m_white_to_move;

    m_move_history.push_back(move);
}

void Board::ValidateMove(const Move& move) {
    if (!move.Valid()) {
        throw std::runtime_error("Invalid move.");
    }

    if (move.GetStartingX() == move.GetEndingX() && move.GetStartingY() == move.GetEndingY()) {
        throw std::runtime_error("No move.");
    }

    const Square& starting_square = GetStartingSquare(move);

    if (starting_square.Empty()) {
        throw std::runtime_error("No piece to move.");
    }

    if (m_white_to_move && starting_square.GetPieceColor() == PieceColor::BLACK) {
        throw std::runtime_error("White to move.");
    }

    if (!m_white_to_move && starting_square.GetPieceColor() == PieceColor::WHITE) {
        throw std::runtime_error("Black to move.");
    }

    std::vector<Move> available_moves = GetAvailableMoves(move.GetStartingX(), move.GetStartingY());
    if (std::find_if(available_moves.begin(),
                     available_moves.end(),
                     [&move](const Move& available_move) {
                         return move.Compare(available_move);
                     }) == available_moves.end()) {
        throw std::runtime_error("Invalid move.");
    }
}

std::string Board::ToString() const {
    std::stringstream printable_board;

    printable_board << "  ABCDEFGH\n";

    for (std::size_t i = 0; i < 8; i++) {
        printable_board << 8 - i << " ";
        for (std::size_t j = 0; j < 8; j++) {
            printable_board << m_board[i][j].ToString();
        }
        printable_board << "\n";
    }

    return printable_board.str();
}

Square& Board::GetStartingSquare(int starting_x, int starting_y) {
    return m_board[starting_y][starting_x];
}

Square& Board::GetStartingSquare(const Move& move) {
    return m_board[move.GetStartingY()][move.GetStartingX()];
}

Square& Board::GetEndingSquare(const Move& move) {
    return m_board[move.GetEndingY()][move.GetEndingX()];
}

const Board::BoardMatrix Board::kStartingBoard = {
    { { Square(SquareColor::WHITE, PieceType::ROOK, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::KNIGHT, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::BISHOP, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::QUEEN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::KING, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::BISHOP, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::KNIGHT, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::ROOK, PieceColor::BLACK) },

      { Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK) },

      { Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK) },

      { Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE) },

      { Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK) },

      { Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE) },

      { Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE) },

      { Square(SquareColor::BLACK, PieceType::ROOK, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::KNIGHT, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::BISHOP, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::QUEEN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::KING, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::BISHOP, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::KNIGHT, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::ROOK, PieceColor::WHITE) } }
};

}
