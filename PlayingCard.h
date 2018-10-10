// PlayingCard.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains all of the declarations for
// playing card functionality.
//
// Lab 4

#pragma once

#include <vector>
#include <string>
using namespace std;

// This is the enum for all of the different card values
enum cardRankEnum {
	two, three, four, five, six, seven, eight,
	nine, ten, jack, queen, king, ace
};

// This is the enum for card suits
enum suitEnum { clubs, diamonds, hearts, spades };

// This is a struct that creates a playing card
// with a suit and value
struct Card {
	bool facedown = false;
	bool operator< (const Card &) const;
	bool operator== (const Card &) const;
	bool pokerRankCardLessThan(const Card &) const;
	cardRankEnum cardRank;
	suitEnum suit;
};



// This function prints out cards from a vector of cards
// in a nicely formatted string
int printCards(const vector<Card> &);

// This function returns true if a group of characters is
// a valid card.
bool validateCard(string);

// This function returns true if a string is "//"
bool checkComment(string);

// This function returns true and changes the string if the
// string contains a comment
bool checkContainsComment(string &);

// This function makes a string out of a card that 
// describes what type of card it is
string makeString(Card);

// This makes a string that is more space-concious
// than the makeString function. For the six of hearts,
// it would print out "*6H*".
string makeSimpleString(Card);

// This function will check if a hand is of size five and if so write
// it to the card vector.  Regardless, it will then empty the hand.
int validateHand(vector<Card> &, vector<Card> &, int);

