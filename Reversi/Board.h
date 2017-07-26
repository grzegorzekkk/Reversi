#ifndef _BOARD_H_
#define _BOARD_H_

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<string>

// Represents one field on the board.
struct Field
{
	bool free = true;
	short color;
};

class Board
{
public:
	Board(int width, int height);
	~Board();

	void print(); // Prints board to console
	void regen(); // Clears board and prepares for next game

	void setGamemode(bool mode); // true - singleplayer, false - multiplayer
	void setPlayerTurn(int id);

	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getGamemode() { return gamemode; }
	int getPlayerTurn() { return playerTurn; }

	std::vector<std::vector<Field>> pawns;
private:
	int width;
	int height;

	bool gamemode; // true - singleplayer, false - multiplayer
	int playerTurn; // 1 - black, 2 - white
};

#endif _BOARD_H_
