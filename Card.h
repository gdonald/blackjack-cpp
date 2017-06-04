#ifndef CARD_H_
#define CARD_H_

#include <string>
#include <sstream>

namespace std
{
	class Card
	{
		public:
			static const char * const faces[14][4];
			static const char * const suites[4];

			int value;
			int suiteValue;
			string suite;

			Card();
			Card(int, int, string);
			virtual ~Card();

			bool isAce();
			bool isTen();

			string toString();
	};
}

#endif
