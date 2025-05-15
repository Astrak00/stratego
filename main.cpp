#include "stratego-lib/board.hpp"

#include <iostream>
#include <thread>

int main() {
  // Create a board
  Board board;
  int i, j;
  for (i = 0; i < BOARD_SIZE; ++i) {
    for (j = 0; j < 2; ++j) {
      board.placePiece(j, i, Piece(PieceType::GENERAL, PieceColor::BLUE));
      board.revealPiece(j, i);
    }
  }

  for (i = 0; i < BOARD_SIZE; ++i) {
    for (j = BOARD_SIZE - 2; j < BOARD_SIZE; ++j) {
      board.placePiece(j, i, Piece(PieceType::GENERAL, PieceColor::RED));
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

  // Attempting to move a piece to an occupied position
  std::cout << "Attempting to move a piece from (0, 0) to (1, 0)): ";
  if (board.move(0, 0, 1, 0)) {
    std::cout << "Move successful." << std::endl;
  } else {
    std::cout << "Move failed." << std::endl;
  }

  // Attempting to move a piece to an occupied position
  std::cout << "Attempting to move a piece from (0, 0) to (1, 1): ";
  if (board.move(0, 0, 1, 1)) {
    std::cout << "Move successful." << std::endl;
  } else {
    std::cout << "Move failed." << std::endl;
  }

  std::cout << std::endl << std::endl;

  // Move the piece until it reaches the end of the board
  std::pair<int, int> piece_coordinates = {2, 1};
  std::cout << "Moving a piece from (2, 1) to (10, 1) bit by bit: \n";
  for (int k = 1; k < 13; ++k) {
    std::cout << "Moving from (" << piece_coordinates.first << ", " << piece_coordinates.second
              << ") to (" << piece_coordinates.first + 1 << ", " << piece_coordinates.second << ")"
              << std::endl;
    bool result = board.move(piece_coordinates.first, piece_coordinates.second,
                             piece_coordinates.first + 1, piece_coordinates.second);
    if (result) {
      piece_coordinates.first++;
      board.printBoard();
    } else {
      std::cout << "Move failed." << std::endl;
    }
  }

  std::cout << "Start mooving to the right" << std::endl;
  // Move the piece until it reaches the end of the board
  for (int k = 1; k < BOARD_SIZE - 1; ++k) {
    bool result = board.move(piece_coordinates.first, piece_coordinates.second,
                             piece_coordinates.first, piece_coordinates.second + 1);
    if (result) {
      piece_coordinates.second++;
      board.printBoard();
    } else {
      std::cout << "Move failed." << std::endl;
      break;
    }
  }

  return 0;
}
