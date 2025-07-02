
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <string>

class IllMoveException {
public:
  virtual std::string what() const = 0;
  virtual ~IllMoveException() = default;
};

class EmptyException : public IllMoveException {
public:
  std::string what() const override {
    return "Sorry you can't choose an empty pit :(, try "
           "again!";
  }
};

class InvalidException : public IllMoveException {
public:
  std::string what() const override {
    return "Please choose a valid pit that DOES exist... :o ";
  }
};

class InputException {
public:
  virtual std::string what() const = 0;
  virtual ~InputException() = default;
};

class QuitException : public InputException {
public:
  std::string what() const override {
    return "Quitting the game at user's request and saving "
           "current game play!";
  }
};

class ConnectionException : public InputException {
public:
  std::string what() const override {
    return "Connection has been lost please try reconnecting";
  }
};

#endif