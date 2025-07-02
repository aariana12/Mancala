

#include "Snapshot.hpp"
#include "Board.hpp"
#include "Kalah.hpp"

Snapshot::Snapshot()
    : numHouses(0),
      activePlayer(Player(Side::South, "South", 'S')),
      seeds() {}

Snapshot::Snapshot(const Kalah &kg)
    : numHouses(kg.getNumHouses()),
      activePlayer(kg.getActivePlayer()) {
  kg.grab(seeds);
}

std::ostream &Snapshot::print(std::ostream &out) const {
  out << numHouses << " ";
  out << (activePlayer.side == Side::North ? 'N' : 'S') << " ";
  for (int seed : seeds) {
    out << seed << " ";
  }
  return out;
}

std::istream &Snapshot::read(std::istream &in) {
  in >> numHouses;

  char sideChar;
  in >> sideChar;
  Side side = (sideChar == 'N') ? Side::North : Side::South;
  activePlayer =
      Player(side, (side == Side::North ? "North" : "South"),
             sideChar);

  seeds.clear();
  int seed;
  while (in >> seed) {
    seeds.push_back(seed);
  }
  return in;
}
