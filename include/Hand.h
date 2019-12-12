#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Game;

class Hand {
public:
  enum Status {
    Unknown, Won, Lost, Push
  };
  enum CountMethod {
    Soft, Hard
  };
  std::vector<Card> cards;
  Game *game;
  bool stood;
  bool played;

  explicit Hand(Game *g) : game(g) {
    played = false;
    stood = false;
  };

  virtual ~Hand();

  virtual bool isBusted() = 0;

  bool isBlackjack();

  virtual bool isDone();

  void dealCard();
};

#endif
