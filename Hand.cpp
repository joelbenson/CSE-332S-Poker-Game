// Hand.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains the Hand class, and definitions
// for all the member functions of the Hand class.
// In addition, this file contains all functionality
// for poker hands, including finding their rank
// and ranking them against each other.
//
// Lab 4

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Utilities.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <random>
#include <set>
#include <memory>

using namespace std;


// This is the default copy constructor for Hand
Hand::Hand()
{
	vector<Card> cardVector;
	bestHand = pokerHandEnum::no_rank;
}

// This is an alternate copy constructor for Hand
// which creates a new hand that is exactly the same
// as a passed hand.
Hand::Hand(const Hand & hand)
{
	this->cardVector = hand.cardVector;
	this->bestHand = hand.bestHand;
}

// This function checks if two hands are equal and
// if they are not it assigns the value of one to 
// the other.
int Hand::operator= (const Hand & hand)
{
	if (((*this) == hand) && (this->bestHand == hand.bestHand))
	{
		return success;
	}

	else
	{
		this->cardVector.clear();
		this->cardVector = hand.cardVector;
		this->bestHand = hand.bestHand;
		return success;
	}
}

// This function defines the Hand indexing operator
Card & Hand::operator[] (size_t index)
{
	if ((index < (sizeHand())) && (index >= 0))
	{
		return cardVector[index];
	}
	else
	{
		throw indexOutOfRange;
	}
}

// This function will remove a card from the cardVector of the hand
int Hand::removeCard(size_t index)
{
	if ((index >= 0) && (index < sizeHand()))
	{
		cardVector.erase(cardVector.begin() + index);

		return success;
	}

	else
	{
		throw indexOutOfRange;
	}
}

// This function will give the size of a hand in the
// data type used for sizes of items.
size_t Hand::sizeHand() const
{
	return this->cardVector.size();
}

// This function tests for equality between two hands
bool Hand::operator== (const Hand & hand) const
{
	vector<Card> firstCardHand = this->cardVector;
	vector<Card> secondCardHand = hand.cardVector;
	set<Card> cardSet;

	vector<Card>::iterator firstIT = firstCardHand.begin();
	vector<Card>::iterator lastIT = firstCardHand.end();
	vector<Card>::iterator i;
	bool insertSuccess = true;
	bool identical = true;

	for (i = firstIT; i != lastIT; ++i)
	{
		cardSet.insert(*i).second;
	}

	firstIT = secondCardHand.begin();
	lastIT = secondCardHand.end();

	for (i = firstIT; i != lastIT; ++i)
	{
		insertSuccess = cardSet.insert(*i).second;

		if (insertSuccess == true)
		{
			identical = false;
		}
	}


	if (this->sizeHand() != hand.sizeHand())
	{
		identical = false;
	}

	return identical;
}

// This function defines the Hand less than operator.
bool Hand::operator< (const Hand & hand) const
{
	bool lessThan = true;
	bool wasFalse = true;

	vector<Card> firstHand = this->cardVector;
	vector<Card> secondHand = hand.cardVector;
	vector<Card>::iterator firstStart = firstHand.begin();
	vector<Card>::iterator firstEnd = firstHand.end();
	vector<Card>::iterator secondStart = secondHand.begin();
	vector<Card>::iterator secondEnd = secondHand.end();
	vector<Card>::iterator i;
	vector<Card>::iterator j;

	bool firstSmaller = (firstHand.size() <= secondHand.size());
	int smallestSize = min(firstHand.size(), secondHand.size());

	if (firstHand.size() == 0 && secondHand.size() == 0)
	{
		throw handSizeZero;
	}

	if (firstSmaller)
	{
		j = secondStart;
		for (i = firstStart; i != firstEnd; ++i)
		{
			if ((*i) < (*j))
			{
				lessThan = true;
				return lessThan;
			}

			else if ((*i) == (*j))
			{
				// Do Nothing
			}

			else
			{
				lessThan = false;
				return lessThan;
			}
			++j;
		}

		lessThan = true;
		return lessThan;
	}

	else
	{
		i = firstStart;
		for (j = secondStart; j != secondEnd; ++j)
		{
			if ((*j) < (*i))
			{
				lessThan = false;
				return lessThan;
			}

			else if ((*i) == (*j))
			{
				// Do Nothing
			}

			else
			{
				lessThan = true;
				return lessThan;
			}
			++i;
		}

		lessThan = false;
		return lessThan;
	}


}

