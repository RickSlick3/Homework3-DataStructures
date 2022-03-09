#pragma once
#include "Card.h"
#include <exception>

class Deck : public Card
{

private:
	int numCards = 0;
	Card* top = nullptr;
	Card* bottom = nullptr;

public:
	Deck();
	void addCard(Card* adding);
	void buildDeck(int val);
	Card* takeTopCard();
	int seeTopCard();
	int getNumCards();
};

struct DeckisEmpty : public std::exception
{
	const char* what() const throw ()
	{
		return "deck is empty.";
	}
};


