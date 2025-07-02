
#include "Board.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "UnitTest.hpp"
#include "tools.hpp"

static string usage = "usage: frametest numHouses numSeeds";

//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  banner();
  cout << "Welcome to Mancala frame test!" << endl;

  if (argc == 2 && std::string(argv[1]) == "-r") {
    std::ifstream inFile("kalah.state");
    Snapshot snapshot;
    snapshot.read(inFile);
    inFile.close();
    Game game;
    game.restoreState(snapshot);
    game.playGame();
  } else if (argc == 3) {
    int numHouses = std::stoi(argv[1]);
    int numSeeds = std::stoi(argv[2]);
    Game game(numHouses, numSeeds);
    game.playGame();
    bye();
    return 0;
  }
}
