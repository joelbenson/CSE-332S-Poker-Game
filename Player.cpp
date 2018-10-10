// Player.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file defines a Player struct and functions,
// and includes support for both player automation 
// and betting and folding
//
// Lab 4

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Player::Player(const char * name)
{
	playerBet = 0;
	folded = false;
	//
	if (name[strlen(name) - 1] == '*') {
		automated = true;
	}
	else {
		automated = false;
	}
	stayingProbability = 100;
	//
	int wordCount = 0;
	string filename = name;

	///
	if (automated) {
		filename.pop_back();
	}
	///
	filename = filename + ".txt";
	ifstream ifs;
	ifs.open(filename);

	if (ifs.is_open())
	{
		string line, word;
		getline(ifs, line);
		istringstream iss(line);

		if (iss >> word)
		{
			wordCount = wordCount + 1;
			playerName = word;
		}


		if (iss >> word)
		{
			wordCount = wordCount + 1;
			stringstream wins(word);
			wins >> playerWins;
		}


		if (iss >> word)
		{
			wordCount = wordCount + 1;
			stringstream losses(word);
			losses >> playerLosses;
		}

		if (iss >> word)
		{
			wordCount = wordCount + 1;
			stringstream chips(word);
			chips >> playerChips;
		}

		/////////////
		if (wordCount != 4)
		{
			playerName = name;
			playerWins = 0;
			playerLosses = 0;
			playerChips = 20;
		}
	}

	else
	{
		playerName = name;
		playerWins = 0;
		playerLosses = 0;
		playerChips = 20;
	}
}

ostream & operator<< (ostream & out, const Player & printingPlayer)
{
	string printableString = "Player Name: " + printingPlayer.playerName +
		" | Number of Wins: " + to_string(printingPlayer.playerWins) + " Numer of Losses: "
		+ to_string(printingPlayer.playerLosses) + "\n Chips remaining: " + to_string(printingPlayer.playerChips);


	constPrintPokerHand(printingPlayer.playerHand);
	out << printableString << endl;

	return out;
}

///
string automateLine(Player & player) {

	vector<Card> hand = player.playerHand.cardVector;
	sortCardVector(hand);

	int handSize = hand.size();
	rankHand(player.playerHand);

	int handRank = player.playerHand.bestHand;
	bool discardCards[5] = { false };	//HOW CAN YOU DO THIS WITHOUT USING CONSTANT 5?

	string automatedLine = "";

	bool straightFlushHand = (handRank == straight_flush);
	bool fullHouseHand = (handRank == full_house);
	bool straightHand = (handRank == straight);
	bool flushHand = (handRank == pokerHandEnum::flush);
	bool fourOfAKindHand = (handRank == four_of_a_kind);
	bool twoPairHand = (handRank == two_pairs);
	bool threeOfAKindHand = (handRank == three_of_a_kind);
	bool onePairHand = (handRank == one_pair);
	bool noRankHand = (handRank == no_rank);

	int i = 0;

	if (((straightFlushHand || fullHouseHand) || straightHand) || flushHand) {
		return "none";
	}
	else if (((fourOfAKindHand || twoPairHand) || threeOfAKindHand) || onePairHand) {

		if (hand[0].cardRank != hand[1].cardRank) {
			discardCards[0] = true;
		}

		for (i = 1; i < handSize - 1; i = i + 1) {
			if ((hand[i - 1].cardRank != hand[i].cardRank) && (hand[i].cardRank != hand[i + 1].cardRank)) {
				discardCards[i] = true;
			}
		}

		if (hand[handSize - 1].cardRank != hand[handSize - 2].cardRank) {
			discardCards[handSize - 1] = true;
		}

	}
	else if (noRankHand) {
		if (hand[handSize - 1].cardRank == ace) {
			for (i = 0; i < handSize - 1; i = i + 1) {
				discardCards[i] = true;
			}
		}
		else {
			for (i = 0; i < handSize - 2; i = i + 1) {
				discardCards[i] = true;
			}
		}
	}

	for (i = 0; i < handSize; i = i + 1) {
		if (discardCards[i]) {
			automatedLine = automatedLine + to_string(i) + " ";
		}
	}

	return automatedLine;
}
///