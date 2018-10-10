// SevenCardStud.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the class SevenCardStud, which
// is a derived class of game.  It also defines the
// pure virtual functions that come from game.
//
// Lab 4

#include "stdafx.h"
#include "SevenCardStud.h"
#include "Game.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Utilities.h"
#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Player.h"
using namespace std;

// Default constructor for a game of SevenCardStud
SevenCardStud::SevenCardStud()
{
	///////
	roundOver = false;
	////////
	dealerPosition = 0;
	discardDeck;
	gameDeck;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			Card tempCard;
			tempCard.suit = static_cast<suitEnum>(i);
			tempCard.cardRank = static_cast<cardRankEnum>(j);
			gameDeck.addCard(tempCard);
		}
	}
}

// Shows the player their hand and then asks them if they want to 
// discard any cards, and discards them if necessary
int SevenCardStud::before_turn(Player & currentPlayer)
{
	string testinput;
	cout << endl << currentPlayer.playerName << "'s Turn" << endl;
	for (size_t i = 0; i < playerVector.size(); ++i)
	{
		if ((*playerVector[i]).playerName == currentPlayer.playerName)
		{
			cout << "Player " << (*playerVector[i]).playerName << " has cards:" << endl;
			string playersCards = (*playerVector[i]).playerHand.cardAsString();
			cout << playersCards << endl;
		}
		else
		{
			if (!(*playerVector[i]).folded) {
				cout << "Player " << (*playerVector[i]).playerName << " has cards:" << endl;
				string playersCards = (*playerVector[i]).playerHand.othercardAsString();
				cout << playersCards << endl;
			}
			else {
				cout << "Player " << (*playerVector[i]).playerName << " has folded." << endl;
			}
		}

	}

	return success;
}


// Adds cards to the hand so that a player has five cards and then
// ranks the new hand
int SevenCardStud::turn(Player & currentPlayer)
{

	if (gameDeck.sizeDeck() > 0)
	{
		currentPlayer.playerHand << gameDeck;
	}

	else if ((gameDeck.sizeDeck()) == 0 && (discardDeck.sizeDeck() > 0))
	{
		discardDeck.shuffleDeck();
		currentPlayer.playerHand << discardDeck;
	}

	else
	{
		return both_decks_empty;
	}


	return success;
}

// Print out the results of the new player hand and the
// best rank of that hand
int SevenCardStud::after_turn(Player & currentPlayer)
{
	if (!currentPlayer.folded) {
		if (currentPlayer.playerHand.sizeHand() >= 7)
		{
			cout << endl << "After Turn!" << endl;
			sortCardVector(currentPlayer.playerHand.getCardVector());
			rankHand(currentPlayer.playerHand);
			cout << "Player " << currentPlayer.playerName << " has cards:" << endl;
			string playersCards = currentPlayer.playerHand.cardAsString();
			cout << playersCards << endl;
			printPokerHand(currentPlayer.playerHand);
		}
	}
	else
	{
		cout << endl << "Player: " << currentPlayer.playerName << " has folded." << endl;
	}
	return success;
}

// Shuffles the deck and starting with one past the 
// dealer deals out all of the cards, and then 
// calls before turn for all of the players
int SevenCardStud::before_round()
{
	roundOver = false;
	gameDeck.shuffleDeck();

	bool dealtCardLastRound = true;
	bool dealtFirst = false;
	int numberPlayers = playerVector.size();
	size_t firstToBeDealt = (dealerPosition + 1) % numberPlayers;
	size_t currentPosition = firstToBeDealt;
	int anteAmount = 1;

	int j = 0;
	for (j = 0; j < numberPlayers; ++j) {
		(*playerVector[j]).playerChips -= anteAmount;
		chipPot += anteAmount;
	}
	cout << "An ante of " << anteAmount << " chip has been taken from each player in the game." << endl;

	while (dealtCardLastRound)
	{
		currentPosition = firstToBeDealt;
		dealtCardLastRound = false;
		dealtFirst = false;

		while (!(dealtFirst && (currentPosition == firstToBeDealt)))
		{
			if (currentPosition == firstToBeDealt)
			{
				dealtFirst = true;
			}

			if ((*playerVector[currentPosition]).playerHand.sizeHand() < 3)
			{
				try
				{
					(*playerVector[currentPosition]).playerHand << gameDeck;
					dealtCardLastRound = true;
				}

				catch (...)
				{
					cout << "Deck Out of Cards and before_round called." << endl;
				}
			}

			currentPosition = (currentPosition + 1) % numberPlayers;
		}
	}



	if (!roundOver) {
		betRequirement = 0;
		bettingRound(playerVector, chipPot, betRequirement);
	}
	if (countFolds(playerVector) >= (playerVector.size() - 1)) {
		roundOver = true;
	}

	return success;
}