// This function takes in a hand, and creates a string
// separated by spaces that contains all of the cards in
// the hand.
string Hand::cardAsString() const
{
	string textString;

	vector<Card> firstCardHand = this->cardVector;
	vector<Card>::iterator firstIT = firstCardHand.begin();
	vector<Card>::iterator lastIT = firstCardHand.end();
	vector<Card>::iterator i;

	for (i = firstIT; i != lastIT; ++i)
	{
		textString = textString + makeSimpleString(*i) + " ";
	}

	return textString;
}

// This function takes in a hand, and creates a string
// separated by spaces that contains all of the cards in
// the hand.
string Hand::othercardAsString() const
{
	string textString;

	vector<Card> firstCardHand = this->cardVector;
	vector<Card>::iterator firstIT = firstCardHand.begin();
	vector<Card>::iterator lastIT = firstCardHand.end();
	vector<Card>::iterator i;

	for (i = firstIT; i != lastIT; ++i)
	{
		if ((*i).facedown)
		{
			textString = textString + "***" + " ";
		}
		else
		{
			textString = textString + makeSimpleString(*i) + " ";
		}
	}

	return textString;
}

// This function returns a reference to a Hand's
// cardVector
vector<Card> & Hand::getCardVector()
{
	return this->cardVector;
}

// This is a function to set the enum of a Hand.
int Hand::setEnum(pokerHandEnum enumToSet)
{
	bestHand = enumToSet;
	return success;
}

// This is a function to set the cardVector of a Hand.
int Hand::setCardVector(vector<Card> vectorToSet)
{
	cardVector = vectorToSet;
	return success;
}

int Hand::clearHand()
{
	cardVector.clear();
	return success;
}

// This is an insertion operator that is used to insert a
// Hand onto an output stream as a string.
ostream & operator<< (ostream & out, const Hand & printingHand)
{
	string printableString;

	printableString = printingHand.cardAsString();

	out << printableString << endl;

	return out;
}


// This is an insertion operator that takes the back card off of the
// deck and inserts it onto the card vector of the hand.
Hand & operator<< (Hand & hand, Deck & deck)
{
	Card transferCard = deck.cardDeck.back();
	deck.cardDeck.pop_back();
	if (Game::instance()->isSeven)
	{
		if (hand.cardVector.size() == 0 || hand.cardVector.size() == 1 || hand.cardVector.size() == 6)
		{
			transferCard.facedown = true;
		}
	}


	hand.cardVector.push_back(transferCard);

	if (!(Game::instance()->isSeven))
	{
		sortCardVector(hand.cardVector);
	}

	return hand;
}


//////////////////////////////////////////////////

///////////////POKER HAND MANIPULATIONS///////////

//////////////////////////////////////////////////



const int numCards = 13;
const int numSuit = 4;


// This function takes in and sorts a hand.
int sortCardVector(vector<Card> & hand)
{
	sort(hand.begin(), hand.end());
	return success;
}

// This function calls all of the hand rank functions in the correct order.
int rankHand(Hand & hand)
{
	noRank(hand);
	onePairCheck(hand);
	twoPairCheck(hand);
	threeOfAKindCheck(hand);
	straightCheck(hand);
	flushCheck(hand);
	fullHouseCheck(hand);
	fourOfAKindCheck(hand);
	straightFlushCheck(hand);
	return success;
}

// This function will assign no rank to the enum of a poker hand.
int noRank(Hand & hand)
{
	hand.setEnum(no_rank);

	return success;
}

// This function will check if a hand has one pair and assign the enum if so.
int onePairCheck(Hand & hand)
{
	bool onePair = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 2)
		{
			onePair = true;
		}
	}

	if (onePair)
	{
		hand.setEnum(one_pair);
	}

	return success;
}

