#include "stratego-lib/board.hpp"

#include <iostream>

int main()
{
  // Create a board
  Board board;

  Piece redFlag(PieceType::FLAG, PieceColor::RED);
  board.placePiece(0, 0, redFlag);
  board.printBoard();

  board.revealPiece(0, 0);
  std::cout << "After revealing:" << std::endl;
  board.printBoard();
  std::cout << "Is (0, 0) occupied? " << (board.isOccupied(0, 0) ? "Yes" : "No") << std::endl;
  std::cout << "Is (0, 1) occupied? " << (board.isOccupied(0, 1) ? "Yes" : "No") << std::endl;
  std::cout << "Is (0, 0) revealed? " << (board.isRevealed(0, 0) ? "Yes" : "No") << std::endl;
  std::cout << "Is (0, 1) revealed? " << (board.isRevealed(0, 1) ? "Yes" : "No") << std::endl;
  std::cout << "Surrounding pieces of (0, 0):" << std::endl;
  auto surroundingPieces = board.getSurroundingPieces(0, 1);
  for (auto const &piece : surroundingPieces)
  {
    std::cout << piece << " ";
  }
  std::cout << std::endl;

  Piece blueScout(PieceType::SCOUT, PieceColor::BLUE);
  board.placePiece(1, 0, blueScout);
  board.revealPiece(1, 0);

  Piece blueFlag(PieceType::FLAG, PieceColor::BLUE);
  // Place it at the bottom right corner
  board.placePiece(BOARD_SIZE - 1, BOARD_SIZE - 1, blueFlag);
  board.revealPiece(BOARD_SIZE - 1, BOARD_SIZE - 1);
  std::cout << "After placing blue flag:" << std::endl;
  board.printBoard();

  return 0;
}
