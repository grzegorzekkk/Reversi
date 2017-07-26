#ifndef _HUMAN_CPP_
#define _HUMAN_CPP_

#include "Human.h"

using namespace std;

Human::Human(Board *p, int color) : Player(p, color)
{
}


Human::~Human()
{
}

bool Human::move()
{
	pair<char, short> coords; // Coordinates of pawn to get from player input
	stringstream s;
	string line;
	vector<std::pair<char, short>> validFields = findPlaceToMove(map); // Array of fields where player can place pawn

	if (validFields.empty())  // Unable to move, turn goes to opponent
		return false;

	// Gamestate info
	cout << "Turn of player " << getNick() << " with pawns of color " << (getColor() == 1 ? "black" : "white") 
		<< ". Collected pawns: " << getPossesessedPawns() << endl;
	cout << "You can place your pawn on: " << endl;
	for (auto punkt : validFields)
		cout << punkt.first << punkt.second << " ";
	cout << endl;
	cout << "Type the field where you want to place next pawn" << endl;

	bool validAnswer = false;
	do
	{
		getline(cin, line);
		coords.first = line.at(0); 
		coords.second = line.at(1) - '0'; // Change char to number

		// Check if coordinates entered by player are stored in valid fields array.
		if (find(validFields.begin(), validFields.end(), coords) != validFields.end()) {
			placePawn(coords.first, coords.second);
			validAnswer = true;
		}
		else {
			cout << "Invalid input. Try to type coordinates again" << endl;
		}
	} while (!validAnswer);

	// Valid move
	return true;
}

void Human::setNick()
{
	string nick; 

	do
	{
		cout << "Player with " << (getColor() == 1 ? "black " : "white ") << "pawns. ";
		cout << "Enter your nickname of max 16 characters length." << endl;
		getline(cin, nick);

		if (nick.size() > 16)
			cout << "Nickname cannot be more than 16 characters long. Type it again" << endl;
		if (nick == "Computer")
			cout << "You cannot enter \"Computer\" nickname" << endl;
		if (nick.size() < 1)
			cout << "Your nickname must be at least 1 character long" << endl;

	} while (nick.size() > 16 || nick=="Computer" || nick.size() < 1);


	this->nick = nick;
}

#endif _HUMAN_CPP_
