#ifndef SHOE_H_
#define SHOE_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"

namespace std
{
  class Shoe
  {
    private:
      unsigned numDecks;
      vector<Card> cards;

    public:
      static const unsigned shuffleSpecs[8][2];

      Shoe();
      Shoe(unsigned nd);
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
}

#endif
