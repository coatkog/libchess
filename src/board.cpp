#include "libchess/board.h"

#include <sstream>

namespace libchess {

Board::Board()
    : _board(Board::kStartingBoard) {
}

std::string Board::GetFen() {
    return "fen";
}

std::string Board::GetPrintableString() const {
    std::stringstream printable_board;

    printable_board << "  ABCDEFGH\n";

    for (std::size_t i = 0; i < kBoardWidth; i++) {
        printable_board << kBoardWidth - i << " ";
        for (std::size_t j = 0; j < kBoardHeight; j++) {
            printable_board << _board[i][j].GetPrintableString();
        }
        printable_board << "\n";
    }

    return printable_board.str();
}

void Board::DoMove(Move move) {
    _board[move.GetStartingX()][move.GetStartingY()].SwapPieces(
        _board[move.GetEndingX()][move.GetEndingY()]);
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
