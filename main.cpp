#include "stratego-lib/board.hpp"

#include <iostream>

int main() {
  // Create a board
  Board board;
  int i, j;
  for (i = 0; i < BOARD_SIZE; ++i) {
    for (j = 0; j < 2; ++j) {
      board.placePiece(j, i, Piece(PieceType::MARSHAL, PieceColor::BLUE));
      board.revealPiece(j, i);
    }
  }

  for (i = 0; i < BOARD_SIZE; ++i) {
    for (j = BOARD_SIZE - 2; j < BOARD_SIZE; ++j) {
      board.placePiece(j, i, Piece(PieceType::MARSHAL, PieceColor::RED));
      board.revealPiece(j, i);
    }
  }

  // Print the board
  std::cout << "Initial Board:" << std::endl;
  board.printBoard();

  // Moving a valid piece: row, column, new row, new column
  std::cout << "Moving a piece from (1, 1) to (2, 1): ";
  if (board.move(1, 1, 2, 1)) {
    std::cout << "Move successful." << std::endl;
  } else {
    std::cout << "Move failed." << std::endl;
  }
  // Print the board after the move
  std::cout << "Board after move:" << std::endl;
  board.printBoard();
  

  return 0;
}
