// Game.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file defines a game class with pure
// virtual functions and a static shared pointer
// to a game. This file contains all of the
// general member functionss that would be 
// inherited by any card game that inhereits game.
//
// Lab 4

#include "stdafx.h"
#include "Game.h"
#include "Utilities.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

shared_ptr<Game> Game::gamePointer(nullptr);

Game::Game()
{
	static shared_ptr<Game> gamePointer(nullptr);
	Deck gameDeck;
	vector<shared_ptr<Player>> playerVector;
	///
	chipPot = 0;
	betRequirement = 0;
}

Game::~Game()
{

}

shared_ptr<Game> Game::instance()
{
	if (gamePointer)
	{
		return gamePointer;
	}
	else
	{
		throw instance_not_available;
	}
}

void Game::start_game(const string & gametype)
{

	if (!gamePointer)
	{
		if (gametype == "FiveCardDraw")
		{
			gamePointer = make_shared<FiveCardDraw>(FiveCardDraw());
			gamePointer->isSeven = false;
		}
		else if (gametype == "SevenCardStud")
		{
			gamePointer = make_shared<SevenCardStud>(SevenCardStud());
			gamePointer->isSeven = true;
		}
		else
		{
			throw unknown_game;
		}
	}


	else
	{
		throw game_already_started;
	}
}

void Game::stop_game()
{
	(*gamePointer).remove_all_player();
	if (gamePointer)
	{
		gamePointer = nullptr;
	}
	else
	{
		throw no_game_in_progress;
	}
}

bool Game::needChips(shared_ptr<Player> & player)
{
	bool playerZeroChips = false;
	if ((*player).playerChips == 0)
	{
		playerZeroChips = true;
		string input;
		bool correctInput = false;
		while (!correctInput)
		{
			cout << (*player).playerName << "! you currently have no chips, do you want to recharge your chips to stay in the game? (type: yes or no)" << endl;
			cin >> input;
			if (input == "yes")
			{
				(*player).playerChips = 20;
				playerZeroChips = false;
				correctInput = true;
				cout << (*player).playerName << " has reset to 20 chips." << endl;
				string playerName = (*player).playerName;
				string fileName;
				shared_ptr<Player> playerPointer;
				playerPointer = find_player(playerName);
				if (playerPointer != nullptr)
				{
					fileName = playerName + ".txt";
					ofstream ofs;
					ofs.open(fileName);
					ofs << playerName << " " << (*playerPointer).playerWins << " " << (*playerPointer).playerLosses << " " << (*playerPointer).playerChips;
					ofs.close();
				}
			}
			else if (input == "no")
			{
				remove_player((*player).playerName);
				correctInput = true;
			}
			else
			{
				cout << "Incorrect input." << endl;
			}
		}
		return playerZeroChips;
	}
	else
	{
		return playerZeroChips;
	}
}

int Game::add_player(const string & newPlayerInput)
{
	int numberPlayers = playerVector.size();
	bool usernameExists = false;

	////
	bool playerAutomated = false;
	string newPlayer = newPlayerInput;

	if (newPlayer.back() == '*') {
		playerAutomated = true;
		newPlayer.pop_back();
	}

	////

	for (int i = 0; i < numberPlayers; ++i)
	{
		string name = playerVector[i]->playerName;
		if (name == newPlayer)
		{
			usernameExists = true;
		}
	}

	if (usernameExists)
	{
		throw already_playing;
	}

	else
	{
		char * newPlayerName = &(newPlayer[0]);
		////////
		string newAutomatedPlayer = newPlayer + "*";
		if (playerAutomated) {
			newPlayerName = &(newAutomatedPlayer[0]);
		}
		////////
		shared_ptr<Player> playerPointer = make_shared<Player>(Player(newPlayerName));

		if (!needChips(playerPointer))
		{
			playerVector.push_back(playerPointer);
		}
		else
		{
			cout << (*playerPointer).playerName << " has decided not to join the game." << endl;
		}
	}
	return success;
}

int Game::remove_all_player()
{
	vector<shared_ptr<Player>>::iterator i = playerVector.begin();

	while (!playerVector.empty())
	{
		remove_player((*(*i)).playerName);
		i = playerVector.begin();
	}
	return success;
}


