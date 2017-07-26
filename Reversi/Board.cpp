#ifndef _BOARD_CPP_
#define _BOARD_CPP_

#include "Board.h"

using namespace std;

Board::Board(int width, int height)
	: width(width), height(height), pawns(width, std::vector<Field>(height))
{
	// Set default setting of board
	regen();
}


Board::~Board()
{
}

void Board::print()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set green background with black text
	SetConsoleTextAttribute(console, 32);

	// Print header
	cout << "   | ";
	for (int i = 0; i < width; i++)
		cout << i+1 << " | ";
	cout << endl;
	cout << "-------------------------------------" << endl;
	
	// Print rows of the board
	char start = 'a';
	for (int i = 0; i < height; i++)
	{
		cout << " " << char(start + i) << " |";
		for (int j = 0; j < width; j++)
			// Print black pawn
			if (pawns[i][j].color == 1)
				cout << " O |";
			else if (pawns[i][j].color == 2)
			{
				// Print white pawn
				SetConsoleTextAttribute(console, 47);
				cout << " O ";
				SetConsoleTextAttribute(console, 32);
				cout << "|";
			}
			else
				cout << "   |";
		cout << " " << endl;
		cout << "-------------------------------------" << endl;
	}

	// Set default colors of console back
	SetConsoleTextAttribute(console, 7);
	cout << endl;
}

void Board::regen()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			pawns[i][j].color = 0;
			pawns[i][j].free = true;
		}

	pawns[3][3].color = 2;
	pawns[3][3].free = false;

	pawns[3][4].color = 1;
	pawns[3][4].free = false;

	pawns[4][3].color = 1;
	pawns[4][3].free = false;

	pawns[4][4].color = 2;
	pawns[4][4].free = false;
}

void Board::setGamemode(bool mode)
{
	if (mode)
		this->gamemode = true;
	else
		this->gamemode = false;
}

void Board::setPlayerTurn(int id)
{
	this->playerTurn = id;
}

#endif _BOARD_CPP_
