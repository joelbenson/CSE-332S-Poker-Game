// SevenCardStud.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the class SevenCardStud, which
// is a derived class of game.  It also declares the
// pure virtual functions that come from game.
//
// Lab 4

#pragma once
#include "Game.h"
#include "Deck.h"


class SevenCardStud : public Game
{
private:

protected:
	size_t dealerPosition;
	Deck discardDeck;

public:
	// Default Constructor
	SevenCardStud();
	// Shows the player their hand and then asks them if they want to 
	// discard any cards, and discards them if necessary
	virtual int before_turn(Player &);
	// Adds cards to the hand so that a player has five cards and then
	// ranks the new hand
	virtual int turn(Player &);
	// Print out the results of the new player hand and the
	// best rank of that hand
	virtual int after_turn(Player &);
	// Shuffles the deck and starting with one past the 
	// dealer deals out all of the cards, and then 
	// calls before turn for all of the players
	virtual int before_round();
	// Goes through all of the players starting with one past the dealer and
	// calls turn and after turn, handling all exceptions
	virtual int round();
	// Takes all of the players and ranks them by their best hand,
	// and then assigns wins and losses appropriately. Asks if any
	// players want to join or leave and reponds appropriately
	virtual int after_round();
	////////
	void bettingRound(vector<shared_ptr<Player>> &, unsigned int &, unsigned int &);
	void bettingTurn(Player &, unsigned int &, unsigned int &);
	bool roundOver;
	unsigned int countFolds(vector<shared_ptr<Player>> & playerVector);
};
