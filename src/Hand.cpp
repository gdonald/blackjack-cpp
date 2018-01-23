#include "Hand.h"
#include "Game.h"

namespace std
{
  void Hand::dealCard()
  {
    Card c = game->shoe.getNextCard();
    cards.push_back(c);
  }

  bool Hand::isBlackjack()
  {
    if(cards.size() != 2)
    {
      return false;
    }

    if(cards[0].isAce() && cards[1].isTen())
    {
      return true;
    }

    if(cards[1].isAce() && cards[0].isTen())
    {
      return true;
    }

    return false;
  }

  bool Hand::isDone()
  {
    return false;
  }

  Hand::~Hand()
  {
  }
}
