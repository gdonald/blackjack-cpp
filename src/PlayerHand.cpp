#include "PlayerHand.h"
#include "Game.h"

unsigned PlayerHand::totalPlayerHands = 0;

PlayerHand::~PlayerHand() = default;

PlayerHand::PlayerHand(Game *g) : Hand(g) {
  status = Unknown;
}

bool PlayerHand::isBusted() {
  return getValue(Soft) > 21;
}

unsigned PlayerHand::getValue(CountMethod countMethod) {
  unsigned v = 0;
  unsigned total = 0;

  for (auto &card : cards) {
    unsigned tmp_v = card.value + 1;
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

bool PlayerHand::isDone() {
  if (played || stood || isBlackjack() || isBusted() || 21 == getValue(Soft) || 21 == getValue(Hard)) {
    played = true;

    if (!payed) {
      if (isBusted()) {
        payed = true;
        status = Lost;
        game->money -= bet;
      }
    }

    return true;
  }

  return false;
}

bool PlayerHand::canSplit() {
  if (stood || PlayerHand::totalPlayerHands >= PlayerHand::MAX_PLAYER_HANDS) {
    return false;
  }

  if (game->money < game->allBets() + bet) { return false; }

  return cards.size() == 2 && cards[0].value == cards[1].value;
}

bool PlayerHand::canDbl() {
  if (game->money < game->allBets() + bet) { return false; }
  return !(stood || cards.size() != 2 || isBlackjack());
}

bool PlayerHand::canStand() {
  return !(stood || isBusted() || isBlackjack());
}

bool PlayerHand::canHit() {
  return !(played || stood || 21 == getValue(Hard) || isBlackjack() || isBusted());
}

void PlayerHand::hit() {
  dealCard();

  if (isDone()) {
    process();
    return;
  }

  game->drawHands();
  game->playerHands.at(game->currentPlayerHand).getAction();
}

void PlayerHand::dbl() {
  dealCard();
  played = true;
  bet *= 2;

  if (isDone()) { process(); }
}

void PlayerHand::stand() {
  stood = true;
  played = true;

  if (game->moreHandsToPlay()) {
    game->playMoreHands();
    return;
  }

  game->playDealerHand();
  game->drawHands();
  game->betOptions();
}

void PlayerHand::process() {
  if (game->moreHandsToPlay()) {
    game->playMoreHands();
    return;
  }

  game->playDealerHand();
  game->drawHands();
  game->betOptions();
}

void PlayerHand::draw(unsigned index) {
  std::cout << " ";

  for (auto &card : cards) {
    std::cout << card.toString() << " ";
  }

  std::cout << " ⇒  " << getValue(Soft) << "  ";

  if (status == Hand::Lost) { std::cout << "-"; }
  else if (status == Hand::Won) { std::cout << "+"; }

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "$" << (float) (bet / 100.0);

  if (!played && index == game->currentPlayerHand) {
    std::cout << " ⇐";
  }

  std::cout << "  ";

  if (status == Lost) {
    if (isBusted()) { std::cout << "Busted!"; }
    else { std::cout << "Lose!"; }
  } else if (status == Won) {
    if (isBlackjack()) { std::cout << "Blackjack!"; }
    else { std::cout << "Won!"; }
  } else if (status == Push) {
    std::cout << "Push";
  }

  std::cout << std::endl << std::endl;
}

void PlayerHand::getAction() {
  std::cout << " ";
  if (canHit()) { std::cout << "(H) Hit  "; }
  if (canStand()) { std::cout << "(S) Stand  "; }
  if (canSplit()) { std::cout << "(P) Split  "; }
  if (canDbl()) { std::cout << "(D) Double  "; }
  std::cout << std::endl;

  char myChar;

  while (true) {
    myChar = (char) getchar();

    switch (myChar) {
      case 'h':;
        hit();
        break;
      case 's':;
        stand();
        break;
      case 'p':;
        game->splitCurrentHand();
        break;
      case 'd':;
        dbl();
        break;
      default:;
        Game::clear();
        game->drawHands();
        getAction();
    }

    break;
  }
}
