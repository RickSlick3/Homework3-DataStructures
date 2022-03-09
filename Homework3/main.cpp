#pragma once
#include "Card.h"
#include "Deck.h"
#include "SidePile.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <random>
#include <algorithm>

using namespace std;

int main(void) {

	//creating and populating decks

	Deck userDeck = Deck();
	Deck compDeck = Deck();
	SidePile userPile = SidePile();
	SidePile compPile = SidePile();

	int fullDeck[52];
	int i = 0;
	for (int x = 1; x < 14; x++) {
		for (int y = 1; y <= 4; y++) {
			fullDeck[i] = x;
			i++;
		}
	}
	random_shuffle(&fullDeck[0], &fullDeck[51]);

	for (int x = 0; x < 26; x++) {
		userDeck.buildDeck(fullDeck[x]);
	}
	for (int x = 26; x < 52; x++) {
		compDeck.buildDeck(fullDeck[x]);
	}

	// start the game 
	
	bool game = true;
	int input;
	while (game) {
		cout << "Should the winner be the last one with cards, or the player that wins the most turns? (0 or 1): ";
		cin >> input;
		cin.ignore();
		cout << endl << "-----START GAME-----" << endl << endl;

		if (input == 0 || input == 1) {
			game = false;
		}
		else {
			cout << "\nNot a valid game selection.\n";
		}
	}
	int userW = 0;
	int compW = 0;
	int turn = 1;
	while (((userDeck.getNumCards() != 0 || userPile.getPileSize() != 0) && (compDeck.getNumCards() != 0 || compPile.getPileSize() != 0)) && game == false) {
		cout << endl << "Turn " << turn << endl;
		cout << "You have " << userDeck.getNumCards() + userPile.getPileSize() << " cards and the computer has " 
				<< compDeck.getNumCards() + compPile.getPileSize() << " cards." << endl;
		cout << "Your top card is a " << userDeck.seeTopCard() << " and your side pile has " 
				<< userPile.getPileSize() << " cards, what do you want to do? " << endl;
		cout << "Press 1 to play the top card\nPress 2 to play a second card from your side pile\npress 3 to push card to side pile and play the second card in your deck\nPress 4 to quit\n";
		cout << "Your Choice: ";
		int userInput = 0;
		cin >> userInput;

		// make sure there are cards in the users/comps deck
		if (userDeck.getNumCards() == 0) {
			userDeck.addCard(userPile.takeFromPile());
		}
		if (compDeck.getNumCards() == 0) {
			compDeck.addCard(compPile.takeFromPile());
		}

		// computer strategy
		int compCards = 1;
		if ((compDeck.getNumCards() + compPile.getPileSize()) >= 2) {
			if (compDeck.seeTopCard() <= 5) {
				if (compPile.getPileSize() != 0) {
					compCards = 2;
				}
				else if (compPile.getPileSize() < 5) {
					compPile.addToPile(compDeck.takeTopCard());
				}
			}
		}
		

		// user move based on input
		switch (userInput)
		{
		case 1:
			if (compCards == 1 && compDeck.getNumCards() != 0) {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 1 card: " << compDeck.seeTopCard() << endl;
				if (userDeck.seeTopCard() > compDeck.seeTopCard()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compDeck.takeTopCard());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compDeck.takeTopCard());
					compW++;
				}
			}
			else if (compCards == 1 && compDeck.getNumCards() == 0) {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 1 card: " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() > compPile.seeTopPile()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}
			else {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 2 cards: " << compDeck.seeTopCard() << " and " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() > (compDeck.seeTopCard() + compPile.seeTopPile())) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compDeck.takeTopCard());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compDeck.takeTopCard());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}
			break;

		case 2:
			if (compCards == 1 && compDeck.getNumCards() != 0) {
				cout << "\nYou played 2 cards: " << userDeck.seeTopCard() << " and " << userPile.seeTopPile() << ". The computer played 1 card: " << compDeck.seeTopCard() << endl;
				if (userDeck.seeTopCard() + userPile.seeTopPile() > compDeck.seeTopCard()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(userPile.takeFromPile());
					userDeck.addCard(compDeck.takeTopCard());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(userPile.takeFromPile());
					compDeck.addCard(compDeck.takeTopCard());
					compW++;
				}
			}
			else if (compCards == 1 && compDeck.getNumCards() == 0) {
				cout << "\nYou played 2 cards: " << userDeck.seeTopCard() << " and " << userPile.seeTopPile() << ". The computer played 1 card: " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() + userPile.seeTopPile() > compDeck.seeTopCard()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(userPile.takeFromPile());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(userPile.takeFromPile());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}
			else {
				cout << "\nYou played 2 cards: " << userDeck.seeTopCard() << " and " << userPile.seeTopPile() << ". The computer played 2 cards: " << compDeck.seeTopCard() << " and " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() + userPile.seeTopPile() > (compPile.seeTopPile() + compPile.seeTopPile())) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(userPile.takeFromPile());
					userDeck.addCard(compDeck.takeTopCard());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(userPile.takeFromPile());
					compDeck.addCard(compDeck.takeTopCard());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}

			break;
		case 3:
			userPile.addToPile(userDeck.takeTopCard());
			cout << "top card was pushed to your side pile" << endl;
			if (compCards == 1 && compDeck.getNumCards() != 0) {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 1 card: " << compDeck.seeTopCard() << endl;
				if (userDeck.seeTopCard() > compDeck.seeTopCard()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compDeck.takeTopCard());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compDeck.takeTopCard());
					compW++;
				}
			}
			else if (compCards == 1 && compDeck.getNumCards() == 0) {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 1 card: " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() > compPile.seeTopPile()) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}
			else {
				cout << "\nYou played 1 card: " << userDeck.seeTopCard() << ". The computer played 2 cards: " << compDeck.seeTopCard() << " and " << compPile.seeTopPile() << endl;
				if (userDeck.seeTopCard() > (compPile.seeTopPile() + compPile.seeTopPile())) {
					cout << "\nthe user won this round\n" << endl;
					userDeck.addCard(userDeck.takeTopCard());
					userDeck.addCard(compDeck.takeTopCard());
					userDeck.addCard(compPile.takeFromPile());
					userW++;
				}
				else {
					cout << "\nthe computer won this round\n" << endl;
					compDeck.addCard(userDeck.takeTopCard());
					compDeck.addCard(compDeck.takeTopCard());
					compDeck.addCard(compPile.takeFromPile());
					compW++;
				}
			}

			break;
		case 4:
			cout << "\nThe user quit the Game\n";
			game = true;
			break;
		default:
			cout << "That is not an option" << endl;
			break;
		}
		turn++;
	}
	if (input == 0) {
		cout << "Cards left: " << userDeck.getNumCards() + userPile.getPileSize() << " - " << compDeck.getNumCards() + compPile.getPileSize() << endl;
		if ((userDeck.getNumCards() + userPile.getPileSize()) > (compDeck.getNumCards() + compPile.getPileSize())) {
			cout << "THE USER WON\n";
		}
		else {
			cout << "THE COMPUTER WON\n";
		}
	}
	else {
		cout << "Turns won: " << userW << " - " << compW << endl;
		if (userW > compW) {
			cout << "THE USER WON\n";
		}
		else {
			cout << "THE COMPUTER WON\n";
		}
		
	}

}