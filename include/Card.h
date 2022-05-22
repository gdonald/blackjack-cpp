#ifndef CARD_H
#define CARD_H

#include <string>
#include <sstream>

class Card {
public:
  static const char *const faces[14][4];
  static const char *const faces2[14][4];
  static unsigned faceType;

  unsigned value{};
  unsigned suitValue{};

  Card(unsigned v, unsigned sv);

  ~Card();

  [[nodiscard]] bool isAce() const;

  [[nodiscard]] bool isTen() const;

  [[nodiscard]] std::string toString() const;
};

#endif
