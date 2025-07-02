

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include "side.hpp"
#include <string>

struct Player {
  Side side;
  std::string name;
  char label;

  Player(Side s, const std::string &n, char l)
      : side(s), name(n), label(l) {}

  Side otherSide() const {
    return side == Side::South ? Side::North : Side::South;
  }

  bool operator==(const Player &other) const {
    return this->name == other.name;
  }
  std::string getName() const { return name; }
};

#endif
