#include "Shoe.h"

namespace std
{
  const unsigned Shoe::shuffleSpecs[8][2] = { { 95, 8 },
					      { 92, 7 },
					      { 89, 6 },
					      { 86, 5 },
					      { 84, 4 },
					      { 82, 3 },
					      { 81, 2 },
					      { 80, 1 } };

  Shoe::Shoe()
  {
    numDecks = 1;
  }

  Shoe::Shoe(unsigned nd) : numDecks(nd)
  {
  }
  
  bool Shoe::needToShuffle()
  {
    if (cards.size() == 0)
    {
      return true;
    }
    
    unsigned totalCards = numDecks * 52;
    unsigned cardsDealt = totalCards - cards.size();
    unsigned used = (cardsDealt / (double) totalCards) * 100.0;
    
    for(unsigned x = 0; x < 8; ++x)
    {
      if (used > Shoe::shuffleSpecs[x][0] && numDecks == Shoe::shuffleSpecs[x][1])
      {
	return true;
      }
    }
    
    return false;
  }
  
  void Shoe::shuffle()
  {
    std::random_device rng;
    std::mt19937 urng(rng());

    for(unsigned i = 0; i < 7; ++i)
    {
      std::shuffle(cards.begin(), cards.end(), urng);
    }
  }
  
  void Shoe::newAcesJacks()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks * 4; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	cards.push_back(Card(0, suite));
	cards.push_back(Card(10, suite));
      }
    }

    shuffle();
  }
  
  void Shoe::newJacks()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks * 5; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	cards.push_back(Card(10, suite));
      }
    }
  }
  
  void Shoe::newAces()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks * 5; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	cards.push_back(Card(0, suite));
      }
    }
  }
  
  void Shoe::newSevens()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks * 5; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	cards.push_back(Card(6, suite));
      }
    }
  }
  
  void Shoe::newEights()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks * 5; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	cards.push_back(Card(7, suite));
      }
    }
  }
  
  void Shoe::newRegular()
  {
    cards.clear();
    
    for(unsigned deck = 0; deck < numDecks; ++deck)
    {
      for(unsigned suite = 0; suite < 4; ++suite)
      {
	for(unsigned value = 0; value < 13; ++value)
	{
	  cards.push_back(Card(value, suite));
	}
      }
    }

    shuffle();
  }
  
  Card Shoe::getNextCard()
  {
    Card c = cards.back();
    cards.pop_back();
    return c;
  }
  
  Shoe::~Shoe()
  {
  }
}
