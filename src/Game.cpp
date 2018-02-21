#include "Game.h"

namespace std
{
  const char * const Game::SAVE_FILE = "bj.txt";

  Game::Game()
  {
    numDecks = 1;
    money = 10000;
    currentBet = 500;

    loadGame();

    shoe = Shoe(numDecks);
    dealerHand = DealerHand(this);

    currentPlayerHand = 0;
    playerHands = {};
  }

  Game::~Game()
  {
  }

  int Game::allBets()
  {
    int allBets = 0;

    for(unsigned x = 0; x < playerHands.size(); ++x)
    {
      allBets += playerHands[x].bet;
    }

    return allBets;
  }

  void Game::askInsurance()
  {
    cout << " Insurance?  (Y) Yes  (N) No" << endl;
    bool br = false;
    char myChar = { 0 };

    while(true)
    {
      myChar = getchar();

      switch(myChar)
      {
        case 'y':
          br = true;
          insureHand();
          break;
        case 'n':
          br = true;
          noInsurance();
          break;
        default:
          br = true;
          clear();
          drawHands();
          askInsurance();
          break;
      }

      if (br)
      {
        break;
      }
    }
  }

  void Game::clear()
  {
    system("export TERM=linux; clear");
  }

  void Game::dealNewHand()
  {
    if (shoe.needToShuffle())
    {
      shoe.newRegular();
    }

    playerHands = {};
    playerHands.clear();
    PlayerHand::totalPlayerHands = 0;

    PlayerHand* playerHand;
    playerHands.push_back(PlayerHand(this, currentBet));
    playerHand = &playerHands[0];

    currentPlayerHand = 0;

    dealerHand = DealerHand(this);

    dealerHand.dealCard();
    playerHand->dealCard();
    dealerHand.dealCard();
    playerHand->dealCard();

    if (dealerHand.upCardIsAce() && !playerHand->isBlackjack())
    {
      drawHands();
      askInsurance();
      return;
    }

    if (playerHand->isDone())
    {
      dealerHand.hideDownCard = false;
      payHands();
      drawHands();
      betOptions();
      return;
    }

    drawHands();
    playerHand->getAction();
    saveGame();
  }

  void Game::drawHands()
  {
    clear();
    cout << endl << " Dealer: " << endl;
    dealerHand.draw();
    cout << endl;

    cout << fixed << setprecision(2);
    cout << endl << " Player $" << (float)(money / 100.0) << ":" << endl;
    for(unsigned i = 0; i < playerHands.size(); ++i)
    {
      playerHands.at(i).draw(i);
    }
  }

  void Game::betOptions()
  {
    cout << " (D) Deal Hand  (B) Change Bet  (O) Options  (Q) Quit" << endl;

    bool br = false;
    char myChar = { 0 };

    while(true)
    {
      myChar = getchar();

      switch(myChar)
      {
        case 'd':
          br = true;
          dealNewHand();
          break;
        case 'b':
          br = true;
          getNewBet();
          break;
        case 'o':
	  br = true;
	  gameOptions();
	  break;
        case 'q':
          clear();
          br = true;
          break;
        default:
          br = true;
          clear();
          drawHands();
          betOptions();
      }

      if (br)
      {
        break;
      }
    }
  }

  void Game::gameOptions()
  {
    bool br = false;
    char myChar = { 0 };

    clear();
    drawHands();
    cout << " (N) Number of Decks  (T) Deck Type  (B) Back" << endl;

    while(true)
    {
      myChar = getchar();

      switch(myChar)
      {
        case 'n':
          br = true;
          getNewNumDecks();
          break;
        case 't':
          br = true;
          getNewDeckType();
          break;
        case 'b':
	  br = true;
	  clear();
	  drawHands();
	  betOptions();
	  break;
        default:
          br = true;
          clear();
          drawHands();
          gameOptions();
      }

      if (br)
      {
        break;
      }
    }
  }

  void Game::getNewDeckType()
  {

    bool br = false;
    char myChar = { 0 };

    clear();
    drawHands();
    cout << " (1) Regular  (2) Aces  (3) Jacks  (4) Aces & Jacks  (5) Sevens  (6) Eights" << endl;

    while(true)
    {
      myChar = getchar();

      switch(myChar)
      {
        case '1':
          br = true;
          shoe.newRegular();
          break;
        case '2':
          br = true;
          shoe.newAces();
          break;
        case '3':
          br = true;
          shoe.newJacks();
          break;
        case '4':
          br = true;
          shoe.newAcesJacks();
          break;
        case '5':
          br = true;
          shoe.newSevens();
          break;
        case '6':
          br = true;
          shoe.newEights();
          break;
        default:
          br = true;
          clear();
          drawHands();
          gameOptions();
      }

      if (br)
      {
	drawHands();
	betOptions();
        break;
      }
    }
  }

  void Game::getNewBet()
  {
    clear();
    drawHands();

    cout << "  Current Bet: $" << put_money(currentBet / 100) << endl << "  Enter New Bet: $";
    long double betTmp;
    cin >> get_money(betTmp);
    unsigned bet = betTmp * 100;
    currentBet = bet;

    normalizeCurrentBet();
    dealNewHand();
  }

  void Game::getNewNumDecks()
  {
    clear();
    drawHands();

    cout << "  Number Of Decks: " << numDecks << endl << "  Enter New Number Of Decks: ";
    unsigned tmp;
    cin >> tmp;

    if(tmp < 1) tmp = 1;
    if(tmp > 8) tmp = 8;

    numDecks = tmp;
    gameOptions();
  }

