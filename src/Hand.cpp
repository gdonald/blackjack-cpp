#include "Hand.h"
#include "Game.h"

void Hand::dealCard() {
  Card c = game->shoe.getNextCard();
  cards.push_back(c);
}

bool Hand::isBlackjack() {
  if (cards.size() != 2) { return false; }
  if (cards[0].isAce() && cards[1].isTen()) { return true; }

  return cards[1].isAce() && cards[0].isTen();
}

bool Hand::isDone() {
  return false;
}

Hand::~Hand() = default;
