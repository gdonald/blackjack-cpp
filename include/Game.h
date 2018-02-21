#ifndef GAME_H_
#define GAME_H_

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

namespace std
{
  class Game
  {
    private:
      unsigned numDecks;

    public:
      const static unsigned MIN_BET = 500;
      const static unsigned MAX_BET = 10000000;
      static const char * const SAVE_FILE;

      Game();
      virtual ~Game();

      Shoe shoe;
      DealerHand dealerHand;
      vector<PlayerHand> playerHands;
      unsigned currentPlayerHand;
      unsigned currentBet;
      unsigned money;


      int run();
      int allBets();

      bool moreHandsToPlay();
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
      void getNewBet();
      void normalizeCurrentBet();
      void saveGame();
      void loadGame();
      void clear();
  };
}

#endif
