// Lab4.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file is the main source file for LabFour,
// which takes in arguments for games and players
// and tries to then create a game with that game
// name and the passed in players. This will continue
// looping until there are either too many or two
// few players.
//
// Lab 4
//
// Lab4.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Utilities.h"
#include "Game.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Main function call passing in arguments from the command line
int main(int argc, char * argv[])
{

	int expectedMinArgs = 4;

	// As long as there are enough arguments begin to execute the program
	if (argc >= expectedMinArgs)
	{
		// Try to start a game with the passed in game name
		try
		{
			Game::start_game(argv[gameName]);
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


		//Add all players to the game
		for (int i = firstPlayer; i < argc; ++i)
		{
			try
			{
				(*currentGame).add_player(argv[i]);
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

		int minPlayers = 2;
		int maxPlayers = 10;

		if (Game::instance()->isSeven)
		{
			maxPlayers = 7;
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

	}

	//If there are too few arguments, print usage message
	else
	{
		return tooFewArgumentsMessage(argv[programTitle]);
	}
	bool quit = false;

	while (!quit)
	{
		string input;
		cout << "Do you want to start a new game? yes or no" << endl;
		cin >> input;
		if (input == "yes")
		{
			bool correctInput = false;
			while (!correctInput)
			{
				string gamename;
				cout << "Which game? FiveCardDraw or SevenCardStud?" << endl;
				cin >> gamename;
				if (gamename == "FiveCardDraw" || gamename == "SevenCardStud")
				{
					rungame(gamename);
					correctInput = true;
				}
				else
				{
					cout << "Wrong input try again type correct gamename" << endl;
				}
			}
		}
		if (input == "no")
		{
			quit = true;
		}
		else
		{
			cout << "Please type either yes or no" << endl;
			//do nothing
		}
	}


	return success;

}