// Goes through all of the players starting with one past the dealer and
// calls turn and after turn, handling all exceptions
int SevenCardStud::round()
{
	int i = 0;
	while (i < 4)
	{
		int numberPlayers = playerVector.size();
		size_t firstToBeDealt = (dealerPosition + 1) % numberPlayers;
		size_t currentPosition = firstToBeDealt;
		bool passedFirst = false;
		currentPosition = firstToBeDealt;

		while (!(passedFirst && (currentPosition == firstToBeDealt)))
		{
			if (currentPosition == firstToBeDealt)
			{
				passedFirst = true;
			}

			if (countFolds(playerVector) >= (playerVector.size() - 1)) {
				roundOver = true;
			}
			try
			{
				if (!(*playerVector[currentPosition]).folded && !roundOver) {
					turn((*playerVector[currentPosition]));
				}
			}

			catch (returnMessages f)
			{
				return f;
			}

			catch (...)
			{
				return unknownException;
			}
			if (countFolds(playerVector) >= (playerVector.size() - 1)) {
				roundOver = true;
			}

			currentPosition = (currentPosition + 1) % numberPlayers;
		}
		if (!roundOver) {
			betRequirement = 0;
			bettingRound(playerVector, chipPot, betRequirement);
		}
		i = i + 1;
		if (countFolds(playerVector) >= (playerVector.size() - 1)) {
			roundOver = true;
		}
	}
	int numberPlayers = playerVector.size();
	size_t firstToBeDealt = (dealerPosition + 1) % numberPlayers;
	size_t currentPosition = firstToBeDealt;
	bool passedFirst = false;
	currentPosition = firstToBeDealt;

	while (!(passedFirst && (currentPosition == firstToBeDealt)))
	{
		if (currentPosition == firstToBeDealt)
		{
			passedFirst = true;
		}

		after_turn((*playerVector[currentPosition]));
		currentPosition = (currentPosition + 1) % numberPlayers;

	}

	return success;
}

