#include "Game.h"

const char *const Game::SAVE_FILE = "bj.txt";

Game::Game() {
  numDecks = 1;
  money = 10000;
  currentBet = 500;

  loadGame();

  shoe = Shoe(numDecks);
  dealerHand = DealerHand(this);

  currentPlayerHand = 0;
  playerHands = {};
}

Game::~Game() = default;

int Game::allBets() {
  uint allBets = 0;

  for (auto & playerHand : playerHands) {
    allBets += playerHand.bet;
  }

  return allBets;
}

void Game::askInsurance() {
  std::cout << " Insurance?  (Y) Yes  (N) No" << std::endl;
  char myChar;

  while (true) {
    myChar = (char) getchar();

    switch (myChar) {
      case 'y':
        insureHand();
        break;
      case 'n':
        noInsurance();
        break;
      default:
        clear();
        drawHands();
        askInsurance();
        break;
    }

    break;
  }
}

void Game::clear() {
  system("export TERM=linux; clear");
}

void Game::dealNewHand() {
  if (shoe.needToShuffle()) {
    std::cout << "omg, reshuffling!" << std::endl;
    shoe.newRegular();
  }

  playerHands = {};
  playerHands.clear();
  PlayerHand::totalPlayerHands = 0;

  PlayerHand *playerHand;
  playerHands.emplace_back(this, currentBet);
  playerHand = &playerHands[0];

  currentPlayerHand = 0;

  dealerHand = DealerHand(this);

  dealerHand.dealCard();
  playerHand->dealCard();
  dealerHand.dealCard();
  playerHand->dealCard();

  if (dealerHand.upCardIsAce() && !playerHand->isBlackjack()) {
    drawHands();
    askInsurance();
    return;
  }

  if (playerHand->isDone()) {
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

void Game::drawHands() {
  clear();
  std::cout << std::endl << " Dealer: " << std::endl;
  dealerHand.draw();
  std::cout << std::endl;

  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::endl << " Player $" << (float) (money / 100.0) << ":" << std::endl;
  for (unsigned i = 0; i < playerHands.size(); ++i) {
    playerHands.at(i).draw(i);
  }
}

void Game::betOptions() {
  std::cout << " (D) Deal Hand  (B) Change Bet  (O) Options  (Q) Quit" << std::endl;

  char myChar;

  while (true) {
    myChar = (char) getchar();

    switch (myChar) {
      case 'd':
        dealNewHand();
        break;
      case 'b':
        getNewBet();
        break;
      case 'o':
        gameOptions();
        break;
      case 'q':
        clear();
        break;
      default:
        clear();
        drawHands();
        betOptions();
    }

    break;
  }
}

void Game::gameOptions() {
  char myChar;

  clear();
  drawHands();
  std::cout << " (N) Number of Decks  (T) Deck Type  (B) Back" << std::endl;

  while (true) {
    myChar = (char) getchar();

    switch (myChar) {
      case 'n':
        getNewNumDecks();
        break;
      case 't':
        getNewDeckType();
        break;
      case 'b':
        clear();
        drawHands();
        betOptions();
        break;
      default:
        clear();
        drawHands();
        gameOptions();
    }

    break;
  }
}

void Game::getNewDeckType() {
  char myChar;

  clear();
  drawHands();
  std::cout << " (1) Regular  (2) Aces  (3) Jacks  (4) Aces & Jacks  (5) Sevens  (6) Eights" << std::endl;

  while (true) {
    myChar = (char) getchar();

    std::cout << "myChar: " << myChar << std::endl;

    switch (myChar) {
      case '1':
        shoe.newRegular();
        break;
      case '2':
        std::cout << "shoe.newAces()" << std::endl;
        shoe.newAces();
        break;
      case '3':
        shoe.newJacks();
        break;
      case '4':
        shoe.newAcesJacks();
        break;
      case '5':
        shoe.newSevens();
        break;
      case '6':
        shoe.newEights();
        break;
      default:
        clear();
        drawHands();
        gameOptions();
    }

    drawHands();
    betOptions();
    break;
  }
}

void Game::getNewBet() {
  clear();
  drawHands();

  std::cout << "  Current Bet: $" << std::put_money(currentBet / 100) << std::endl << "  Enter New Bet: $";
  long double betTmp;
  std::cin >> std::get_money(betTmp);
  auto bet = (unsigned) (betTmp * 100);
  currentBet = bet;

  normalizeCurrentBet();
  dealNewHand();
}

void Game::getNewNumDecks() {
  clear();
  drawHands();

  std::cout << "  Number Of Decks: " << numDecks << std::endl << "  Enter New Number Of Decks: ";
  unsigned tmp;
  std::cin >> tmp;

  if (tmp < 1) tmp = 1;
  if (tmp > 8) tmp = 8;

  numDecks = tmp;
  gameOptions();
}

void Game::insureHand() {
  PlayerHand *h = &playerHands[currentPlayerHand];

  h->bet /= 2;
  h->played = true;
  h->payed = true;
  h->status = Hand::Lost;

  money -= h->bet;

  drawHands();
  betOptions();
}

bool Game::moreHandsToPlay() {
  return currentPlayerHand < playerHands.size() - 1;
}

bool Game::needToPlayDealerHand() {
  for (auto & playerHand : playerHands) {
    PlayerHand *h = &playerHand;

    if (!(h->isBusted() || h->isBlackjack())) {
      return true;
    }
  }

  return false;
}

void Game::noInsurance() {
  if (dealerHand.isBlackjack()) {
    dealerHand.hideDownCard = false;
    dealerHand.played = true;

    payHands();
    drawHands();
    betOptions();
    return;
  }

  PlayerHand *h = &playerHands[currentPlayerHand];
  if (h->isDone()) {
    playDealerHand();
    drawHands();
    betOptions();
    return;
  }

  drawHands();
  h->getAction();
}

void Game::normalizeCurrentBet() {
  if (currentBet < Game::MIN_BET) {
    currentBet = Game::MIN_BET;
  } else if (currentBet > Game::MAX_BET) {
    currentBet = Game::MAX_BET;
  }

  if (currentBet > money) {
    currentBet = money;
  }
}

void Game::payHands() {
  unsigned dhv = dealerHand.getValue(Hand::Soft);
  bool dhb = dealerHand.isBusted();

  for (auto & playerHand : playerHands) {
    PlayerHand *h = &playerHand;

    if (h->payed) {
      continue;
    }

    h->payed = true;

    unsigned phv = h->getValue(Hand::Soft);

    if (dhb || phv > dhv) {
      if (h->isBlackjack()) {
        h->bet = (unsigned) (h->bet * 1.5);
      }

      money += h->bet;
      h->status = Hand::Won;
    } else if (phv < dhv) {
      money -= h->bet;
      h->status = Hand::Lost;
    } else {
      h->status = Hand::Push;
    }
  }

  normalizeCurrentBet();
  saveGame();
}

void Game::playDealerHand() {
  if (dealerHand.isBlackjack()) {
    dealerHand.hideDownCard = false;
  }

  if (!needToPlayDealerHand()) {
    dealerHand.played = true;
    payHands();
    return;
  }

  dealerHand.hideDownCard = false;

  unsigned softCount = dealerHand.getValue(Hand::Soft);
  unsigned hardCount = dealerHand.getValue(Hand::Hard);
  while (softCount < 18 && hardCount < 17) {
    dealerHand.dealCard();
    softCount = dealerHand.getValue(Hand::Soft);
    hardCount = dealerHand.getValue(Hand::Hard);
  }

  dealerHand.played = true;
  payHands();
}

void Game::playMoreHands() {
  ++currentPlayerHand;
  PlayerHand *h = &playerHands[currentPlayerHand];
  h->dealCard();
  if (h->isDone()) {
    h->process();
    return;
  }

  drawHands();
  h->getAction();
}

int Game::run() {
  dealNewHand();
  return 0;
}

void Game::saveGame() {
  std::ofstream saveFile;
  saveFile.open(Game::SAVE_FILE);

  if (saveFile.is_open()) {
    saveFile << numDecks << "|" << money << "|" << currentBet << std::endl;
    saveFile.close();
  } else {
    std::cout << "Could not open file: " << Game::SAVE_FILE << std::endl;
    throw;
  }
}

void Game::loadGame() {
  std::ifstream saveFile;
  saveFile.open(Game::SAVE_FILE);
  if (saveFile.is_open()) {
    std::string line;
    getline(saveFile, line);
    saveFile.close();

    std::vector <std::string> elems;
    std::stringstream ss;
    ss.str(line);
    std::string item;
    while (getline(ss, item, '|')) {
      elems.push_back(item);
    }

    numDecks = (unsigned) stoul(elems[0]);
    money = (unsigned) stoul(elems[1]);
    currentBet = (unsigned) stoul(elems[2]);
  }

  if (money < MIN_BET) {
    money = 10000;
  }
}

void Game::splitCurrentHand() {
  PlayerHand *currentHand = &playerHands[currentPlayerHand];

  if (!currentHand->canSplit()) {
    drawHands();
    currentHand->getAction();
    return;
  }

  playerHands.emplace_back(this, this->currentBet);

  // expand hands
  unsigned x = playerHands.size() - 1;
  while (x > currentPlayerHand) {
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

  if (thisHand->isDone()) {
    thisHand->process();
    return;
  }

  drawHands();
  playerHands[currentPlayerHand].getAction();
}
