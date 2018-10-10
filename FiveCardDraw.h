// FiveCardDraw.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the class FiveCardDraw, which
// is a derived class of game.  It also declares the
// pure virtual functions that come from game.
//
// Lab 4

#pragma once
#include "Game.h"
#include "Deck.h"


class FiveCardDraw : public Game
{
private:

protected:
	size_t dealerPosition;
	Deck discardDeck;

public:
	FiveCardDraw();
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	////
	bool roundOver;
	unsigned int countFolds(vector<shared_ptr<Player>> & playerVector);
	void bettingRound(vector<shared_ptr<Player>> &, unsigned int &, unsigned int &);
	void bettingTurn(Player &, unsigned int &, unsigned int &);
};
