#ifndef UNITTEST_HPP_
#define UNITTEST_HPP_

#include "Board.hpp"
using namespace std;
class UnitTest {
private:
  const Board bd;

public:
  UnitTest(int numHouses, int numSeeds)
      : bd(numHouses, numSeeds) {
    cout << "UnitTest constructor called" << endl;
  }
  ~UnitTest() = default;

  void run() const;
};

#endif 