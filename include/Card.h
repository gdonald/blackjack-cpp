#ifndef CARD_H
#define CARD_H

#include <string>
#include <sstream>

class Card {
public:
  static const char *const faces[14][4];

  unsigned value{};
  unsigned suitValue{};

  Card(unsigned v, unsigned sv);

  ~Card();

  bool isAce();

  bool isTen();

  std::string toString();
};

#endif
