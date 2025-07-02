

#ifndef SNAPSHOT_HPP
#define SNAPSHOT_HPP

#include "Player.hpp"
#include <iostream>
#include <vector>

class Kalah;

class Snapshot {
private:
  int numHouses;
  Player activePlayer;
  std::vector<int> seeds;

public:
  Snapshot();
  Snapshot(const Kalah &kg);

  std::ostream &print(std::ostream &out) const;
  std::istream &read(std::istream &in);

  int getNumHouses() const { return numHouses; }
  const Player &getActivePlayer() const {
    return activePlayer;
  }
  const std::vector<int> &getSeeds() const { return seeds; }
};

#endif
