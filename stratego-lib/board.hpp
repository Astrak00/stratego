#include <iostream>
#include <string>
#include <thread>
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
        revealed[x][y] = false;  // Hide the piece
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
      // Clear the console
      std::cout << "\033[2J\033[1;1H";  // ANSI escape code to clear the screen

      for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
          if (revealed[i][j]) {
            std::cout << grid[i][j] << " ";
          } else {
            std::cout << " . ";  // X for unrevealed pieces
          }
        }
        std::cout << std::endl;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
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

    bool canMove(int fromX, int fromY, int toX, int toY) {
      Piece piece = grid[fromX][fromY];
      int deltaX  = std::abs(toX - fromX);
      int deltaY  = std::abs(toY - fromY);

      if (piece.type == PieceType::EMPTY || piece.type == PieceType::BOMB ||
          piece.type == PieceType::FLAG) {
        std::cerr << "No piece to move." << std::endl;
        return false;
      } else if (piece.type == PieceType::SCOUT) {
        return (deltaX == 0 || deltaY == 0) && (deltaX + deltaY > 0);
      }
      return (deltaX + deltaY == 1);
    }

    bool move(int fromX, int fromY, int toX, int toY) {
      if (!(fromX >= 0 && fromX < BOARD_SIZE && fromY >= 0 && fromY < BOARD_SIZE && toX >= 0 &&
            toX < BOARD_SIZE && toY >= 0 && toY < BOARD_SIZE)) {
        std::cerr << "Invalid position to move." << std::endl;
        return false;
      }
      // Check if the source is occupied and destination is empty
      if (!(occupied[fromX][fromY] && !occupied[toX][toY])) {
        std::cerr << "Source position is not occupied or destination is not empty." << std::endl;
        return false;
      }
      if (!canMove(fromX, fromY, toX, toY)) {  // Check if the piece can perform the move
        std::cerr
            << "Move coordinates are not valid: too much movement in one or multiple directions."
            << std::endl;
        return false;
      }
      placePiece(toX, toY, grid[fromX][fromY]);  // Place the piece at the new position
      revealed[toX][toY] = true;                 // Reveal the new position
      removePiece(fromX, fromY);                 // Set the old position to an empty piece
      return true;
    }

  private:
    // Function that checks if a piece can beat another piece after attacking
    bool canBeat(Piece attacker, Piece defender) { return (attacker >= defender); }
};

#endif