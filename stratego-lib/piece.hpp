#include <array>
#include <iostream>
#include <string>
#include <vector>

#ifndef STRATEGO_PIECE_HPP
  #define STRATEGO_PIECE_HPP

enum class PieceType {
  SCOUT,
  MINER,
  SPY,
  SERGEANT,
  LIEUTENANT,
  CAPTAIN,
  MAJOR,
  COLONEL,
  GENERAL,
  MARSHAL,
  FLAG,
  BOMB,
  EMPTY
};

enum class PieceColor { RED, BLUE };

enum class PieceStatus { HIDDEN, REVEALED, MOVED };

struct Piece {
    PieceType type;
    PieceColor color;
    PieceStatus status;

    Piece() : type(PieceType::EMPTY), color(PieceColor::BLUE), status(PieceStatus::HIDDEN) { }

    Piece(PieceType t, PieceColor c) : type(t), color(c), status(PieceStatus::HIDDEN) { }

    void reveal() { status = PieceStatus::REVEALED; }

    void hide() { status = PieceStatus::HIDDEN; }

    // Function for printing piece information
    friend std::ostream & operator<<(std::ostream & os, Piece const & piece) {
      std::string color_code = (piece.color == PieceColor::RED) ? "R" : "B";

      if (piece.status == PieceStatus::HIDDEN) { return os << color_code + "?"; }

      std::string type_code;
      switch (piece.type) {
        case PieceType::SCOUT:
          type_code = "1";
          break;
        case PieceType::MINER:
          type_code = "2";
          break;
        case PieceType::SPY:
          type_code = "S";
          break;
        case PieceType::SERGEANT:
          type_code = "4";
          break;
        case PieceType::LIEUTENANT:
          type_code = "5";
          break;
        case PieceType::CAPTAIN:
          type_code = "6";
          break;
        case PieceType::MAJOR:
          type_code = "7";
          break;
        case PieceType::COLONEL:
          type_code = "8";
          break;
        case PieceType::GENERAL:
          type_code = "9";
          break;
        case PieceType::MARSHAL:
          type_code = "10";
          break;
        case PieceType::FLAG:
          type_code = "F";
          break;
        case PieceType::BOMB:
          type_code = "B";
          break;
        case PieceType::EMPTY:
          type_code = "E";
          break;
      }

      return os << color_code + type_code;
    }

    // Function to compare pieces (can beat another piece) #TODO Game logic lies here
    friend bool operator>=(Piece const & lhs, Piece const & rhs) { return true; }
};

#endif
