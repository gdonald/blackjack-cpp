#include "Shoe.h"

const unsigned Shoe::shuffleSpecs[8][2] = {{95, 8},
                                           {92, 7},
                                           {89, 6},
                                           {86, 5},
                                           {84, 4},
                                           {82, 3},
                                           {81, 2},
                                           {80, 1}};

Shoe::~Shoe() = default;

Shoe::Shoe() { numDecks = 1; }

Shoe::Shoe(unsigned nd) : numDecks(nd) {}

bool Shoe::needToShuffle() {
  if (cards.empty()) { return true; }

  unsigned totalCards = numDecks * 52;
  unsigned cardsDealt = totalCards - cards.size();
  auto used = (unsigned) ((cardsDealt / (double) cards.size()) * 100.0);

  for (auto shuffleSpec : Shoe::shuffleSpecs) {
    if (used > shuffleSpec[0] && numDecks == shuffleSpec[1]) {
      return true;
    }
  }

  return false;
}

void Shoe::shuffle() {
  std::random_device rng;
  std::mt19937 urng(rng());

  for (unsigned i = 0; i < 7; ++i) {
    std::shuffle(cards.begin(), cards.end(), urng);
  }
}

void Shoe::newAcesJacks() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 50; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      cards.emplace_back(0, suit);
      cards.emplace_back(10, suit);
    }
  }

  shuffle();
}

void Shoe::newJacks() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      cards.emplace_back(10, suit);
    }
  }
}

void Shoe::newAces() {
  cards.clear();
  std::cout << "cards.size(): " << cards.size() << std::endl;

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      cards.emplace_back(0, suit);
    }
  }

  std::cout << "cards.size(): " << cards.size() << std::endl;
}

void Shoe::newSevens() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      cards.emplace_back(6, suit);
    }
  }
}

void Shoe::newEights() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      cards.emplace_back(7, suit);
    }
  }
}

void Shoe::newRegular() {
  std::cout << "Shoe::newRegular(): " << std::endl;
  cards.clear();

  for (unsigned deck = 0; deck < numDecks; ++deck) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      for (unsigned value = 0; value < 13; ++value) {
        cards.emplace_back(value, suit);
      }
    }
  }

  shuffle();
}

Card Shoe::getNextCard() {
  Card c = cards.back();
  cards.pop_back();
  return c;
}
