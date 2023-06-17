#ifndef PLAYERHAND_H
#define PLAYERHAND_H

#include <iostream>
#include <string>
#include <sstream>
#include "Hand.h"

class Game;

class PlayerHand : public Hand {
  using Hand::Hand;

public:
  const static unsigned MAX_PLAYER_HANDS = 7;
  static unsigned totalPlayerHands;
  unsigned bet{};
  Status status;
  bool paid{};

  explicit PlayerHand(Game *g);

  PlayerHand(Game *g, unsigned b) : Hand(g), bet(b) {
    ++totalPlayerHands;
    status = Unknown;
    paid = false;
  };

  ~PlayerHand() override;

  void getAction();

  void hit();

  void dbl();

  void stand();

  bool canSplit();

  bool canDbl();

  bool canStand();

  bool canHit();

  bool isDone() override;

  bool isBusted() override;

  void draw(unsigned index);

  void process();

  unsigned getValue(CountMethod);
};

#endif