  void Game::insureHand()
  {
    PlayerHand *h = &playerHands[currentPlayerHand];

    h->bet /= 2;
    h->played = true;
    h->payed = true;
    h->status = Hand::Lost;

    money -= h->bet;

    drawHands();
    betOptions();
  }

  bool Game::moreHandsToPlay()
  {
    return currentPlayerHand < playerHands.size() - 1;
  }

  bool Game::needToPlayDealerHand()
  {
    for(unsigned x = 0; x < playerHands.size(); ++x)
    {
      PlayerHand* h = &playerHands[x];

      if (!(h->isBusted() || h->isBlackjack()))
      {
        return true;
      }
    }

    return false;
  }

  void Game::noInsurance()
  {
    if (dealerHand.isBlackjack())
    {
      dealerHand.hideDownCard = false;
      dealerHand.played = true;

      payHands();
      drawHands();
      betOptions();
      return;
    }

    PlayerHand *h = &playerHands[currentPlayerHand];
    if (h->isDone())
    {
      playDealerHand();
      drawHands();
      betOptions();
      return;
    }

    drawHands();
    h->getAction();
  }

  void Game::normalizeCurrentBet()
  {
    if (currentBet < Game::MIN_BET)
    {
      currentBet = Game::MIN_BET;
    }
    else if (currentBet > Game::MAX_BET)
    {
      currentBet = Game::MAX_BET;
    }

    if (currentBet > money)
    {
      currentBet = money;
    }
  }

  void Game::payHands()
  {
    unsigned dhv = dealerHand.getValue(Hand::Soft);
    bool dhb = dealerHand.isBusted();

    for(unsigned x = 0; x < playerHands.size(); ++x)
    {
      PlayerHand* h = &playerHands[x];

      if (h->payed)
      {
        continue;
      }

      h->payed = true;

      unsigned phv = h->getValue(Hand::Soft);

      if (dhb || phv > dhv)
      {
        if (h->isBlackjack())
        {
          h->bet *= 1.5;
        }

        money += h->bet;
        h->status = Hand::Won;
      }
      else if (phv < dhv)
      {
        money -= h->bet;
        h->status = Hand::Lost;
      }
      else
      {
        h->status = Hand::Push;
      }
    }

    normalizeCurrentBet();
    saveGame();
  }

  void Game::playDealerHand()
  {
    if (dealerHand.isBlackjack())
    {
      dealerHand.hideDownCard = false;
    }

    if (!needToPlayDealerHand())
    {
      dealerHand.played = true;
      payHands();
      return;
    }

    dealerHand.hideDownCard = false;

    unsigned softCount = dealerHand.getValue(Hand::Soft);
    unsigned hardCount = dealerHand.getValue(Hand::Hard);
    while(softCount < 18 && hardCount < 17)
    {
      dealerHand.dealCard();
      softCount = dealerHand.getValue(Hand::Soft);
      hardCount = dealerHand.getValue(Hand::Hard);
    }

    dealerHand.played = true;
    payHands();
  }

  void Game::playMoreHands()
  {
    ++currentPlayerHand;
    PlayerHand *h = &playerHands[currentPlayerHand];
    h->dealCard();
    if (h->isDone())
    {
      h->process();
      return;
    }

    drawHands();
    h->getAction();
  }

  int Game::run()
  {
    dealNewHand();
    return 0;
  }

  void Game::saveGame()
  {
    ofstream saveFile;
    saveFile.open(Game::SAVE_FILE);

    if(saveFile.is_open())
    {
      saveFile << numDecks << "|" << money << "|" << currentBet << endl;
      saveFile.close();
    }
    else
    {
      cout << "Could not open file: " << Game::SAVE_FILE << endl;
      throw;
    }
  }

  void Game::loadGame()
  {
    ifstream saveFile;
    saveFile.open(Game::SAVE_FILE);
    if(saveFile.is_open())
    {
      string line;
      getline(saveFile, line);
      saveFile.close();

      vector<string> elems;
      stringstream ss;
      ss.str(line);
      string item;
      while(getline(ss, item, '|'))
      {
        elems.push_back(item);
      }

      numDecks = (unsigned)stoul(elems[0]);
      money = (unsigned)stoul(elems[1]);
      currentBet = (unsigned)stoul(elems[2]);
    }

    if(money < MIN_BET)
    {
      money = 10000;
    }
  }

  void Game::splitCurrentHand()
  {
    PlayerHand *currentHand = &playerHands[currentPlayerHand];

    if (!currentHand->canSplit())
    {
      drawHands();
      currentHand->getAction();
      return;
    }

    playerHands.push_back(PlayerHand(this, this->currentBet));

    // expand hands
    unsigned x = playerHands.size() - 1;
    while(x > currentPlayerHand)
    {
      playerHands[x] = playerHands[x - 1];
      --x;
    }

    // split
    PlayerHand *thisHand = &playerHands[currentPlayerHand];
    PlayerHand *splitHand = &playerHands[currentPlayerHand + 1];

    splitHand->cards.clear();
    Card c = thisHand->cards.back();
    splitHand->cards.push_back(c);
    thisHand->cards.pop_back();

    Card cx = shoe.getNextCard();
    thisHand->cards.push_back(cx);

    if (thisHand->isDone())
    {
      thisHand->process();
      return;
    }

    drawHands();
    playerHands[currentPlayerHand].getAction();
  }
}