int Game::remove_player(string player)
{
	vector<shared_ptr<Player>>::iterator startPointerToPlayer;
	vector<shared_ptr<Player>>::iterator endPointerToPlayer;
	vector<shared_ptr<Player>>::iterator l;
	string playerName = player;
	string fileName;
	shared_ptr<Player> playerPointer;
	playerPointer = find_player(playerName);
	if (playerPointer != nullptr)
	{
		fileName = playerName + ".txt";
		ofstream ofs;
		ofs.open(fileName);
		ofs << playerName << " " << (*playerPointer).playerWins << " " << (*playerPointer).playerLosses << " " << (*playerPointer).playerChips;
		ofs.close();

		int playerLocation = 0;
		int counter = 0;
		startPointerToPlayer = playerVector.begin();
		endPointerToPlayer = playerVector.end();

		for (l = startPointerToPlayer; l != endPointerToPlayer; ++l)
		{
			if (playerPointer == (*l))
			{
				playerLocation = counter;
			}

			counter = counter + 1;
		}

		playerVector.erase(startPointerToPlayer + playerLocation);

	}
	return success;
}

shared_ptr<Player> Game::find_player(string playerToFind)
{
	vector<shared_ptr<Player>>::iterator beginIter = playerVector.begin();
	vector<shared_ptr<Player>>::iterator endIter = playerVector.end();
	vector<shared_ptr<Player>>::iterator i;

	for (i = beginIter; i != endIter; ++i)
	{
		if (playerToFind == (*(*i)).playerName)
		{
			return (*i);
		}
	}

	shared_ptr<Player> emptyPointer(nullptr);
	return emptyPointer;
}

int Game::getNumPlayers()
{
	return playerVector.size();
}

int Game::checkChipCounts() {
	unsigned int i = 0;

	for (i = 0; i < playerVector.size(); ++i)
	{
		if (Game::needChips(playerVector[i]))
		{
			//cout << (*playerVector[i]).playerName << " has left the game with insufficient chips." << endl;
		}
		else
		{

		}
	}
	return success;
}

int rungame(string gamename)
{
	string input;
	int minPlayers = 2;
	int maxPlayers = 10;
	try
	{
		Game::start_game(gamename);
	}

	catch (returnMessages x)
	{
		if (x == unknown_game)
		{
			cout << "You have tried to run a game not named 'FiveCardDraw' or 'SevenCardStud'!" << endl;
			cout << "Make sure that the first argument is `FiveCardDraw' or 'SevenCardStud'" << endl;
			return unknown_game;
		}

		else if (x == game_already_started)
		{
			// Do not need try catch here because we know there is a
			// game that is already in progress.
			Game::stop_game();
		}

		else
		{
			return x;
		}
	}

	catch (...)
	{
		return unknownException;
	}
	//Start game and create a shared pointer variable for the game
	shared_ptr<Game> currentGame;

	try
	{
		// Find the current game in progress
		currentGame = Game::instance();
	}

	catch (returnMessages y)
	{
		cout << "There is no game in progress" << endl;
		return y;
	}

	// If something unknown happnes make sure to try and stop the game in progress
	catch (...)
	{
		try
		{
			(*currentGame).stop_game();
			return unknownException;
		}

		catch (returnMessages z)
		{
			return z;
		}

		catch (...)
		{
			return unknownException;
		}
	}

	cout << "Type in names of the players to play with with space between names." << endl;
	getline(cin, input);
	if (input.empty())
	{
		getline(cin, input);
	}
	istringstream inputStream(input);
	string word;
	//Add all players to the game
	while (inputStream >> word)
	{
		try
		{
			(*currentGame).add_player(word);
		}

		// Explain that a player was added to the game once
		catch (returnMessages)
		{
			cout << endl << "You tried to add the same player twice at the beginning of the game!" << endl;
			cout << "This player was only added once!" << endl;
		}

		catch (...)
		{
			return unknownException;
		}
	}



	//While at least 2 players in the game, continually call game methods
	while (((*currentGame).getNumPlayers() >= minPlayers) && ((*currentGame).getNumPlayers() <= maxPlayers))
	{

		try
		{
			(*currentGame).before_round();

			(*currentGame).round();

			(*currentGame).after_round();

			(*currentGame).checkChipCounts();
		}

		catch (returnMessages error)
		{
			try
			{
				(*currentGame).stop_game();
				return error;
			}

			catch (returnMessages stopError)
			{
				return stopError;
			}

			catch (...)
			{
				return unknownException;
			}
		}

		catch (...)
		{
			try
			{
				(*currentGame).stop_game();
				return unknownException;
			}

			catch (returnMessages f)
			{
				return f;
			}

			catch (...)
			{
				return unknownException;
			}
		}
	}

	// If there are not enough players to continue playing
	if ((*currentGame).getNumPlayers() < minPlayers)
	{
		cout << "You have too few friends, make some more and play again!" << endl;
	}

	// If there are too many players to deal with only one deck
	else
	{
		cout << "You have too many friends, be more selective!" << endl;
	}

	//When there are too few players or too many players, end the game
	(*currentGame).stop_game();
	return success;
}