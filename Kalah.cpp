

#include "Kalah.hpp"
#include "Exception.hpp"
#include <iostream>
#include <sstream>

Kalah::Kalah(int numHouses, int numSeeds)
    : board(numHouses, numSeeds),
      southPlayer(Side::South, "South", 'S'),
      northPlayer(Side::North, "North", 'N'),
      curPlayer(&southPlayer), extraTurn(false),
      Captured(false), captureSeed(0) {}

bool Kalah::isValidMove(int move) const {
  int index = (curPlayer->side == Side::South)
                  ? move - 1
                  : board.getNum() + move;

  return move >= 0 && move <= board.getNum() &&
         board.getPit(index).getSeeds() > 0;
}

void Kalah::doMove(int move) {
  Captured = false;
  captureSeed = 0;
  extraTurn = false;

  if (!isValidMove(move)) {
    if (move <= 0 || move > board.getNum()) {
      throw InvalidException();
    }
    if (board.getPit(move - 1).getSeeds() == 0) {
      throw EmptyException();
    }
  }

  int startIndex = (curPlayer->side == Side::South)
                       ? move - 1
                       : board.getNum() + move;

  Pit *current = &board.getPit(startIndex);
  int moveSeeds = current->getSeeds();
  current->getSeeds() = 0;

  while (moveSeeds > 0) {
    current = current->get_next();
    if ((curPlayer->side == Side::South &&
         current == &board.getPit(2 * board.getNum() + 1)) ||
        (curPlayer->side == Side::North &&
         current == &board.getPit(board.getNum()))) {
      continue;
    }
    current->getSeeds()++;
    moveSeeds--;
  }

  if (current->getSeeds() == 1 &&
      current->getOwner() == curPlayer->side) {
    Pit *opp = current->get_opp();
    if (opp && opp->getSeeds() > 0) {
      captureSeed = opp->getSeeds() + 1;
      opp->getSeeds() = 0;
      current->getSeeds() = 0;
      Captured = true;
      if (curPlayer->side == Side::South) {
        board.getPit(board.getNum()).getSeeds() += captureSeed;
      } else {
        board.getPit(2 * board.getNum() + 1).getSeeds() +=
            captureSeed;
      }
    }
  }

  if ((curPlayer->side == Side::South &&
       current == &board.getPit(board.getNum())) ||
      (curPlayer->side == Side::North &&
       current == &board.getPit(2 * board.getNum() + 1))) {
    extraTurn = true;
  } else {
    curPlayer = (curPlayer == &southPlayer) ? &northPlayer
                                            : &southPlayer;
  }
}

bool Kalah::isOver() const {
  int southSeeds = 0;
  int northSeeds = 0;
  for (int i = 0; i < board.getNum(); ++i) {
    southSeeds += board.getPit(i).getSeeds();
    northSeeds +=
        board.getPit(board.getNum() + 1 + i).getSeeds();
  }
  return southSeeds == 0 || northSeeds == 0;
}

void Kalah::endGame() {
  for (int i = 0; i < board.getNum(); ++i) {
    board.getPit(board.getNum()).getSeeds() +=
        board.getPit(i).getSeeds();
    board.getPit(i).getSeeds() = 0;
    board.getPit(2 * board.getNum() + 1).getSeeds() +=
        board.getPit(board.getNum() + 1 + i).getSeeds();
    board.getPit(board.getNum() + 1 + i).getSeeds() = 0;
  }
}

Outcome Kalah::getOutcome() const {
  int southScore = board.getPit(board.getNum()).getSeeds();
  int northScore =
      board.getPit(2 * board.getNum() + 1).getSeeds();

  if (southScore > northScore)
    return Outcome::SouthWin;
  if (northScore > southScore)
    return Outcome::NorthWin;
  return Outcome::Tie;
}

void Kalah::grab(std::vector<int> &seeds) const {
  board.collectSeeds(seeds);
}

void Kalah::restoreState(const Snapshot &ss) {
  if (ss.getActivePlayer() == southPlayer) {
    curPlayer = &southPlayer;
  } else if (ss.getActivePlayer() == northPlayer) {
    curPlayer = &northPlayer;
  }
  board.setSeeds(ss.getSeeds());
}

std::string Kalah::printBoard() const {
  std::ostringstream os;

  os << "           ";
  for (int i = board.getNum() + 1; i <= 2 * board.getNum();
       ++i)
    os << "N" << i - board.getNum() << "    ";
  os << "\n          ";
  for (int i = board.getNum() + 1; i <= 2 * board.getNum();
       ++i)
    os << "[" << board.getPit(i).getSeeds() << "]   ";
  os << "\n";

  os << "  N0 ["
     << board.getPit(2 * board.getNum() + 1).getSeeds() << "]"
     << "                                    "
     << "[" << board.getPit(board.getNum()).getSeeds()
     << "] S0\n";

  os << "          ";
  for (int i = board.getNum() - 1; i >= 0; --i)
    os << "[" << board.getPit(i).getSeeds() << "]   ";
  os << "\n           ";
  for (int i = board.getNum() - 1; i >= 0; --i)
    os << "S" << i + 1 << "    ";
  os << "\n";

  return os.str();
}
