#ifndef DEALERHAND_H_
#define DEALERHAND_H_

#include <iostream>
#include "Hand.h"
#include "Card.h"

namespace std
{
  class DealerHand: public Hand
  {
    using Hand::Hand;

    public:
      DealerHand();
      DealerHand(Game* g);
      virtual ~DealerHand();
      bool upCardIsAce();
      void draw();
      bool isBusted();

      bool hideDownCard = true;
      unsigned getValue(CountMethod);
  };
}

#endif
