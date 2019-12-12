#ifndef SHOE_H
#define SHOE_H

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"

class Shoe {
private:
  unsigned numDecks;
  std::vector <Card> cards;

public:
  static const unsigned shuffleSpecs[8][2];

  Shoe();

  explicit Shoe(unsigned nd);

  virtual ~Shoe();

  bool needToShuffle();

  void shuffle();

  void newRegular();

  void newEights();

  void newSevens();

  void newAces();

  void newJacks();

  void newAcesJacks();

  Card getNextCard();
};

#endif
