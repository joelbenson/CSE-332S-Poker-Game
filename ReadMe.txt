========================================================================
    CONSOLE APPLICATION : Lab4 Project Overview
========================================================================

CSE 332 Lab 4:

Alexander DiChristofano, a.dichristofano@wustl.edu, ID 450420
Dean Choi, jaehoon.choi@wustl.edu, ID 449668
Joel Benson, joel.benson@wustl.edu, ID 450521

Sources Used:
	Everything that we did was on our own, we just used cppreference to understand
	the functionality of some functions of data types.

//////////////////////////////////////////////////////////////////////////////
Documentation of Errors and Warnings While Creating the Program
//////////////////////////////////////////////////////////////////////////////

We came across many different errors when creating our program. They are below.

We had an error that would allow a player to keep raising even if they did not have
	chips. This has been fixed but checking before raising how many chips a
	player has.

We had an error that would result in a player having 4XXXXXXXXX chips
	when a player was betting since a
	player could bet 2 chips even if they had 1. We changed this by making
	sure in this situation a player could only bet one chip.

We were also accidentally indexing out of vector when we would try to access a 
	player after their removal. This is not safe and we stopped doing it!

//////////////////////////////////////////////////////////////////////////////
Program Design Choices
//////////////////////////////////////////////////////////////////////////////

To handle with creating new game, we defined a function called “rungame” in Game.h 
	and it is triggered when user asks to start another game. It is almost same
	code as the one for lab4.cpp, but since the user input is different for initial 
	game initiation and the second one, we decided to create another function 
	with almost the same functionality.

To print out the final hands of players, we chose to print out all of their seven cards
	and print out the rank of their best five cards. This follows all of the
	instructions as we are determining the best five card rank from the seven cards.

To implement betting for each round, we created two new functions that are defined 
	separately for each game. The first function is bettingRound, which calls the
	function bettingTurn for each player. This allows us to continuously ask each 
	player to make a bet until either all players are in agreement, or everyone except
	for one has folded.

For each betting turn, we print out the players options given what the current bet 
	requirement is and take their input on the command line to determine which 
	action they want to take. If a player does not have enough chips to bet any more,
	they will simply be skipped but remain in the round. If a player only has one 
	more chip to bet, they can only raise the bet by one chip.

The logic of bettingRound is that it iterates through all of the players calling bettingTurn
	until conditions are satisfied to end the betting. After everyone has made a bet,
	the program counts the number of players that are ready. A player is ready only 
	if they have either folded, their current bet is equal to the betRequirement, or
	they have bet all of the chips that they have. 

The variables we added to maintain this logic consists of betRequirement and chipPot in our
	Game class and currentBet and folded in our Player class. This helps us keep track
	of the betting status of each player in each of these functions, and keeps a running
	pot of chips that is dealt out at the end of the round.

Within each game, we have a new variable called roundOver that is constantly updated after 
	each betting round to check if all of the players have folded. If this is the case,
	roundOver is set to true, and the round skips to the end where each player is ranked 
	according to their hand and their folded status.

If at any point a player does not have any chips remaining, the game prints out a message 
	asking if they would like to update their chip count to 20. If they reply 'yes' then
	they remain in the game and are awarded 20 chips, otherwise they are either forced
	to leave the game, or are not allowed to join in the first place. We check this at 
	the beginning of each round by checking the new playerChips member variable of our 
	Player class.

We decided that a player would have to type "none" to not discard any cards,
	and since we gave the player this instruction we felt that this was appropriate.

We decided that a player would type the index of the card in order to discard 
	that card, and felt that since we explained it to the player this was justified.
	To discard the third card in the hand, type "2".

We decided not to let more than ten players play at once, since a deck is only
	52 cards and thus five cards could not be dealt to more players than that.

For the extra credit, we decided that the asterisk for an automated player had
	to come after the player name, in order to make it easier to parse through.

We decided to store the count of each type of card number or suit in an array,
	so that we could easily access the count and the value of each.  This also
	made it easier to detect straights.

We also decided to separately check if the straight was two three four five ace
	since this was only one case and therefore not too bad to check manually.

We allowed multiple cards of the same type to be added to a hand since the game 
	itself will dictate whether or not we are playing with multiple decks.

We chose not to create destructors for the Hand and Deck class since they included
	no member variables that could not be destructed in a default way.

We chose to print out stars between cards of a hand to make them look nicer. For face
	down cards it prints out as ***. We chose a design to print out * before and
	after the card we print out. For example, *7D* ***, so one asterisk * will 
	print out ***.

We chose to print out the poker rank of each hand so that it was easier to delineate
	hands in a meaningful way in Five Card Draw.

We also chose to print out statements that let the user know what part of the round
	or if there were problems adding a player to the game so that the user knew
	what was going on.

///////////////////////////////////////////////////////////////////////////////
Test Cases
///////////////////////////////////////////////////////////////////////////////

We checked to make sure that if everyone but one person folds, the game ends instantaneously.

We checked that a player is asked to recharge their chips if they run out and that it
	properly goes to 20.

We played Seven Card Stud and made sure that the proper cards were hidden from a player
	and it wasn't their turn.

We tested to see that if a player folds then they cannot win the game even if they
	have the highest hand.

We tested to make sure that a player cannot bet more than they currently have in chips
	where it be calling or raising.

We tried to play the game with fewer than two players or more than ten players
	at many points in the game for FiveCardDraw and more than seven players
	for SevenCardStud and checked to make sure that the game would end, and
	it did
	(Lab3.exe FiveCardDraw a a) and other variations.

We individually checked all of the game functions to make sure that the exceptions
	thrown were the correct ones, checking them against their value in the program.
	Many of these actually are handled by the main function, so we had to unsafely
	call the game functions specifically to make them occur.

We tested to make sure that once the program ended all players that were in the
	game had a save file created for them, which is what happened.

We tested to make sure that when a player joins a game if they have a save file
	already that file is correctly opened and read.

We tested error handling when a user does not input three arguments, and this 
	worked well and returned a message and the non-zero value 15.

We tested to make sure that all player rankings and assignments of wins were
	happening correctly.

We tested to make sure that a non-zero value (10) was returned if a game
	that was not called "FiveCardDraw" was attempted to be played.
	(Lab3.exe FiveCard a b)

We tested to make sure that player discard automation was working correctly.

We tested to make sure that when an automated player leaves the game then they
	have a file created the same as an automated player. We also tested that they
	can read files in that were previously assigned to a human player successfully.

=============================================================================
END OF LAB WRITE-UP
=============================================================================

AppWizard has created this Lab4 application for you.

This file contains a summary of what you will find in each of the files that
make up your Lab4 application.


Lab4.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Lab4.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Lab4.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Lab4.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
