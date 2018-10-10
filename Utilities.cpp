// Utilities.cpp
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains all of the definitions for
// various file utilities, especially error handling.
//
// Lab 4

#include "stdafx.h"
#include "Utilities.h"
#include <string>
#include <iostream>
using namespace std;


// This function returns an enum and prints a string if 
// there are too many arguments.
int moreThanTwoArgumentsMessage(string programName, string fileName)
{
	cout << endl;
	cout << programName << endl;
	cout << endl;
	cout << "It seems that you have encountered an error." << endl;
	cout << "You have run " << programName << " with more than two arguments!" << endl;
	cout << "Please run " << programName << " with either one .txt file argument" << endl;
	cout << "or these two arguments, in any order: " << endl;
	cout << "1.   The .txt file containing the cards" << endl;
	cout << "2.   `-shuffle'" << endl;
	cout << "To run " << programName << " with the default .txt file:" << endl;
	cout << "Type the following:" << endl;
	cout << endl;
	cout << programName << " " << fileName << endl;
	return moreThanTwoArguments;
}

// This function returns an enum and prints a string if there
// are too few arguments
int noArgumentsMessage(string programName, string fileName)
{
	cout << endl;
	cout << programName << endl;
	cout << endl;
	cout << "It seems that you have encountered an error." << endl;
	cout << "You have run " << programName << " with no arguments!" << endl;
	cout << "Please run " << programName << " with either one .txt file argument" << endl;
	cout << "or these two arguments, in any order: " << endl;
	cout << "1.   The .txt file containing the cards" << endl;
	cout << "2.   `-shuffle'" << endl;
	cout << "To run " << programName << " with the default .txt file:" << endl;
	cout << "Type the following:" << endl;
	cout << endl;
	cout << programName << " " << fileName << endl;
	return noArguments;
}


// This function returns an enum and prints a string if there are two
// arguments but neither one includes '-shuffle'
int twoNoShuffleMessage(string programName, string fileName)
{
	cout << endl;
	cout << programName << endl;
	cout << endl;
	cout << "It seems that you have encountered an error." << endl;
	cout << "You have run " << programName << " with two arguments," << endl;
	cout << "but neither one contains `-shuffle'!" << endl;
	cout << "Please run " << programName << " with either one .txt file argument" << endl;
	cout << "or these two arguments, in any order: " << endl;
	cout << "1.   The .txt file containing the cards" << endl;
	cout << "2.   `-shuffle'" << endl;
	cout << "To run " << programName << " with the default .txt file:" << endl;
	cout << "Type the following:" << endl;
	cout << endl;
	cout << programName << " " << fileName << endl;
	return twoNoShuffle;
}

// This function returns an enum and prints a string if there is
// one argument but it is only '-shuffle'
int oneJustShuffleMessage(string programName, string fileName)
{
	cout << endl;
	cout << programName << endl;
	cout << endl;
	cout << "It seems that you have encountered an error." << endl;
	cout << "You have run " << programName << " with one argument," << endl;
	cout << "but it contains `-shuffle'!" << endl;
	cout << "Please run " << programName << " with either one .txt file argument" << endl;
	cout << "or these two arguments, in any order: " << endl;
	cout << "1.   The .txt file containing the cards" << endl;
	cout << "2.   `-shuffle'" << endl;
	cout << "To run " << programName << " with the default .txt file:" << endl;
	cout << "Type the following:" << endl;
	cout << endl;
	cout << programName << " " << fileName << endl;
	return oneJustShuffle;
}


// This function returns an enum and prints a string if
// the .txt could not be opened.
int fileNotOpenMessage(string programName, string fileName)
{
	cout << endl;
	cout << programName << endl;
	cout << endl;
	cout << "The file: " << fileName << " could not be opened." << endl;
	cout << "Either the filename is incorrect or the file does not exist." << endl;
	cout << "Make sure you choose a .txt file in the Debug folder." << endl;
	return fileOpenError;
}

// This function returns an enum and prints a string
// if two hands of size zero are compared
int handSizeZeroMessage()
{
	cout << endl;
	cout << "You tried to compare two empty hands!" << endl;
	cout << "This is not allowed!" << endl;
	return handSizeZero;
}

// This function returns an enum and prints a string
// poker rank tries to run on hands that are not all size five
int handSizeNotFiveMessage()
{
	cout << endl;
	cout << "The size of every hand was not five!" << endl;
	return handSizeNotFive;
}

int tooFewArgumentsMessage(char * programName)
{
	cout << endl << "You have run " << programName << " with too few arguments!" << endl;
	cout << "You should run this program with at least three arguments!" << endl;
	cout << "The first argument should be the name of the game you want to play," << endl;
	cout << "and the next two arguments should be the names of two different players!" << endl;
	cout << "Try `FiveCardDraw Dean Alex'." << endl;
	//
	cout << "If you would like to play an automated player," << endl;
	cout << "Enter the name of the player followed directly by an asterisk ('Joel*')" << endl;
	//
	return tooFewArguments;
}