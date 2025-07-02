

#ifndef KALAH_HPP_
#define KALAH_HPP_
#include "Board.hpp"
#include "Player.hpp"
#include "Snapshot.hpp"
#include "side.hpp"
#include <string>

enum class Outcome { SouthWin, NorthWin, Tie };

class Kalah {
private:
  Board board;
  Player southPlayer;
  Player northPlayer;
  Player *curPlayer;
  bool extraTurn;
  bool Captured;
  int captureSeed;

public:
  Kalah(int numHouses, int numSeeds);
  bool isValidMove(int move) const;
  void doMove(int move);
  bool isOver() const;
  void endGame();
  Outcome getOutcome() const;
  std::string printBoard() const;

  int numHouses() const { return board.getNum(); }
  const Board &getBoard() const { return board; }
  const Player &getCurPlayer() const { return *curPlayer; }
  bool wasCaptured() const { return Captured; }
  int getCapSeeds() const { return captureSeed; }
  bool wasExtra() const { return extraTurn; }

  void grab(std::vector<int> &seeds) const;
  void restoreState(const Snapshot &ss);
  int getNumHouses() const { return board.getNum(); }
  const Player getActivePlayer() const { return *curPlayer; }
};

#endif