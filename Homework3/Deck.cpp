#include "Deck.h"

Deck::Deck()
{
	
}

void Deck::addCard(Card* adding)
{
	if (this->numCards == 0) {
		top = adding;
		bottom = adding;
	}
	else {
		adding->above = bottom;
		bottom->below = adding;
		bottom = adding;
		bottom->below = nullptr;
	}
	this->numCards++;
}

void Deck::buildDeck(int val)
{
	Card* cardi = new Card();
	cardi->cardVal = val;
	this->addCard(cardi);

}

Card* Deck::takeTopCard()
{
	if (this->numCards == 0) {
		throw DeckisEmpty();
	}
	Card* cardi = top;
	this->numCards--;
	if (this->numCards == 1) {
		top = nullptr;
		bottom = nullptr;
		return cardi;
	}
	else {
		top = top->below;
		top->above = nullptr;
		return cardi;
	}
}

int Deck::seeTopCard()
{
	return top->cardVal;
}

int Deck::getNumCards()
{
	return numCards;
}
