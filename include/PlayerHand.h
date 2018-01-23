#ifndef PLAYERHAND_H_
#define PLAYERHAND_H_

#include <iostream>
#include <string>
#include <sstream>
#include "Hand.h"

namespace std
{
  class Game;

  class PlayerHand: public Hand
  {
      using Hand::Hand;

    public:
      const static unsigned MAX_PLAYER_HANDS = 7;
      static unsigned totalPlayerHands;
      unsigned bet;
      Status status;
      bool payed;

      PlayerHand();
      PlayerHand(Game* g, unsigned b) : Hand(g), bet(b)
      {
        ++totalPlayerHands;
        status = Unknown;
        payed = false;
      };

      virtual ~PlayerHand();
      void getAction();
      void hit();
      void dbl();
      void stand();
      bool canSplit();
      bool canDbl();
      bool canStand();
      bool canHit();
      bool isDone();
      bool isBusted();
      
      void draw(unsigned index);
      void process();

      unsigned getValue(CountMethod);
  };
}

#endif
