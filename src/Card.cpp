#include "Card.h"

unsigned Card::faceType = 1;

const char *const Card::faces[14][4] = {{"A♠", "A♥", "A♣", "A♦"},
                                        {"2♠", "2♥", "2♣", "2♦"},
                                        {"3♠", "3♥", "3♣", "3♦"},
                                        {"4♠", "4♥", "4♣", "4♦"},
                                        {"5♠", "5♥", "5♣", "5♦"},
                                        {"6♠", "6♥", "6♣", "6♦"},
                                        {"7♠", "7♥", "7♣", "7♦"},
                                        {"8♠", "8♥", "8♣", "8♦"},
                                        {"9♠", "9♥", "9♣", "9♦"},
                                        {"T♠", "T♥", "T♣", "T♦"},
                                        {"J♠", "J♥", "J♣", "J♦"},
                                        {"Q♠", "Q♥", "Q♣", "Q♦"},
                                        {"K♠", "K♥", "K♣", "K♦"},
                                        {"??", "",   "",   ""},};

const char *const Card::faces2[14][4] = {{"🂡", "🂱", "🃁", "🃑"},
                                         {"🂢", "🂲", "🃂", "🃒"},
                                         {"🂣", "🂳", "🃃", "🃓"},
                                         {"🂤", "🂴", "🃄", "🃔"},
                                         {"🂥", "🂵", "🃅", "🃕"},
                                         {"🂦", "🂶", "🃆", "🃖"},
                                         {"🂧", "🂷", "🃇", "🃗"},
                                         {"🂨", "🂸", "🃈", "🃘"},
                                         {"🂩", "🂹", "🃉", "🃙"},
                                         {"🂪", "🂺", "🃊", "🃚"},
                                         {"🂫", "🂻", "🃋", "🃛"},
                                         {"🂭", "🂽", "🃍", "🃝"},
                                         {"🂮", "🂾", "🃎", "🃞"},
                                         {"🂠", "",   "",   ""},};

Card::~Card() = default;

Card::Card(unsigned v, unsigned sv) {
  value = v;
  suitValue = sv;
}

std::string Card::toString() const {
  if (faceType == 2) {
    return Card::faces2[value][suitValue];
  }

  return Card::faces[value][suitValue];
}

bool Card::isAce() const { return value == 0; }

bool Card::isTen() const { return value > 8; }
