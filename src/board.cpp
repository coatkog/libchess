#include "libchess/board.h"
#include "libchess/piece.h"

#include <sstream>
#include <stdexcept>

namespace libchess {

Board::Board()
    : _board(Board::kStartingBoard)
    , _white_to_move(true) {
}

std::string Board::GetFen() {
    return "fen";
}

Board::BoardMatrix Board::GetBoard() const {
    return _board;
}

std::vector<Move> Board::GetAvailableMoves(int starting_x, int starting_y) {
    std::vector<Move> available_moves;

    // TODO: Should this be checked here?
    if (starting_x < 0 || starting_x > 8 || starting_y < 0 || starting_y > 8) {
        return available_moves;
    }

    const Square& starting_square = _board[starting_y][starting_x];

    // TODO: Should this be checked here?
    if (starting_square.Empty()) {
        return available_moves;
    }

    switch (starting_square.GetPieceType()) {
        case PieceType::PAWN:
            GetAvailableMovesPawn(starting_square, available_moves, starting_x, starting_y);
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

void Board::GetAvailableMovesPawn(const Square& starting_square,
                                  std::vector<Move>& available_moves,
                                  int starting_x,
                                  int starting_y) {
    // TODO: Taking, after first move, en passant, promotion
    switch (starting_square.GetPieceColor()) {
        case PieceColor::WHITE:
            available_moves.emplace_back(starting_x, starting_y, starting_x, starting_y - 1);
            available_moves.emplace_back(starting_x, starting_y, starting_x, starting_y - 2);
            break;
        case PieceColor::BLACK:
            available_moves.emplace_back(starting_x, starting_y, starting_x, starting_y + 1);
            available_moves.emplace_back(starting_x, starting_y, starting_x, starting_y + 2);
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
    // TODO: Castling
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

bool Board::CheckPossibleMove(std::vector<Move>& available_moves, const Move& move) {
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

    GetStartingSquare(move).SwapPieces(GetEndingSquare(move));

    _white_to_move = !_white_to_move;

    _move_history.push_back(move);
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

    if (_white_to_move && starting_square.GetPieceColor() == PieceColor::BLACK) {
        throw std::runtime_error("White to move.");
    }

    if (!_white_to_move && starting_square.GetPieceColor() == PieceColor::WHITE) {
        throw std::runtime_error("Black to move.");
    }
}

std::string Board::ToString() const {
    std::stringstream printable_board;

    printable_board << "  ABCDEFGH\n";

    for (std::size_t i = 0; i < 8; i++) {
        printable_board << 8 - i << " ";
        for (std::size_t j = 0; j < 8; j++) {
            printable_board << _board[i][j].ToString();
        }
        printable_board << "\n";
    }

    return printable_board.str();
}

Square& Board::GetStartingSquare(const Move& move) {
    return _board[move.GetStartingY()][move.GetStartingX()];
}

Square& Board::GetEndingSquare(const Move& move) {
    return _board[move.GetEndingY()][move.GetEndingX()];
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
