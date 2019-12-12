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

  unsigned cardsDealt = cards.size() - cards.size();
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
    for (unsigned suite = 0; suite < 4; ++suite) {
      cards.emplace_back(0, suite);
      cards.emplace_back(10, suite);
    }
  }

  shuffle();
}

void Shoe::newJacks() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suite = 0; suite < 4; ++suite) {
      cards.emplace_back(10, suite);
    }
  }
}

void Shoe::newAces() {
  cards.clear();
  std::cout << "cards.size(): " << cards.size() << std::endl;

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suite = 0; suite < 4; ++suite) {
      cards.emplace_back(0, suite);
    }
  }

  std::cout << "cards.size(): " << cards.size() << std::endl;
}

void Shoe::newSevens() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suite = 0; suite < 4; ++suite) {
      cards.emplace_back(6, suite);
    }
  }
}

void Shoe::newEights() {
  cards.clear();

  for (unsigned deck = 0; deck < numDecks * 100; ++deck) {
    for (unsigned suite = 0; suite < 4; ++suite) {
      cards.emplace_back(7, suite);
    }
  }
}

void Shoe::newRegular() {
  std::cout << "Shoe::newRegular(): " << std::endl;
  cards.clear();

  for (unsigned deck = 0; deck < numDecks; ++deck) {
    for (unsigned suite = 0; suite < 4; ++suite) {
      for (unsigned value = 0; value < 13; ++value) {
        cards.emplace_back(value, suite);
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
