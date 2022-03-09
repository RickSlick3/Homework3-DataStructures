#pragma once
#include "Card.h"
#include <exception>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <cstdint>


class SidePile : public Card
{

private:
	int sizePile = 0;
	Card* pile[5];

public:
	int seeTopPile();
	void addToPile(Card* pushed);
	Card* takeFromPile();
	int getPileSize() { return sizePile; }

};

struct PileisFull : public std::exception
{
	const char* what() const throw ()
	{
		return "Side pile is full.";
	}
};

struct PileisEmpty : public std::exception
{
	const char* what() const throw ()
	{
		return "Side pile is empty.";
	}
};

void SidePile::addToPile(Card* pushed)
{
	if (this->getPileSize() >= 5)
		throw PileisFull();
	this->pile[sizePile] = pushed;
	sizePile++;
}

Card* SidePile::takeFromPile() 
{
	if (this->getPileSize() <= 0)
		throw PileisEmpty();
	Card* taking = this->pile[sizePile - 1];
	sizePile--;
	return taking;
}

int SidePile::seeTopPile()
{
	return this->pile[sizePile - 1]->cardVal;

}


