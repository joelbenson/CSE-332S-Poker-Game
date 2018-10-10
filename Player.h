// Player.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file declares a Player struct and functions,
// and includes support for both player automation 
// and betting and folding
//
// Lab 4

#pragma once
#include "Hand.h"
#include <string>

using namespace std;



struct Player
{
	Player(const char*);
	string playerName;
	Hand playerHand;
	unsigned int playerWins;
	unsigned int playerLosses;
	unsigned int playerChips;
	bool folded;
	unsigned int playerBet;

	//
	int stayingProbability;
	bool automated;
	//
};

// Non-member Player insertion operator to ostream
ostream & operator<< (ostream &, const Player &);

//
string automateLine(Player &);
//