// This function will check if a hand has two pairs and assign the enum if so.
int twoPairCheck(Hand & hand)
{
	bool onePair = false;
	bool twoPair = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 2 && !onePair)
		{
			onePair = true;
		}

		else if (cardCount[j] >= 2 && onePair)
		{
			twoPair = true;
		}
	}

	if (onePair && twoPair)
	{
		hand.setEnum(two_pairs);
	}

	return success;
}

// This function will check if a hand has three of a kind and assign the enum if so.
int threeOfAKindCheck(Hand & hand)
{
	bool threeKind = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 3)
		{
			threeKind = true;
		}
	}

	if (threeKind)
	{
		hand.setEnum(three_of_a_kind);
	}

	return success;
}

// This function will check if a hand is a straight and assign the enum if so.
// This function will also check if the hand has the straight two three four five ace.
int straightCheck(Hand & hand)
{
	bool straightState = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}


	int straightCount = 0;

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 1)
		{
			straightCount = straightCount + 1;

			if (straightCount == 5)
			{
				straightState = true;
			}

		}

		else
		{
			straightCount = 0;
		}
	}

	if (cardCount[0] == 1 &&
		cardCount[1] == 1 &&
		cardCount[2] == 1 &&
		cardCount[3] == 1 &&
		cardCount[12] == 1)
	{
		straightState = true;
	}

	if (straightState)
	{
		hand.setEnum(straight);
	}

	return success;
}

// This function will check if a hand is has a flush and assign the enum if so.
int flushCheck(Hand & hand)
{
	bool flushState = false;
	int suitCount[numSuit] = { 0, 0, 0, 0 };

	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int suitType = hand.getCardVector()[i].suit;
		suitCount[suitType] = suitCount[suitType] + 1;
	}

	for (int j = 0; j < numSuit; ++j)
	{
		if (suitCount[j] == hand.getCardVector().size())
		{
			flushState = true;
		}
	}

	if (flushState)
	{
		hand.setEnum(pokerHandEnum::flush);
	}

	return success;
}

// This function will check if a hand has a full house and assign the enum if so.
int fullHouseCheck(Hand & hand)
{
	bool threeKind = false;
	bool twoKind = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 3)
		{
			threeKind = true;
		}

		else if (cardCount[j] == 2)
		{
			twoKind = true;
		}
	}

	if (threeKind && twoKind)
	{
		hand.setEnum(full_house);
	}

	return success;
}

// This function will check if a hand has four of a kind and assign the enum if so.
int fourOfAKindCheck(Hand & hand)
{
	bool fourKind = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= numSuit)
		{
			fourKind = true;
		}
	}

	if (fourKind)
	{
		hand.setEnum(four_of_a_kind);
	}

	return success;
}

// This function will check if a hand has a straight flush and assign the enum if so.
int straightFlushCheck(Hand & hand)
{
	bool straightState = false;
	int cardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int cardType = hand.getCardVector()[i].cardRank;
		cardCount[cardType] = cardCount[cardType] + 1;
	}


	int straightCount = 0;

	for (int j = 0; j < numCards; ++j)
	{
		if (cardCount[j] >= 1)
		{
			straightCount = straightCount + 1;

			if (straightCount == 5)
			{
				straightState = true;
			}

		}

		else
		{
			straightCount = 0;
		}
	}

	if (cardCount[0] == 1 &&
		cardCount[1] == 1 &&
		cardCount[2] == 1 &&
		cardCount[3] == 1 &&
		cardCount[12] == 1)
	{
		straightState = true;
	}



	bool flushState = false;
	int suitCount[numSuit] = { 0, 0, 0, 0 };

	for (unsigned int i = 0; i < hand.getCardVector().size(); ++i)
	{
		int suitType = hand.getCardVector()[i].suit;
		suitCount[suitType] = suitCount[suitType] + 1;
	}

	for (int j = 0; j < numSuit; ++j)
	{
		if (suitCount[j] == hand.getCardVector().size())
		{
			flushState = true;
		}
	}


	if (straightState && flushState)
	{
		hand.setEnum(straight_flush);
	}


	return success;
}

