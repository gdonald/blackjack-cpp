#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Hand.h"
#include "DealerHand.h"
#include "PlayerHand.h"
#include "Shoe.h"

class Game {

public:
  const static unsigned MIN_BET = 500;
  const static unsigned MAX_BET = 10000000;
  static const char *const SAVE_FILE;

  Game();

  virtual ~Game();

  Shoe shoe;
  DealerHand dealerHand;
  std::vector<PlayerHand> playerHands;
  unsigned currentPlayerHand;
  unsigned currentBet;
  unsigned money;
  bool quitting;
  unsigned deckType;

  int run();

  unsigned allBets();

  [[nodiscard]] bool moreHandsToPlay() const;

  bool needToPlayDealerHand();

  void splitCurrentHand();

  void playMoreHands();

  void playDealerHand();

  void dealNewHand();

  void drawHands();

  void askInsurance();

  void insureHand();

  void noInsurance();

  void payHands();

  void betOptions();

  void gameOptions();

  void getNewNumDecks();

  void getNewDeckType();

  void getNewFaceType();

  void getNewBet();

  void normalizeCurrentBet();

  void saveGame() const;

  void loadGame();

  static void clear();
};

#endif
