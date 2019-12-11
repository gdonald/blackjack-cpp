#ifndef DEALERHAND_H
#define DEALERHAND_H

#include <iostream>
#include "Hand.h"
#include "Card.h"

class DealerHand : public Hand {
  using Hand::Hand;

public:
  DealerHand();

  explicit DealerHand(Game *g);

  ~DealerHand() override;

  bool upCardIsAce();

  void draw();

  bool isBusted() override;

  bool hideDownCard = true;

  unsigned getValue(CountMethod);
};

#endif
