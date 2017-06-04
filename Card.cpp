#include "Card.h"

namespace std
{
	const char * const Card::faces[14][4] = { { "🂡", "🂱", "🃁", "🃑" }, { "🂢", "🂲", "🃂", "🃒" }, { "🂣", "🂳", "🃃",
			"🃓" }, { "🂤", "🂴", "🃄", "🃔" }, { "🂥", "🂵", "🃅", "🃕" }, { "🂦", "🂶", "🃆", "🃖" }, { "🂧", "🂷", "🃇",
			"🃗" }, { "🂨", "🂸", "🃈", "🃘" }, { "🂩", "🂹", "🃉", "🃙" }, { "🂪", "🂺", "🃊", "🃚" }, { "🂫", "🂻", "🃋",
			"🃛" }, { "🂭", "🂽", "🃍", "🃝" }, { "🂮", "🂾", "🃎", "🃞" }, { "🂠", "", "", "" }, };

	const char * const Card::suites[4] = { "Spades", "Hearts", "Clubs", "Diamonds" };

	Card::Card(int v, int sv, string s)
	{
		value = v;
		suiteValue = sv;
		suite = s;
	}

	string Card::toString()
	{
		return Card::faces[value][suiteValue];
	}

	bool Card::isAce()
	{
		return value == 0;
	}

	bool Card::isTen()
	{
		return value > 9;
	}

	Card::~Card()
	{
	}
}
