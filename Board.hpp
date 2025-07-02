

#ifndef BOARD_HPP_
#define BOARD_HPP_
#include "pit.hpp"
#include "side.hpp"
#include <iostream>
#include <memory>
#include <vector>

class Board {
private:
  int num_house;
  int num_seeds;
  std::unique_ptr<Pit[]> pitWarehouse;

public:
  Board(int house, int seeds)
      : num_house(house), num_seeds(seeds),
        pitWarehouse(std::make_unique<Pit[]>(2 * house + 2)) {
    initializePits();
  }

  void initializePits() {
    for (int i = num_house - 1; i >= 0; --i) {
      pitWarehouse[i] =
          Pit(Side::South, i, "S" + std::to_string(i + 1),
              num_seeds);
      if (i > 0) {
        pitWarehouse[i].set_next(&pitWarehouse[i - 1]);
      }
    }
    pitWarehouse[0].set_next(&pitWarehouse[num_house]);

    pitWarehouse[num_house] = Pit(Side::South, -1, "S0", 0);
    pitWarehouse[num_house].set_next(
        &pitWarehouse[2 * num_house]);

    for (int i = 2 * num_house; i > num_house; --i) {
      pitWarehouse[i] =
          Pit(Side::North, i - num_house - 1,
              "N" + std::to_string(i - num_house), num_seeds);
      pitWarehouse[i].set_next(&pitWarehouse[i - 1]);
    }
    pitWarehouse[num_house + 1].set_next(
        &pitWarehouse[2 * num_house + 1]);

    pitWarehouse[2 * num_house + 1] =
        Pit(Side::North, -1, "N0", 0);
    pitWarehouse[2 * num_house + 1].set_next(
        &pitWarehouse[num_house - 1]);

    for (int i = 0; i < num_house; ++i) {
      pitWarehouse[i].set_opp(
          &pitWarehouse[2 * num_house - i]);
      pitWarehouse[2 * num_house - i].set_opp(
          &pitWarehouse[i]);
    }
  }

  int getNum() const { return num_house; }

  Pit &getPit(int index) const { return pitWarehouse[index]; }

  void collectSeeds(std::vector<int> &seeds) const {
    seeds.clear();
    for (int i = num_house - 1; i >= 0; --i) {
      seeds.push_back(pitWarehouse[i].getSeeds());
    }
    seeds.push_back(pitWarehouse[num_house].getSeeds());

    for (int i = 2 * num_house; i > num_house; --i) {
      seeds.push_back(pitWarehouse[i].getSeeds());
    }
    seeds.push_back(
        pitWarehouse[2 * num_house + 1].getSeeds());
  }

  void setSeeds(const std::vector<int> &seeds) {

    int index = 0;

    for (int i = num_house - 1; i >= 0; --i) {
      pitWarehouse[i].getSeeds() = seeds[index++];
    }
    pitWarehouse[num_house].getSeeds() = seeds[index++];

    for (int i = 2 * num_house; i > num_house; --i) {
      pitWarehouse[i].getSeeds() = seeds[index++];
    }
    pitWarehouse[2 * num_house + 1].getSeeds() =
        seeds[index++];
  }

  void printPitWarehouse() {
    std::cout << "Pit Warehouse State:" << std::endl;
    for (int i = 0; i <= 2 * num_house + 1; ++i) {
      Pit &pit = pitWarehouse[i];
      std::cout << "Index: " << i
                << ", Label: " << pit.get_label()
                << ", Owner: "
                << (pit.getOwner() == Side::South ? "South"
                                                  : "North")
                << ", Seeds: " << pit.getSeeds() << ", Next: "
                << (pit.get_next()
                        ? pit.get_next()->get_label()
                        : "None")
                << ", Opposite: "
                << (pit.get_opp() ? pit.get_opp()->get_label()
                                  : "None")
                << std::endl;
    }
  }
};

#endif