// Takes all of the players and ranks them by their best hand,
// and then assigns wins and losses appropriately. Asks if any
// players want to join or leave and reponds appropriately
int SevenCardStud::after_round()
{
	cout << endl << "Round Over!" << endl << endl;

	vector<shared_ptr<Player>> tempPlayerVector = playerVector;
	vector<shared_ptr<Player>>::iterator startPointerToPlayer = tempPlayerVector.begin();
	vector<shared_ptr<Player>>::iterator endPointerToPlayer = tempPlayerVector.end();
	vector<shared_ptr<Player>>::iterator i;
	vector<shared_ptr<Player>>::iterator j;
	vector<shared_ptr<Player>>::iterator k;
	vector<shared_ptr<Player>>::iterator l;
	vector<shared_ptr<Player>>::iterator m;
	vector<shared_ptr<Player>>::iterator p;

	bool firstLoserLost = false;

	sort(startPointerToPlayer, endPointerToPlayer, poker_rank_players);

	startPointerToPlayer = tempPlayerVector.begin();
	endPointerToPlayer = tempPlayerVector.end();

	pokerHandEnum bestPlayerHand = (*(*startPointerToPlayer)).playerHand.bestHand;

	// This will assign wins and losses
	for (i = startPointerToPlayer; i != endPointerToPlayer; ++i)
	{
		bool handEquality = false;
		if ((*(*i)).playerHand.bestHand == bestPlayerHand)
		{
			///////////
			int numWinners = 0;
			for (p = startPointerToPlayer; p != endPointerToPlayer; ++p) {
				if ((((poker_rank((*(*startPointerToPlayer)).playerHand, (*(*p)).playerHand)
					&& poker_rank((*(*p)).playerHand, (*(*startPointerToPlayer)).playerHand)))
					|| (!(poker_rank((*(*startPointerToPlayer)).playerHand, (*(*p)).playerHand))
						&& !(poker_rank((*(*p)).playerHand, (*(*startPointerToPlayer)).playerHand)))) && !(*(*p)).folded) {
					numWinners += 1;
				}
			}
			////////////


			// Checks if two players are equal according to the poker rank player function
			handEquality = ((poker_rank((*(*startPointerToPlayer)).playerHand, (*(*i)).playerHand)
				&& poker_rank((*(*i)).playerHand, (*(*startPointerToPlayer)).playerHand)))
				|| (!(poker_rank((*(*startPointerToPlayer)).playerHand, (*(*i)).playerHand))
					&& !(poker_rank((*(*i)).playerHand, (*(*startPointerToPlayer)).playerHand)));

			if (handEquality && !(*(*i)).folded)
			{
				(*(*i)).playerWins = (*(*i)).playerWins + 1;
				////////
				(*(*i)).playerChips = (*(*i)).playerChips + (chipPot / numWinners);
				/////////
			}

			else
			{
				(*(*i)).playerLosses = (*(*i)).playerLosses + 1;
			}
		}

		else
		{
			if (!firstLoserLost)
			{
				firstLoserLost = true;
				m = i;
			}

			(*(*i)).playerLosses = (*(*i)).playerLosses + 1;
		}
	}


	for (j = startPointerToPlayer; j != endPointerToPlayer; ++j)
	{

		cout << (*(*j));
		///////////////
		if (!((*(*j)).folded))
		{
			cout << "Played through round." << endl;
		}
		else
		{
			cout << "Folded during round." << endl;
		}

		cout << endl;
		/////////////////
	}
	//////RESET POT AND BET REQUIREMENT
	chipPot = 0;
	betRequirement = 0;
	roundOver = false;
	//////


	// Clears all of the decks and hands

	gameDeck.clearDeck();
	discardDeck.clearDeck();

	for (k = startPointerToPlayer; k != endPointerToPlayer; ++k)
	{
		(*(*k)).playerHand.clearHand();
		///////RESET ANY HANDS THAT FOLDED
		(*(*k)).folded = false;
		////////
	}

	// Adds a fresh deck of cards and shuffles
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			Card tempCard;
			tempCard.suit = static_cast<suitEnum>(i);
			tempCard.cardRank = static_cast<cardRankEnum>(j);
			gameDeck.addCard(tempCard);
		}
	}

	gameDeck.shuffleDeck();
	bool playersDoneLeaving = false;
	string playerLeaving = "";

	// Checks if any players want to leave
	while (!playersDoneLeaving)
	{
		string trashString;
		cout << "Do any players want to leave the game? (Type 'yes' or 'no')" << endl;
		cin >> playerLeaving;
		if (playerLeaving == "yes")
		{
			string playerName;
			cout << "Type the name of the player exactly" << endl;
			cin >> playerName;
			remove_player(playerName);
		}

		else if (playerLeaving == "no")
		{
			playersDoneLeaving = true;
		}

		else
		{

		}

	}

	bool playersDoneJoining = false;
	string playerJoining = "";

	// Checks if any players want to join
	while (!playersDoneJoining)
	{
		string trashString;
		cout << "Do any players want to join the game? (Type 'yes' or 'no')" << endl;
		cin >> playerJoining;
		if (playerJoining == "yes")
		{
			string playerToAdd;
			cout << "Type the name of the player exactly" << endl;
			cin >> playerToAdd;

			try
			{
				add_player(playerToAdd);
			}

			catch (...)
			{
				cout << "This player is already in the game!" << endl;
			}
		}

		else if (playerJoining == "no")
		{
			playersDoneJoining = true;
		}

		else
		{

		}

	}


	// Increments the dealer position
	unsigned int numberPlayers = playerVector.size();

	if ((dealerPosition + 1) < numberPlayers)
	{
		dealerPosition = dealerPosition + 1;
	}

	else
	{
		dealerPosition = 0;
	}

	return success;
}

