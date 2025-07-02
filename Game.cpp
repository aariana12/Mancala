

#include "Game.hpp"
#include "Exception.hpp"
#include "tools.hpp"
#include <fstream>
#include <iostream>
#include <string>

Game::Game(int numHouses, int numSeeds)
    : kalah(std::make_unique<Kalah>(numHouses, numSeeds)) {}

Game::Game() : kalah(nullptr) {}

void Game::playGame() {
  std::cout << "Welcome to Kalah!" << std::endl;
  try {
    while (!kalah->isOver()) {
      std::cout << "-----------" << std::endl;
      std::cout << kalah->getCurPlayer().name
                << "'s turn:" << std::endl;
      std::cout << kalah->printBoard() << std::endl;

      std::cout << "Please enter a pit number for "
                << kalah->getCurPlayer().name
                << " (q to quit): " << std::endl;
      std::string input;
      if (!(std::cin >> input)) {
        throw ConnectionException();
      }

      std::cout << kalah->getCurPlayer().name
                << " playing move " << input << std::endl;

      if (input == "q") {
        throw QuitException();
      }
      int move = -1;
      try {
        move = std::stoi(input);
        kalah->doMove(move);

        if (kalah->wasCaptured()) {
          std::cout << "Captured " << kalah->getCapSeeds()
                    << " seeds!!" << std::endl;
        }

        if (kalah->wasExtra()) {
          std::cout << kalah->getCurPlayer().name
                    << " gets another turn" << std::endl;
        } else {
          std::cout << "Turn is over" << std::endl;
        }
      } catch (const IllMoveException &e) {
        std::cerr << "You have an illegal move!!!: "
                  << e.what() << std::endl;
        continue;
      } catch (const std::invalid_argument &) {
        std::cerr
            << "Your input is invalid, please try again :("
            << std::endl;
        continue;
      } catch (const std::out_of_range &) {
        std::cerr << "Your input is not in range, please try "
                     "again :("
                  << std::endl;
        continue;
      }
    }
    kalah->endGame();
    std::cout << kalah->printBoard() << std::endl;

    Outcome winner = kalah->getOutcome();
    if (winner == Outcome::SouthWin) {
      std::cout << "South Wins!!! :)" << std::endl;
    } else if (winner == Outcome::NorthWin) {
      std::cout << "North Wins!! :)" << std::endl;
    } else {
      std::cout << "so sad, it's a tie :( TRY AGAIN!"
                << std::endl;
    }

    std::cout << "Hope you had fun, game over!" << std::endl;
  } catch (const ConnectionException &e) {
    std::cerr << e.what() << std::endl;
    saveState();
    std::exit(EXIT_FAILURE);
  } catch (const QuitException &e) {
    std::cerr << e.what() << std::endl;
    saveState();
    std::exit(EXIT_SUCCESS);
  }
}

void Game::saveState() const {
  std::ofstream outFile("kalah.state");
  if (!outFile) {
    throw std::runtime_error("Could not open file to save :(");
  }
  Snapshot snapshot(*kalah);
  snapshot.print(outFile);
  outFile.close();
}

void Game::restoreState(const Snapshot &snapshot) {
  std::ifstream inFile("kalah.state");
  if (!inFile) {
    fatal("Could not open file to restore :(");
  }

  kalah = std::make_unique<Kalah>(snapshot.getNumHouses(), 0);
  kalah->restoreState(snapshot);
}