#include "stratego-lib/board.hpp"

#include <iostream>

int main() {
  // Create a board
  Board board;
  int i = 0;
  for (i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < 2; ++j) {
      board.placePiece(i, j, Piece(PieceType::EMPTY, PieceColor::BLUE));
      board.revealPiece(0, i);
    }

    board.printBoard();

    return 0;
  }
}