// This is the function that will print out a poker hand, printing out both the highest rank
// and the sorted cards within that hand.
int printPokerHand(Hand & hand)
{
	string finalString = "The best rank of this hand is ";

	rankHand(hand);

	switch (hand.bestHand)
	{
	case no_rank:
		finalString += "no rank.";
		break;
	case one_pair:
		finalString += "one pair.";
		break;
	case two_pairs:
		finalString += "two pairs.";
		break;
	case three_of_a_kind:
		finalString += "three of a kind.";
		break;
	case straight:
		finalString += "a straight.";
		break;
	case pokerHandEnum::flush:
		finalString += "a flush.";
		break;
	case full_house:
		finalString += "a full house.";
		break;
	case four_of_a_kind:
		finalString += "four of a kind.";
		break;
	case straight_flush:
		finalString += "a straight flush.";
		break;
	}

	cout << finalString << endl;

	return success;
}

int constPrintPokerHand(const Hand & hand)
{
	string finalString = "The best rank of their hand was ";

	switch (hand.bestHand)
	{
	case no_rank:
		finalString += "no rank.";
		break;
	case one_pair:
		finalString += "one pair.";
		break;
	case two_pairs:
		finalString += "two pairs.";
		break;
	case three_of_a_kind:
		finalString += "three of a kind.";
		break;
	case straight:
		finalString += "a straight.";
		break;
	case pokerHandEnum::flush:
		finalString += "a flush.";
		break;
	case full_house:
		finalString += "a full house.";
		break;
	case four_of_a_kind:
		finalString += "four of a kind.";
		break;
	case straight_flush:
		finalString += "a straight flush.";
		break;
	}

	cout << finalString << endl;

	return success;
}

