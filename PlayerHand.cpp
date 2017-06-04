#include "PlayerHand.h"
#include "Game.h"

namespace std
{
	unsigned PlayerHand::totalPlayerHands = 0;

	unsigned PlayerHand::getValue(CountMethod countMethod)
	{
		unsigned v = 0;
		unsigned total = 0;

		for(unsigned x = 0; x < cards.size(); ++x)
		{
			unsigned tmp_v = cards.at(x).value + 1;
			v = tmp_v > 9 ? 10 : tmp_v;

			if (countMethod == Soft && v == 1 && total < 11)
			{
				v = 11;
			}

			total += v;
		}

		if (countMethod == Soft && total > 21)
		{
			return getValue(Hard);
		}

		return total;
	}

	bool PlayerHand::isDone()
	{
		if (played || stood || isBlackjack() || isBusted() || 21 == getValue(Soft) || 21 == getValue(Hard))
		{
			played = true;

			if (!payed)
			{
				if (isBusted())
				{
					payed = true;
					status = Lost;
					game->money -= bet;
				}
			}

			return true;
		}

		return false;
	}

	bool PlayerHand::canSplit()
	{
		if (stood || PlayerHand::totalPlayerHands >= PlayerHand::MAX_PLAYER_HANDS)
		{
			return false;
		}

		if(game->money < game->allBets() + bet)
		{
			return false;
		}

		if (cards.size() == 2 && cards[0].value == cards[1].value)
		{
			return true;
		}

		return false;
	}

	bool PlayerHand::canDbl()
	{
		if(game->money < game->allBets() + bet)
		{
			return false;
		}

		if (stood || cards.size() != 2 || isBusted() || isBlackjack())
		{
			return false;
		}

		return true;
	}

	bool PlayerHand::canStand()
	{
		if (stood || isBusted() || isBlackjack())
		{
			return false;
		}

		return true;
	}

	bool PlayerHand::canHit()
	{
		if (played || stood || 21 == getValue(Hard) || isBlackjack() || isBusted())
		{
			return false;
		}

		return true;
	}

	void PlayerHand::hit()
	{
		dealCard();

		if (isDone())
		{
			process();
			return;
		}

		game->drawHands();
		game->playerHands.at(game->currentPlayerHand).getAction();
	}

	void PlayerHand::dbl()
	{
		dealCard();
		played = true;
		bet *= 2;

		if (isDone())
		{
			process();
		}
	}

	void PlayerHand::stand()
	{
		stood = true;
		played = true;

		if (game->moreHandsToPlay())
		{
			game->playMoreHands();
			return;
		}

		game->playDealerHand();
		game->drawHands();
		game->drawPlayerBetOptions();
	}

	void PlayerHand::process()
	{
		if (game->moreHandsToPlay())
		{
			game->playMoreHands();
			return;
		}

		game->playDealerHand();
		game->drawHands();
		game->drawPlayerBetOptions();
	}

	void PlayerHand::draw(unsigned index)
	{
		cout << " ";

		for(unsigned i = 0; i < cards.size(); ++i)
		{
			cout << cards.at(i).toString() << " ";
		}

		cout << " ⇒  " << getValue(Soft) << "  ";

		if (status == Hand::Lost)
		{
			cout << "-";
		}
		else if (status == Hand::Won)
		{
			cout << "+";
		}

		cout << fixed << setprecision(2);
		cout << "$" << (float)(bet / 100.0);

		if (!played && index == game->currentPlayerHand)
		{
			cout << " ⇐";
		}

		cout << "  ";

		if (status == Lost)
		{
			if (isBusted())
			{
				cout << "Busted!";
			}
			else
			{
				cout << "Lose!";
			}
		}
		else if (status == Won)
		{
			if (isBlackjack())
			{
				cout << "Blackjack!";
			}
			else
			{
				cout << "Won!";
			}
		}
		else if (status == Push)
		{
			cout << "Push";
		}

		cout << endl << endl;
	}

	void PlayerHand::getAction()
	{
		cout << " ";

		if (canHit())
		{
			cout << "(H) Hit  ";
		}

		if (canStand())
		{
			cout << "(S) Stand  ";
		}

		if (canSplit())
		{
			cout << "(P) Split  ";
		}

		if (canDbl())
		{
			cout << "(D) Double  ";
		}
		cout << endl;

		bool br = false;
		char myChar = { 0 };

		while(true)
		{
			myChar = getchar();

			switch(myChar)
			{
				case 'h':
					br = true;
					hit();
					break;
				case 's':
					br = true;
					stand();
					break;
				case 'p':
					br = true;
					game->splitCurrentHand();
					break;
				case 'd':
					br = true;
					dbl();
					break;
				default:
					br = true;
					game->clear();
					game->drawHands();
					getAction();
			}

			if (br)
			{
				break;
			}
		}
	}

	PlayerHand::~PlayerHand()
	{
	}
}
