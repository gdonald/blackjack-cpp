#ifndef HAND_H_
#define HAND_H_

#include <vector>
#include "Card.h"

namespace std
{
  class Game;
  
  class Hand
  {
    public:
      enum Status { Unknown, Won, Lost, Push };
      enum CountMethod { Soft, Hard };
      vector<Card> cards;
      Game* game;
      bool stood;
      bool played;

      Hand(Game* g) : game(g)
      {
        played = false;
        stood = false;
      };

      virtual ~Hand();

      bool isBusted();
      bool isBlackjack();
      virtual bool isDone();
      void dealCard();
  };
}

#endif