// This function will look at two poker hands and return true if and only if the 
// first hand ranks higher than the second hand.
// THROWS EXCEPTION!
bool poker_rank(const Hand & firstHand, const Hand & secondHand)
{
	int handSize = 5;
	int handSize2 = 7;


	// Important to start as false for the tie cases
	bool ranksHigher = false;
	int firstHandSize = firstHand.sizeHand();
	int secondHandSize = secondHand.sizeHand();
	int firstCardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int secondCardCount[numCards] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	////// IF THE 
	if (firstHandSize != secondHandSize) {
		return (firstHandSize > secondHandSize);
	}
	//////
	// If the hand size is not five in this case
	if ((firstHandSize != handSize && firstHandSize != handSize2) || (secondHandSize != handSize && secondHandSize != handSize2))
	{
		return (firstHandSize > secondHandSize);
	}

	else
	{
		// Check if the first hand has a worse rank outright than
		// the second hand
		if (firstHand.bestHand < secondHand.bestHand)
		{
			ranksHigher = false;
			return ranksHigher;
		}

		// Check if the first hand has a better rank outright than
		// the second hand
		else if (firstHand.bestHand > secondHand.bestHand)
		{
			ranksHigher = true;
			return ranksHigher;
		}

		// If the rank of the hands is the same
		else
		{

			// One Pair Variables
			int firstCardPair = 0;
			int secondCardPair = 0;

			// Two Pair Variables
			int firstCardPairHigh = 0;
			int firstCardPairLow = 0;
			int secondCardPairHigh = 0;
			int secondCardPairLow = 0;

			// Three of a Kind Variables
			int firstCardThreeKind = 0;
			int secondCardThreeKind = 0;

			// Full House Variables
			int firstCardThreeFH = 0;
			int firstCardTwoFH = 0;
			int secondCardThreeFH = 0;
			int secondCardTwoFH = 0;

			//Four of a Kind Variables
			int firstCardFourKind = 0;
			int secondCardFourKind = 0;

			switch (firstHand.bestHand)
			{

				// In the case that both hands have no best rank
			case no_rank:

				ranksHigher = false;

				// Clear card counters
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Assign card counts for both the first and second hands
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				// Starting at the highest rank check who has the high card
				for (int i = (numCards - 1); i >= 0; --i)
				{
					if (firstCardCount[i] > secondCardCount[i])
					{
						ranksHigher = true;
						break;
					}

					else if (secondCardCount[i] > firstCardCount[i])
					{
						ranksHigher = false;
						break;
					}
				}

				break;

				// In the case that both hands have best rank one pair
			case one_pair:

				ranksHigher = false;

				// Clear card counters
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Find out where the one pair is for both the first
				// and second hand and save that location
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
					if (firstCardCount[cardType] == 2)
					{
						firstCardPair = cardType;
					}
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
					if (secondCardCount[cardType] == 2)
					{
						secondCardPair = cardType;
					}
				}

				// If the first card pair ranks higher than the second card pair
				if (firstCardPair > secondCardPair)
				{
					ranksHigher = true;
				}

				// If the first card pair ranks lower than the second card pair
				else if (firstCardPair < secondCardPair)
				{
					ranksHigher = false;
				}

				// If the card pairs both rank equally
				else
				{
					for (int i = (numCards - 1); i >= 0; --i)
					{
						if (firstCardCount[i] > secondCardCount[i])
						{
							ranksHigher = true;
							break;
						}

						else if (secondCardCount[i] > firstCardCount[i])
						{
							ranksHigher = false;
							break;
						}
					}
				}

				break;

				// In the case that both hands have best rank have two pairs
			case two_pairs:

				ranksHigher = false;

				// Clear card counters
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of each type of card in the hand
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				// Find out where the high pair and low pair
				// is for both the first and second hand
				for (int i = 0; i < numCards; ++i)
				{

					if (firstCardCount[i] == 2 && i > firstCardPairHigh)
					{
						firstCardPairHigh = i;
					}
					else if (firstCardCount[i] == 2 && i > firstCardPairLow)
					{
						firstCardPairLow = i;
					}

					if (secondCardCount[i] == 2 && i > secondCardPairHigh)
					{
						secondCardPairHigh = i;
					}
					else if (secondCardCount[i] == 2 && i > secondCardPairLow)
					{
						secondCardPairLow = i;
					}

				}

				// If the high pair for the first hand ranks higher
				// than the high pair for the second hand
				if (firstCardPairHigh > secondCardPairHigh)
				{
					ranksHigher = true;
				}

				// If the high pair for the first hand ranks lower
				// than the high pair for the second hand
				else if (firstCardPairHigh < secondCardPairHigh)
				{
					ranksHigher = false;
				}

				// If the high pair for the first hand has the 
				// same rank as the high pair for the second hand
				else
				{
					if (firstCardPairLow > secondCardPairLow)
					{
						ranksHigher = true;
					}

					else if (firstCardPairLow < secondCardPairLow)
					{
						ranksHigher = false;
					}

					else
					{
						ranksHigher = false;
					}

				}

				break;

				// If both of the cards have best rank three of a kind
			case three_of_a_kind:

				ranksHigher = false;

				// Clear card count
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of cards per rank for both hands
				// and also find the rank of the three of a kind
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
					if (firstCardCount[cardType] == 3)
					{
						firstCardThreeKind = cardType;
					}
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
					if (secondCardCount[cardType] == 3)
					{
						secondCardThreeKind = cardType;
					}
				}

				// If the three of a kind rank is higher for the
				// first hand than the second hand
				if (firstCardThreeKind > secondCardThreeKind)
				{
					ranksHigher = true;
				}

				// If the three of a kind rank is lower for the first
				// hand than the second hand
				else if (firstCardThreeKind < secondCardThreeKind)
				{
					ranksHigher = false;
				}

				// If the three of a kind rank is equal for both hands
				else
				{
					for (int i = (numCards - 1); i >= 0; --i)
					{
						if (firstCardCount[i] > secondCardCount[i])
						{
							ranksHigher = true;
							break;
						}

						else if (secondCardCount[i] > firstCardCount[i])
						{
							ranksHigher = false;
							break;
						}
					}
				}

				break;

				// If the best rank of each hand is a straight
			case straight:

				ranksHigher = false;

				// Clear card count
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of cards per rank for each hand
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				// Find the lowest card of the straight for each hand
				// and the hand with the highest low card has the highest rank
				for (int i = 0; i < numCards; ++i)
				{
					if (firstCardCount[i] > secondCardCount[i])
					{
						ranksHigher = false;
						break;
					}

					else if (secondCardCount[i] > firstCardCount[i])
					{
						ranksHigher = true;
						break;
					}
				}

				break;

				// In the case where both hands have best rank flush
			case pokerHandEnum::flush:

				ranksHigher = false;

				// Clear card counts
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of each rank of cards for each hand
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				// Start at ace and find the highest card for each hand
				for (int i = (numCards - 1); i >= 0; --i)
				{
					if (firstCardCount[i] > secondCardCount[i])
					{
						ranksHigher = true;
						break;
					}

					else if (secondCardCount[i] > firstCardCount[i])
					{
						ranksHigher = false;
						break;
					}

				}

				break;

				// In the case that both hands have best rank full house
			case full_house:

				ranksHigher = false;

				// Clear card count
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of each rank of card for both hands
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				// Find the rank of the three of a kind and the pair
				// for each hand
				for (int i = 0; i < numCards; ++i)
				{
					if (firstCardCount[i] == 3)
					{
						firstCardThreeFH = i;
					}
					else if (firstCardCount[i] == 2)
					{
						firstCardTwoFH = i;
					}

					if (secondCardCount[i] == 3)
					{
						secondCardThreeFH = i;
					}
					else if (secondCardCount[i] == 2)
					{
						secondCardTwoFH = i;
					}

				}

				// First attempt to rank by best three of a kind
				// If that is tied, then rank by pair
				if (firstCardThreeFH > secondCardThreeFH)
				{
					ranksHigher = true;
				}

				else if (firstCardThreeFH < secondCardThreeFH)
				{
					ranksHigher = false;
				}

				else
				{
					if (firstCardTwoFH > secondCardTwoFH)
					{
						ranksHigher = true;
					}

					else if (firstCardTwoFH < secondCardTwoFH)
					{
						ranksHigher = false;
					}

					else
					{
						ranksHigher = false;
					}

				}

				break;

				// In the case that both hands have best rank four of a kind
			case four_of_a_kind:

				ranksHigher = false;

				// Clear card count
				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				// Calculate the number of cards for each rank in each hand
				// and register the card rank of the four of a kind
				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
					if (firstCardCount[cardType] == 4)
					{
						firstCardFourKind = cardType;
					}
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
					if (secondCardCount[cardType] == 4)
					{
						secondCardFourKind = cardType;
					}
				}

				// Attempt to rank by four of a kind, if not possible
				// rank by highest card
				if (firstCardFourKind > secondCardFourKind)
				{
					ranksHigher = true;
				}

				else if (firstCardFourKind < secondCardFourKind)
				{
					ranksHigher = false;
				}

				else
				{
					for (int i = (numCards - 1); i >= 0; --i)
					{
						if ((firstCardCount[i] > secondCardCount[i]))
						{
							ranksHigher = true;
							break;
						}

						else if (secondCardCount[i] > firstCardCount[i])
						{
							ranksHigher = false;
							break;
						}
					}
				}

				break;

				// In the case that both hands have best rank straight flush
			case straight_flush:

				ranksHigher = false;

				for (int i = 0; i < numCards; ++i)
				{
					firstCardCount[i] = 0;
					secondCardCount[i] = 0;
				}

				for (int i = 0; i < firstHandSize; ++i)
				{
					int cardType = firstHand.cardVector[i].cardRank;
					firstCardCount[cardType] = firstCardCount[cardType] + 1;
				}

				for (int i = 0; i < secondHandSize; ++i)
				{
					int cardType = secondHand.cardVector[i].cardRank;
					secondCardCount[cardType] = secondCardCount[cardType] + 1;
				}

				for (int i = 0; i < numCards; ++i)
				{
					if (firstCardCount[i] > secondCardCount[i])
					{
						ranksHigher = false;
						break;
					}

					else if (secondCardCount[i] > firstCardCount[i])
					{
						ranksHigher = true;
						break;
					}
				}

				break;
			}

			return ranksHigher;
		}
	}

}

bool poker_rank_players(const shared_ptr<Player> firstPlayer, const shared_ptr<Player> secondPlayer)
{
	bool ranksHigher = false;

	if (firstPlayer == nullptr)
	{
		ranksHigher = false;
	}

	else if (secondPlayer == nullptr)
	{
		ranksHigher = true;
	}

	else
	{
		//////
		if ((*firstPlayer).folded) {
			return false;
		}
		if ((*secondPlayer).folded) {
			return true;
		}
		///////
		ranksHigher = poker_rank((*firstPlayer).playerHand, (*secondPlayer).playerHand);
	}

	return ranksHigher;
}