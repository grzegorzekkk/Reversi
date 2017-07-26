#ifndef _COMPUTER_CPP_
#define _COMPUTER_CPP_

#include "Computer.h"

Computer::Computer(Board *p, int color) : Player(p, color)
{
}


Computer::~Computer()
{
}

bool Computer::move()
{
	std::cout << "Turn of player " << getNick() << "..." << std::endl;

	// Sleep thread to simulate "thinking" of computer
	Sleep(2000);

	std::vector<std::pair<char, short>> validFields = findPlaceToMove(map); // Array of fields where place of pawn would be valid

	if (validFields.empty())  // Unable to move, turn goes to opponent
		return false;

	int i = rand() % validFields.size(); 
	placePawn(validFields[i].first, validFields[i].second);  // Choose 1 random field from valid array

	return true;	// Valid move
}

void Computer::setNick()
{
	nick = "Computer";  // Computer's name is "Computer"
}

#endif _COMPUTER_CPP_
