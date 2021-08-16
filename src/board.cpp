#include "libchess/board.h"

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

void Board::DoMove(const Move& move) {
    ValidateMove(move);

    _board[move.GetStartingX()][move.GetStartingY()].SwapPieces(
        _board[move.GetEndingX()][move.GetEndingY()]);

    _white_to_move = !_white_to_move;
}

void Board::ValidateMove(const Move& move) {
    const Square& starting_square = _board[move.GetStartingX()][move.GetStartingY()];

    if (!starting_square.ContainsPiece()) {
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

    for (std::size_t i = 0; i < kBoardWidth; i++) {
        printable_board << kBoardWidth - i << " ";
        for (std::size_t j = 0; j < kBoardHeight; j++) {
            printable_board << _board[i][j].ToString();
        }
        printable_board << "\n";
    }

    return printable_board.str();
}

const Board::BoardMatrix Board::kStartingBoard = {
    { { Square(SquareColor::BLACK, PieceType::ROOK, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::KNIGHT, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::BISHOP, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::QUEEN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::KING, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::BISHOP, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::KNIGHT, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::ROOK, PieceColor::BLACK) },

      { Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::BLACK),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::BLACK) },

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

      { Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK),
        Square(SquareColor::WHITE),
        Square(SquareColor::BLACK) },

      { Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::PAWN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::PAWN, PieceColor::WHITE) },

      { Square(SquareColor::WHITE, PieceType::ROOK, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::KNIGHT, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::BISHOP, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::QUEEN, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::KING, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::BISHOP, PieceColor::WHITE),
        Square(SquareColor::WHITE, PieceType::KNIGHT, PieceColor::WHITE),
        Square(SquareColor::BLACK, PieceType::ROOK, PieceColor::WHITE) } }
};

}
