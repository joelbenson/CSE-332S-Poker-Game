// CardManipulation.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains all of the definitions for
// playing card functionality, including descriminating
// between different text strings and comments when 
// parsing through a text file.
//
// Lab 4

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


// This function returns true if a group of characters is
// a valid card.
bool validateCard(string passedWord)
{
	string s = passedWord;
	int size = s.size();
	int last = size - 1;

	int twoCharString = 2;
	int threeCharString = 3;

	// If the word is either two or three characters and thus
	// could be a valid card.
	if (size == twoCharString || size == threeCharString)
	{
		// If the first character, or in the case of ten first
		// two characters have a valid number
		if (
			((s[0] == '2' || s[0] == '3' || s[0] == '4' ||
				s[0] == '5' || s[0] == '6' || s[0] == '7' ||
				s[0] == '8' || s[0] == '9' || s[0] == 'J' ||
				s[0] == 'j' || s[0] == 'Q' || s[0] == 'q' ||
				s[0] == 'K' || s[0] == 'k' || s[0] == 'A' ||
				s[0] == 'a') && (size == twoCharString))
			||
			(s[0] == '1' && s[1] == '0' && (size == threeCharString))
			)
		{

			// Check if the last character is a valid suit
			// and return true if so
			if (s[last] == 'C' || s[last] == 'c' ||
				s[last] == 'D' || s[last] == 'd' ||
				s[last] == 'H' || s[last] == 'h' ||
				s[last] == 'S' || s[last] == 's')
			{
				return true;
			}

			// If the last character is not a valid suit,
			// it cannot be a valid card.
			else
			{
				return false;
			}
		}

		// If the first or first two characters are not valid, it
		// cannot be a valid card.
		else
		{
			return false;
		}
	}

	// If the word does not have two or three character and thus
	// cannot be a valid card.
	else
	{
		return false;
	}
}

// This function returns true if a string is a valid card.
bool checkComment(string passedWord)
{
	int wordSize = passedWord.size();
	if (wordSize == 2)
	{
		const char commentChar = '/';
		const char firstChar = passedWord[0];
		const char secondChar = passedWord[1];

		// Check to see if both characters of the two
		// character word are '/'
		if ((firstChar == commentChar) && (secondChar == commentChar))
		{
			return true;
		}
	}
	return false;
}

// This function checks if a given string contains "//"
// anywhere in the string and if so modifes the string 
// and sets the comment flag
bool checkContainsComment(string & passedWord)
{
	char slash = '/';
	bool firstSlash = false;
	int size = passedWord.length();

	for (int i = 0; i < size; ++i)
	{
		if ((passedWord[i] == slash) && (firstSlash))
		{
			string tempString;
			for (int j = 0; j < (i - 1); ++j)
			{
				tempString = tempString + passedWord[j];
			}
			passedWord = tempString;
			return true;
		}

		else if ((passedWord[i] == slash) && (!firstSlash))
		{
			firstSlash = true;
		}
	}
	return false;
}

// This function prints out cards from a vector of cards
// in a nicely formatted string
int printCards(const vector<Card> & cardDeck)
{
	string finalPrint;

	// Iterates through the entire cardDeck vector
	for (unsigned int i = 0; i < cardDeck.size(); ++i)
	{
		Card currentCard = cardDeck[i];
		// calls the makeString function to create a 
		// printable string from the currentCard
		string print = makeString(currentCard);
		cout << print << endl;
	}
	return success;
}

// This function makes a string out of a card that 
// describes what type of card it is
string makeString(Card card)
{
	string finalString = "You have the ";

	// Switch statement to add to string based on card value
	switch (card.cardRank)
	{
	case two:
		finalString += "two of ";
		break;
	case three:
		finalString += "three of ";
		break;
	case four:
		finalString += "four of ";
		break;
	case five:
		finalString += "five of ";
		break;
	case six:
		finalString += "six of ";
		break;
	case seven:
		finalString += "seven of ";
		break;
	case eight:
		finalString += "eight of ";
		break;
	case nine:
		finalString += "nine of ";
		break;
	case ten:
		finalString += "ten of ";
		break;
	case jack:
		finalString += "jack of ";
		break;
	case queen:
		finalString += "queen of ";
		break;
	case king:
		finalString += "king of ";
		break;
	case ace:
		finalString += "ace of ";
		break;
	}

	// Switch statement to add to string based on card suit
	switch (card.suit)
	{
	case diamonds:
		finalString += "diamonds!";
		break;
	case hearts:
		finalString += "hearts!";
		break;
	case clubs:
		finalString += "clubs!";
		break;
	case spades:
		finalString += "spades!";
		break;
	}

	return finalString;
}

// This makes a string that is more space-concious
// than the makeString function. For the six of hearts,
// it would print out "*6H*".
string makeSimpleString(Card card)
{
	string finalString = "*";

	// Switch statement to add to string based on card value
	switch (card.cardRank)
	{
	case two:
		finalString += "2";
		break;
	case three:
		finalString += "3";
		break;
	case four:
		finalString += "4";
		break;
	case five:
		finalString += "5";
		break;
	case six:
		finalString += "6";
		break;
	case seven:
		finalString += "7";
		break;
	case eight:
		finalString += "8";
		break;
	case nine:
		finalString += "9";
		break;
	case ten:
		finalString += "10";
		break;
	case jack:
		finalString += "J";
		break;
	case queen:
		finalString += "Q";
		break;
	case king:
		finalString += "K";
		break;
	case ace:
		finalString += "A";
		break;
	}

	// Switch statement to add to string based on card suit
	switch (card.suit)
	{
	case diamonds:
		finalString += "D";
		break;
	case hearts:
		finalString += "H";
		break;
	case clubs:
		finalString += "C";
		break;
	case spades:
		finalString += "S";
		break;
	}

	finalString = finalString + "*";

	return finalString;
}

// This function will check if a hand is of size five and if so write
// it to the card vector.  Regardless, it will then empty the hand.
// This currently is meant for a five card hand.
int validateHand(vector<Card> & cardVector, vector<Card> & hand, int validCardCount)
{
	// If the valid card count is five, then we write the cards to 
	// the card vector and exit the loop
	if (validCardCount == 5)
	{
		int handSize = hand.size();
		for (int i = 0; i < handSize; ++i)
		{
			Card tempCard = hand[i];
			cardVector.push_back(tempCard);
		}
	}

	// Prints out an error if the valid card count is less than the five needed for a hand
	else if (validCardCount < 5)
	{
		cout << "Warning, there were too few cards in this line, this line is not a hand" << endl;
	}

	// Prints out an error if the valid card count is more than the five needed for a hand
	else
	{
		cout << "Warning, there were too many cards in this line, this line is not a hand" << endl;
	}

	hand.clear();

	return success;
}

// Defines the comparison of two cards using the 
// less than operator
bool Card::operator< (const Card & card) const
{
	return (static_cast<int>(cardRank) < static_cast<int>(card.cardRank)) ||
		((static_cast<int>(cardRank) == static_cast<int>(card.cardRank)) && (static_cast<int>(suit) < static_cast<int>(card.suit)));
}

// Defines equality testing for two cards.
bool Card::operator== (const Card & card) const
{
	return ((static_cast<int>(cardRank) == static_cast<int>(card.cardRank)) && (static_cast<int>(suit) == static_cast<int>(card.suit)));
}

// Defines the less than comparison when suit is irrelevant
bool Card::pokerRankCardLessThan(const Card & card) const
{
	return (static_cast<int>(cardRank) < static_cast<int>(card.cardRank));
}