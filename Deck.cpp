// Deck.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains definitions for all of the
// member functions of the Deck class. It also 
// includes parseText, which can be used to insert
// cards from a text file onto the deck.
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
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <random>
#include <set>

using namespace std;

// Deck default constructor definition
Deck::Deck()
{
	vector<Card> cardDeck;
}

// THIS CAN THROW AN EXCEPTION
// Deck constructor definition
Deck::Deck(char* fileName)
{

	int result = this->loadDeck(fileName);

	// If loading the deck was not a success, then
	// throw the int that corresponds to the exception
	if (result != success)
	{
		throw fileOpenError;
	}
}

// Deck method to add a card taking it as the only parameter
int Deck::addCard(Card card)
{
	cardDeck.push_back(card);
	return success;
}


// Deck load method definition
int Deck::loadDeck(char* fileName)
{
	int result = parseText((*this), fileName);

	return result;
}

// Deck shuffle method definition
int Deck::shuffleDeck()
{
	vector<Card>::iterator firstIT = cardDeck.begin();
	vector<Card>::iterator lastIT = cardDeck.end();

	// This code comes from the web reference page we were given
	// for the shuffle algorithm
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(firstIT, lastIT, g);

	return success;
}

// Deck size method definition
int Deck::sizeDeck() const
{
	return cardDeck.size();
}

// This function prints the deck
// defines printing for the cards left
// in the deck
int Deck::printDeck() const
{
	vector<Card> printingVector = this->cardDeck;
	string textString;

	vector<Card>::iterator firstIT = printingVector.begin();
	vector<Card>::iterator lastIT = printingVector.end();
	vector<Card>::iterator i;

	for (i = firstIT; i != lastIT; ++i)
	{
		textString = textString + makeSimpleString(*i) + " ";
	}

	cout << endl;
	cout << "The Cards Left in the Deck Are:" << endl;
	cout << textString << endl;

	return success;
}

// Deck non-member insertion operator definition
ostream & operator<< (ostream & out, const Deck & printingDeck)
{
	string finalPrint;

	// Iterates through the entire cardDeck vector
	for (unsigned int i = 0; i < printingDeck.cardDeck.size(); ++i)
	{
		Card currentCard = printingDeck.cardDeck[i];
		// calls the makeString function to create a 
		// printable string from the currentCard
		string print = makeString(currentCard);
		out << print << endl;
	}

	return out;
}


// This function parses a .txt file and pushes valid
// cards onto a vector of cards (deck)
int Deck::parseText(Deck & deckOfCards, char* file)
{
	// Takes the name of the file and attempts to open
	// that file in an ifstream and also creates a newCard
	string filename = file;
	ifstream ifs;
	ifs.open(filename);
	Card newCard;
	vector<Card> hand;
	int validCardCount = 0;
	bool commentFlag = false;
	bool nothingBeforeComment = false;

	// Checks if the file was opened successfully into the stream
	if (ifs.is_open())
	{
		string line, word;

		// While there are more lines in the file
		while (getline(ifs, line))
		{

			// Set there to be no comment on the line
			commentFlag = false;

			// Reset the valid card cout at each line
			validCardCount = 0;

			istringstream iss(line);


			// While there is another word in the line
			while (iss >> word)
			{
				if (checkContainsComment(word))
				{
					commentFlag = true;
				}

				// If the word is empty, then it led with a comment
				if (word == "")
				{
					break;
				}

				// If the word is the comment word
				if (checkComment(word))
				{
					// CHECK TO MAKE SURE THAT THIS ACTUALLY BREAKS
					// THE (ISS >> WORD) WHILE LOOP
					break;
				}

				// If the word is a valid card
				if (validateCard(word))
				{
					validCardCount = validCardCount + 1;
					// Switch statement to assign enum to the
					// newCard based on word
					switch (word[0])
					{
					case '2':
						newCard.cardRank = two;
						break;
					case '3':
						newCard.cardRank = three;
						break;
					case '4':
						newCard.cardRank = four;
						break;
					case '5':
						newCard.cardRank = five;
						break;
					case '6':
						newCard.cardRank = six;
						break;
					case '7':
						newCard.cardRank = seven;
						break;
					case '8':
						newCard.cardRank = eight;
						break;
					case '9':
						newCard.cardRank = nine;
						break;
					case '1':
						newCard.cardRank = ten;
						break;
					case 'J':
					case 'j':
						newCard.cardRank = jack;
						break;
					case 'Q':
					case 'q':
						newCard.cardRank = queen;
						break;
					case 'K':
					case 'k':
						newCard.cardRank = king;
						break;
					case 'A':
					case 'a':
						newCard.cardRank = ace;
						break;
					}

					// Switch statement to assign the suit to
					// newCard based on word
					switch (word[word.size() - 1])
					{
					case 'H':
					case 'h':
						newCard.suit = hearts;
						break;
					case 'D':
					case 'd':
						newCard.suit = diamonds;
						break;
					case 'C':
					case 'c':
						newCard.suit = clubs;
						break;
					case 'S':
					case 's':
						newCard.suit = spades;
						break;
					}

					// Pushes the newly created card back onto the vector and
					// increments the counter
					deckOfCards.cardDeck.push_back(newCard);
				}

				// This is if the card is invalid
				else
				{
					cout << "Invalid Card Read; Card Not Added" << endl;
				}

				// Check if the comment flag has been raised and if so break
				if (commentFlag)
				{
					break;
				}
			}

		}
		return success;
	}

	// If the file couldn't be opened, return the corresponding error.
	else
	{
		return fileOpenError;
	}
}

int Deck::clearDeck()
{
	cardDeck.clear();
	return success;
}
