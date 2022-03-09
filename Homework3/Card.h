#pragma once
class Card
{
public:
	int cardVal = 0;
	Card* above = nullptr;
	Card* below = nullptr;
};

