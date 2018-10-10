// Hand.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the Hand class, and
// all of the corresponding member variables and
// member functions (including enums).
// In addition, this file contains the ranking
// function to rank two hands.
//
// Lab 4

#pragma once


#include "PlayingCard.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

// This is the ranking for a five card poker hand.
enum pokerHandEnum {
	no_rank, one_pair, two_pairs, three_of_a_kind,
	straight, flush, full_house, four_of_a_kind, straight_flush
};

// Forward Declaration
class Deck;
class Hand;
struct Player;

// Hand uses the default constructor since
// all member variables can be safely destructed
// without special instruction.
class Hand {
private:
	friend ostream & operator<< (ostream & out, const Hand & printingHand);
	friend Hand & operator<< (Hand &, Deck &);
	friend bool poker_rank(const Hand &, const Hand &);
	//
	friend string automateLine(Player &);
	//
	vector<Card> cardVector;
public:
	pokerHandEnum bestHand;
	Hand();
	Hand(const Hand &);
	int operator= (const Hand &);
	Card & operator[] (size_t);
	size_t sizeHand() const;
	bool operator== (const Hand &) const;
	bool operator< (const Hand &) const;
	string cardAsString() const;
	string othercardAsString() const;
	vector<Card> & getCardVector();
	int setCardVector(vector<Card>);
	int setEnum(pokerHandEnum enumToSet);
	int removeCard(size_t);
	int clearHand();
};

// Non-member Hand insertion operator to ostream
ostream & operator<< (ostream & out, const Hand & printingHand);

// Non-member insertion operator from Deck to Hand
Hand & operator<< (Hand &, Deck &);



//////////////////////////////////////////////////

///////////////POKER HAND MANIPULATIONS///////////

//////////////////////////////////////////////////




// This function will assign no rank to the enum of a poker hand.
int noRank(Hand &);

// This function will check if a hand has one pair and assign the enum if so.
int onePairCheck(Hand &);

// This function will check if a hand has two pairs and assign the enum if so.
int twoPairCheck(Hand &);

// This function will check if a hand has three of a kind and assign the enum if so.
int threeOfAKindCheck(Hand &);

// This function will check if a hand is a straight and assign the enum if so.
// This function will also check if the hand has the straight two three four five ace.
int straightCheck(Hand &);

// This function will check if a hand is has a flush and assign the enum if so.
int flushCheck(Hand &);

// This function will check if a hand has a full house and assign the enum if so.
int fullHouseCheck(Hand &);

// This function will check if a hand has four of a kind and assign the enum if so.
int fourOfAKindCheck(Hand &);

// This function will check if a hand has a straight flush and assign the enum if so.
int straightFlushCheck(Hand &);

// This function calls all of the hand rank functions in the correct order.
int rankHand(Hand &);

// This function takes in a hand and sorts it.
int sortCardVector(vector<Card> &);

// This is the function that will print out a poker hand, printing out both the highest rank
// and the sorted cards within that hand.
int printPokerHand(Hand &);

int constPrintPokerHand(const Hand &);


// This function will look at two poker hands and return true if and only if the 
// first hand ranks higher than the second hand.
bool poker_rank(const Hand &, const Hand &);

bool poker_rank_players(const shared_ptr<Player>, const shared_ptr<Player>);
