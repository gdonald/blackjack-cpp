#include "DealerHand.h"

DealerHand::~DealerHand() = default;

DealerHand::DealerHand() : Hand(nullptr) {}

DealerHand::DealerHand(Game *g) : Hand(g) {}

bool DealerHand::isBusted() {
  return getValue(Soft) > 21;
}

unsigned DealerHand::getValue(CountMethod countMethod) {
  unsigned v = 0;
  unsigned total = 0;

  for (unsigned x = 0; x < cards.size(); ++x) {
    if (x == 1 && hideDownCard) {
      continue;
    }

    unsigned tmp_v = cards.at(x).value + 1;
    v = tmp_v > 9 ? 10 : tmp_v;

    if (countMethod == Soft && v == 1 && total < 11) {
      v = 11;
    }

    total += v;
  }

  if (countMethod == Soft && total > 21) {
    return getValue(Hard);
  }

  return total;
}

void DealerHand::draw() {
  std::cout << " ";

  for (unsigned i = 0; i < cards.size(); ++i) {
    std::cout << (i == 1 && hideDownCard ? Card::faces[13][0] : cards[i].toString()) << " ";
  }

  std::cout << " ⇒  " << getValue(Soft);
}

bool DealerHand::upCardIsAce() {
  return cards[0].isAce();
}
