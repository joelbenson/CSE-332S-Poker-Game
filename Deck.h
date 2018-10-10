// Deck.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the Deck class, and
// all of the corresponding member variables and
// member functions.
//
// Lab 4

#pragma once

#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>

// Forward Declaration
class Hand;

// Deck uses the default constructor since
// all member variables can be safely destructed
// without special instruction.
class Deck {
private:
	friend ostream & operator<< (ostream & out, const Deck & printingDeck);
	friend Hand & operator<< (Hand &, Deck &);
	vector<Card> cardDeck;
public:
	// Default constructor that initializes an empty deck
	Deck();
	// Declare the constructor with a filename to read
	Deck(char*);
	// Deck method to add a card taking it as the only parameter
	int Deck::addCard(Card);
	// Declare the load method
	int loadDeck(char*);
	// Declare the shuffle method
	int shuffleDeck();
	// Declare the size method
	int sizeDeck() const;
	// Declare a print method
	int printDeck() const;
	// This function parses a .txt file and pushes valid
	// cards onto a vector of cards (deck)
	int parseText(Deck &, char*);

	int clearDeck();
};


// Non-member insertion operator
ostream & operator<< (ostream & out, const Deck & printingDeck);
