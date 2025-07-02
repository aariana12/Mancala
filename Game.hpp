
#ifndef GAME_HPP_
#define GAME_HPP_
#include "Kalah.hpp"
#include "Snapshot.hpp"

class Game {
private:
  // Kalah kalah;
  std::unique_ptr<Kalah> kalah;

public:
  Game(int numHouses, int numSeeds);
  Game();
  void playGame();
  void saveState() const;
  void restoreState(const Snapshot &snapshot);
};

#endif