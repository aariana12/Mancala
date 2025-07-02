

#ifndef PIT_HPP_
#define PIT_HPP_
#include "side.hpp"
#include <string>

class Pit {
private:
  Side owner;
  int pos;
  std::string label;
  int seeds;
  Pit *next;
  Pit *opposite;

public:
  Pit()
      : owner(Side::South), pos(0), label(""), seeds(0),
        next(nullptr), opposite(nullptr) {}

  Pit(Side owner, int pos, const std::string &label, int seeds)
      : owner(owner), pos(pos), label(label), seeds(seeds),
        next(nullptr), opposite(nullptr) {}

  void set_next(Pit *next_pit) { next = next_pit; }

  void set_opp(Pit *opp_pit) { opposite = opp_pit; }

  Pit *get_next() const { return next; }

  Pit *get_opp() const { return opposite; }
  const std::string &get_label() const { return label; }

  int &getSeeds() { return seeds; }

  Side getOwner() const { return owner; }
};

#endif
