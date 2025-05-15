#include <iostream>
#include <string>
#include <vector>

#ifndef STRATEGO_BOARD_HPP
  #define STRATEGO_BOARD_HPP
  #include "piece.hpp"

  #define BOARD_SIZE 12

struct Board {
    std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> grid;
    std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> revealed{};
    std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> occupied{};

    Board() : grid{}, revealed{}, occupied{} {
      // Initialize the board with a default layout or read from a file
      for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
          grid[i][j]     = Piece();  // Example initialization
          revealed[i][j] = false;
          occupied[i][j] = false;
        }
      }
    }

    void placePiece(int x, int y, Piece piece) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        grid[x][y]     = piece;
        occupied[x][y] = true;
      } else {
        std::cerr << "Invalid position to place piece." << std::endl;
      }
    }

    void removePiece(int x, int y) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        grid[x][y]     = Piece();  // Set to default piece to indicate empty
        occupied[x][y] = false;
      } else {
        std::cerr << "Invalid position to remove piece." << std::endl;
      }
    }

    void revealPiece(int x, int y) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        grid[x][y].reveal();
        revealed[x][y] = true;  // Update the revealed tracking array
      } else {
        std::cerr << "Invalid position to reveal piece." << std::endl;
      }
    }

    void hidePiece(int x, int y) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        revealed[x][y] = false;
      } else {
        std::cerr << "Invalid position to hide piece." << std::endl;
      }
    }

    void printBoard() {
      for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
          if (revealed[i][j]) {
            std::cout << grid[i][j] << "";
          } else {
            std::cout << " .";  // X for unrevealed pieces
          }
        }
        std::cout << std::endl;
      }
    }

    bool isOccupied(int x, int y) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        return occupied[x][y];
      } else {
        std::cerr << "Invalid position to check occupancy." << std::endl;
        return false;
      }
    }

    bool isRevealed(int x, int y) {
      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        return revealed[x][y];
      } else {
        std::cerr << "Invalid position to check revealed status." << std::endl;
        return false;
      }
    }

    void resetBoard() {
      for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
          grid[i][j]     = Piece();
          revealed[i][j] = false;
          occupied[i][j] = false;
        }
      }
    }

    void setGrid(std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> const & newGrid) {
      grid = newGrid;
      for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
          occupied[i][j] = (grid[i][j].type != PieceType::EMPTY);
        }
      }
    }

    // Get the pieces surrounding a given position orthogonally
    std::vector<Piece> getSurroundingPieces(int x, int y) {
      std::vector<Piece> surroundingPieces;
      if (x > 0 && revealed[x - 1][y]) {  // Up
        surroundingPieces.push_back(grid[x - 1][y]);
      }
      if (x < BOARD_SIZE - 1 && revealed[x + 1][y]) {  // Down
        surroundingPieces.push_back(grid[x + 1][y]);
      }
      if (y > 0 && revealed[x][y - 1]) {  // Left
        surroundingPieces.push_back(grid[x][y - 1]);
      }
      if (y < BOARD_SIZE - 1 && revealed[x][y + 1]) {  // Right
        surroundingPieces.push_back(grid[x][y + 1]);
      }
      return surroundingPieces;
    }

    // Get the avaiable positions to move a piece to
    std::vector<std::pair<int, int>> getAvailableMoves(int x, int y) {
      std::vector<std::pair<int, int>> availableMoves;
      if (x > 0 && !occupied[x - 1][y]) {  // Up
        availableMoves.push_back({x - 1, y});
      }
      if (x < BOARD_SIZE - 1 && !occupied[x + 1][y]) {  // Down
        availableMoves.push_back({x + 1, y});
      }
      if (y > 0 && !occupied[x][y - 1]) {  // Left
        availableMoves.push_back({x, y - 1});
      }
      if (y < BOARD_SIZE - 1 && !occupied[x][y + 1]) {  // Right
        availableMoves.push_back({x, y + 1});
      }
      return availableMoves;
    }

    // Function that checks if a piece can beat another piece after attacking
    bool canBeat(Piece attacker, Piece defender) { return (attacker >= defender); }
};

#endif