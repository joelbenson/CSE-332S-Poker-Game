// Utilities.h
// Alex DiChristofano, a.dichristofano@wustl.edu
// This file contains all of the declarations for
// general file errors and return messages. This
// file also contains enums for returnMessages and
// static arguments.
//
// Lab 4

#pragma once

#include <string>
using namespace std;

// This function returns an enum and prints a string if 
// there are too many arguments.
int moreThanTwoArgumentsMessage(string, string);

// This function returns an enum and prints a string if there
// are too few arguments
int noArgumentsMessage(string, string);

// This function returns an enum and prints a string if there are two
// arguments but neither one includes '-shuffle'
int twoNoShuffleMessage(string, string);

// This function returns an enum and prints a string if there is
// one argument but it is only '-shuffle'
int oneJustShuffleMessage(string, string);

// This function returns an enum and prints a string if
// the .txt could not be opened.
int fileNotOpenMessage(string, string);

// This function returns an enum and prints a string
// if two hands of size zero are compared
int handSizeZeroMessage();

// This function returns an enum and prints a string
// poker rank tries to run on hands that are not all size five
int handSizeNotFiveMessage();

int tooFewArgumentsMessage(char *);

// This is an enum of all of the different values that
// could be returned.
enum returnMessages {
	success, oneJustShuffle, twoNoShuffle, noArguments,
	moreThanTwoArguments, fileOpenError, handSizeNotFive,
	handSizeZero, indexOutOfRange, instance_not_available,
	unknown_game, game_already_started, no_game_in_progress,
	already_playing, both_decks_empty, tooFewArguments,
	too_many_players, unknownException
};

// This is an enum of the different args that are constant in place
enum args { programTitle, gameName, firstPlayer, secondPlayer };
