// Game.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file declares a game class with pure
// virtual functions and a static shared pointer
// to a game. This file contains all of the
// general member functionss that would be 
// inherited by any card game that inhereits game.
//
//
// Lab 4

#pragma once
#include "Deck.h"
#include "Player.h"
#include <string>
#include <memory>

using namespace std;

class Game {
private:

protected:
	static shared_ptr<Game> gamePointer;
	Deck gameDeck;
	vector<shared_ptr<Player>> playerVector;
	///
	unsigned int chipPot;
	unsigned int betRequirement;
public:
	Game();
	virtual ~Game();
	static shared_ptr<Game> instance();
	static void Game::start_game(const string &);
	static void Game::stop_game();
	int add_player(const string &);
	int remove_player(string);
	int remove_all_player();
	shared_ptr<Player> find_player(string);
	int getNumPlayers();
	virtual int before_turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	///
	bool Game::needChips(shared_ptr<Player> & player);
	int checkChipCounts();
	bool isSeven;
};

int rungame(string);