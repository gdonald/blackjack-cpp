#ifndef SHOE_H
#define SHOE_H

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"

class Shoe {
private:
  std::vector<Card> cards;

  void newShoe(std::vector<int> values);

  void newRegular();

  void newEights();

  void newSevens();

  void newAces();

  void newJacks();

  void newAcesJacks();

public:
  static const unsigned shuffleSpecs[8];
  static const unsigned CARDS_PER_DECK;
  static unsigned numDecks;

  Shoe();

  virtual ~Shoe();

  bool needToShuffle();

  void shuffle();

  void buildNewShoe(unsigned deckType);

  Card getNextCard();

  [[nodiscard]] unsigned getTotalCards() const;
};

#endif