void SevenCardStud::bettingRound(vector<shared_ptr<Player>> & playerVector, unsigned int & chipPot, unsigned int & betRequirement) {
	bool phaseOver = false;
	unsigned int numPlayers = playerVector.size();
	unsigned int i = 0;
	unsigned int playersReady = 0;
	betRequirement = 0;


	while (!phaseOver)
	{
		for (i = 0; i < numPlayers; ++i)
		{
			if (!(*playerVector[i]).folded) {
				before_turn((*playerVector[i]));
				bettingTurn((*playerVector[i]), chipPot, betRequirement);
			}
		}


		playersReady = 0;
		for (i = 0; i < numPlayers; ++i)
		{
			if (((*playerVector[i]).playerBet == betRequirement) || (*playerVector[i]).folded)
			{
				playersReady += 1;
			}
			else if ((*playerVector[i]).playerBet == (*playerVector[i]).playerChips) {
				playersReady += 1;
			}
		}

		if (playersReady == numPlayers)
		{
			phaseOver = true;
		}
	}
	for (i = 0; i < numPlayers; ++i)
	{
		chipPot += (*playerVector[i]).playerBet;
		if ((*playerVector[i]).playerChips >= (*playerVector[i]).playerBet) {
			(*playerVector[i]).playerChips -= (*playerVector[i]).playerBet;
		}
		else {
			(*playerVector[i]).playerChips = 0;
		}
		(*playerVector[i]).playerBet = 0;
	}
	betRequirement = 0;
	cout << "The pot is at " << chipPot << " chips." << endl;
	return;
}

void SevenCardStud::bettingTurn(Player & player, unsigned int & chipPot, unsigned int & betRequirement) {
	if (player.playerChips <= player.playerBet)
	{
		cout << player.playerName << " does not have enough chips to bet more." << endl;
		player.playerBet = player.playerChips;
		return;
	}
	if (!player.folded && ((player.playerBet < betRequirement) || betRequirement == 0))
	{
		if (betRequirement == 0)
		{
			cout << player.playerName << "! There are no current bets on the table. " << endl;
			cout << "Would you like to 'check' or 'bet'?" << endl;

			bool correctInput = false;
			string input = "";
			while (!correctInput)
			{
				cin >> input;
				if (input == "check")
				{
					correctInput = true;
				}
				else if (input == "bet")
				{
					correctInput = true;
					bool moreCorrectInput = false;
					while (!moreCorrectInput)
					{
						cout << "How many chips would you like to bet? (1 or 2)" << endl;
						cin >> input;
						if (input == "1")
						{
							moreCorrectInput = true;
							betRequirement = 1;
							player.playerBet = 1;
						}
						else if (input == "2")
						{
							moreCorrectInput = true;
							betRequirement = 2;
							player.playerBet = 2;
						}
						else
						{
							cout << "You can only bet '1' or '2' chips." << endl;
						}
					}
				}
				else
				{
					cout << "You can currently only 'check' or 'bet'." << endl;
				}
			}
		}

		else
		{
			cout << player.playerName << "! The current bet requirement is " << betRequirement << endl;
			cout << "Would you like to 'call', 'raise', or 'fold'?" << endl;
			bool correctInput = false;
			string input = "";
			while (!correctInput)
			{
				cin >> input;
				if (input == "call")
				{
					player.playerBet = betRequirement;
					correctInput = true;
				}
				else if (input == "raise")
				{
					correctInput = true;
					bool moreCorrectInput = false;
					if (player.playerChips >= betRequirement + 2) {
						while (!moreCorrectInput)
						{
							cout << "How many chips would you like to raise? (1 or 2)" << endl;
							cin >> input;
							if (input == "1")
							{
								moreCorrectInput = true;
								betRequirement += 1;
								player.playerBet = betRequirement;
							}
							else if (input == "2")
							{
								moreCorrectInput = true;
								betRequirement += 2;
								player.playerBet = betRequirement;
							}
							else
							{
								cout << "You can only raise '1' or '2' chips." << endl;
							}
						}
					}
					else {
						cout << "You only have enough chips to raise by 1." << endl;
						betRequirement += 1;
						player.playerBet = betRequirement;
					}
				}
				else if (input == "fold")
				{
					player.folded = true;
					correctInput = true;
				}
				else
				{
					cout << "You can currently only 'call', 'raise', or 'fold'" << endl;
				}
			}
		}
	}

	return;
}

unsigned int SevenCardStud::countFolds(vector<shared_ptr<Player>> & playerVector) {
	int count = 0;
	unsigned int i = 0;

	for (i = 0; i < playerVector.size(); ++i) {
		if ((*playerVector[i]).folded) {
			count += 1;
		}
	}
	return count;
}