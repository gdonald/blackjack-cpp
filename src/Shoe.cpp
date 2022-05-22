#include "Shoe.h"

const unsigned Shoe::shuffleSpecs[] = {80, 81, 82, 84, 86, 89, 92, 95};
const unsigned Shoe::CARDS_PER_DECK = 52;
unsigned Shoe::numDecks = 8;

Shoe::Shoe() = default;

Shoe::~Shoe() = default;

bool Shoe::needToShuffle() {
  if (cards.empty()) { return true; }

  auto cardsDealt = getTotalCards() - cards.size();
  auto used = (unsigned) ((cardsDealt / (double) cards.size()) * 100.0);
  auto shuffleSpec = Shoe::shuffleSpecs[numDecks - 1];

  return used > shuffleSpec;
}

unsigned int Shoe::getTotalCards() const {
  return Shoe::numDecks * CARDS_PER_DECK;
}

void Shoe::shuffle() {
  std::random_device rng;
  std::mt19937 urng(rng());

  for (unsigned i = 0; i < 7; ++i) {
    std::shuffle(cards.begin(), cards.end(), urng);
  }
}

void Shoe::buildNewShoe(unsigned deckType) {
  switch (deckType) {
    case 2:
      newAces();
      break;
    case 3:
      newJacks();
      break;
    case 4:
      newAcesJacks();
      break;
    case 5:
      newSevens();
      break;
    case 6:
      newEights();
      break;
    default:
      newRegular();
  }
}

void Shoe::newAcesJacks() {
  std::vector<int> values{0, 10};
  Shoe::newShoe(values);
}

void Shoe::newJacks() {
  std::vector<int> values{10};
  newShoe(values);
}

void Shoe::newAces() {
  std::vector<int> values{0};
  newShoe(values);
}

void Shoe::newSevens() {
  std::vector<int> values{6};
  newShoe(values);
}

void Shoe::newEights() {
  std::vector<int> values{7};
  newShoe(values);
}

void Shoe::newRegular() {
  std::vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  newShoe(values);
}

void Shoe::newShoe(std::vector<int> values) {
  cards.clear();
  auto totalCards = getTotalCards();

  while (cards.size() < totalCards) {
    for (unsigned suit = 0; suit < 4; ++suit) {
      if (cards.size() >= totalCards) {
        break;
      }

      std::for_each(values.begin(), values.end(), [this, &suit](int &value) {
        cards.emplace_back(value, suit);
      });
    }
  }

  shuffle();
}

Card Shoe::getNextCard() {
  Card c = cards.back();
  cards.pop_back();
  return c;
}
