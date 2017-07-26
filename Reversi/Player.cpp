#ifndef _PLAYER_CPP_
#define _PLAYER_CPP_

#include "Player.h"

Player::Player(Board *p, int color) : map(p), possessedPawns(2), color(color)
{
}


Player::~Player()
{
}

int Player::getPossesessedPawns()
{
	int n=0;

	// Searches board for pawns of color same as player
	for (int i = 0; i < map->getHeight(); i++)
		for (auto x : map->pawns[i])
		{
			// If found, add to counter
			if (x.color == this->color)
				n++;
		}

	return n;
}

void Player::setNick(std::string arg)
{
	nick = arg;
}

std::string Player::getNick()
{
	return nick;
}

std::vector<std::pair<char, short>> Player::findPlaceToMove(Board *map)
{
	int color = getColor();

	std::vector<std::pair<char, short>> validCoords;
	std::set<std::pair<char, short>> uniqueCoords;

	int width = map->getWidth();
	int height = map->getHeight();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Found field without pawn
			if (map->pawns[i][j].free)
			{
				std::pair<char, short> validField;
				validField.first = i + 97;
				validField.second = j;

				// Search for pawn of player color in a row
				std::pair<char, short> fieldRowAfter = getPawnRow(validField.first, validField.second, 0);
				std::pair<char, short> fieldRowBefore = getPawnRow(validField.first, validField.second, 1);

				// Search for pawn of player color in a column
				std::pair<char, short> fieldColumnAfter = getPawnColumn(validField.first, validField.second, 0);
				std::pair<char, short> fieldColumnBefore = getPawnColumn(validField.first, validField.second, 1);

				// Search for pawn of player color in a cross
				std::pair<char, short> fieldLeftUpCross = getPawnCross(validField.first, validField.second, 0);
				std::pair<char, short> fieldLeftDownCross = getPawnCross(validField.first, validField.second, 1);
				std::pair<char, short> fieldRightDownCross = getPawnCross(validField.first, validField.second, 2);
				std::pair<char, short> fieldRightUpCross = getPawnCross(validField.first, validField.second, 3);

				// Count columns from 1
				validField.second += 1;

				if (fieldRowAfter.first != -1)
					uniqueCoords.insert(validField);
				if (fieldRowBefore.first != -1)
					uniqueCoords.insert(validField);

				if (fieldColumnAfter.first != -1)
					uniqueCoords.insert(validField);
				if (fieldColumnBefore.first != -1)
					uniqueCoords.insert(validField);

				if (fieldLeftUpCross.first != -1)
					uniqueCoords.insert(validField);
				if (fieldLeftDownCross.first != -1)
					uniqueCoords.insert(validField);
				if (fieldRightDownCross.first != -1)
					uniqueCoords.insert(validField);
				if (fieldRightUpCross.first != -1)
					uniqueCoords.insert(validField);
			}
		}
	}

	for (auto pkt : uniqueCoords)
	{
		validCoords.push_back(pkt);
	}

	return validCoords;
}

void Player::placePawn(char y, short x)
{
	int py, px, color;
	int j;

	py = y - 97; // Change char to integer to move on array
	px = x - 1; 

	color = getColor();

	// Place pawn on the board
	map->pawns[py][px].color = color;
	map->pawns[py][px].free = false;

	std::stack<std::pair<int, int>> coords;
	std::pair<int, int> coord;

	//Change pawns on right of placed
	if(getPawnRow(py+97, px, 0).first != -1)
		for (int i = px + 1; i < map->getWidth() && map->pawns[py][i].color != this->color && !map->pawns[py][i].free; i++)
		{
			coord.first = py;
			coord.second = i;
			coords.push(coord);
		}
	//Change pawns on left of placed
	if (getPawnRow(py + 97, px, 1).first != -1)
		for (int i = px - 1; i >= 0 && map->pawns[py][i].color != this->color && !map->pawns[py][i].free; i--)
		{
			coord.first = py;
			coord.second = i;
			coords.push(coord);
		}
	//Change pawns on down of placed
	if (getPawnColumn(py + 97, px, 0).first != -1)
		for (int i = py + 1; i < map->getHeight() && map->pawns[i][px].color != this->color && !map->pawns[i][px].free; i++)
		{
			coord.first = i;
			coord.second = px;
			coords.push(coord);
		}
	//Chenge pawns on up of placed
	if (getPawnColumn(py + 97, px, 1).first != -1)
		for (int i = py - 1; i >= 0 && map->pawns[i][px].color != this->color && !map->pawns[i][px].free; i--)
		{
			coord.first = i;
			coord.second = px;
			coords.push(coord);
		}

	//Change pawns on the cross
	if (getPawnCross(py + 97, px, 0).first != -1)
		for (int i = py - 1, j = px-1; i >= 0 && j>=0 && map->pawns[i][j].color != this->color && !map->pawns[i][j].free; i--, j--)
		{
			coord.first = i;
			coord.second = j;
			coords.push(coord);
		}
	if (getPawnCross(py + 97, px, 1).first != -1)
		for (int i = py + 1, j = px - 1; i < map->getHeight() && j >= 0 && map->pawns[i][j].color != this->color && !map->pawns[i][j].free; i++, j--)
		{
			coord.first = i;
			coord.second = j;
			coords.push(coord);
		}
	if (getPawnCross(py + 97, px, 2).first != -1)
		for (int i = py + 1, j = px + 1; i < map->getHeight() && j < map->getWidth() && map->pawns[i][j].color != this->color && !map->pawns[i][j].free; i++, j++)
		{
			coord.first = i;
			coord.second = j;
			coords.push(coord);
		}
	if (getPawnCross(py + 97, px, 3).first != -1)
		for (int i = py - 1, j = px + 1; i >= 0 && j < map->getWidth() && map->pawns[i][j].color != this->color && !map->pawns[i][j].free; i--, j++)
		{
			coord.first = i;
			coord.second = j;
			coords.push(coord);
		}

	// Change color of collected pawns
	while (!coords.empty())
	{
		std::pair<int, int> tmp = coords.top();
		coords.pop();
		map->pawns[tmp.first][tmp.second].color = color;
	}
}

std::pair<char, short> Player::getPawnRow(char yp, short xp, int mode)
{
	int width = map->getWidth();
	std::pair<char, short> coord;
	coord.first = -1;
	
	// char to int
	int y = yp - 97;

	//Searching for pawn after proposed
	if (mode == 0)
	{
		for (int x = xp + 2; x < width; x++)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = xp + 1; l < x; l++)
					if (map->pawns[y][l].color == color || map->pawns[y][l].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}
	//Searching for pawn before proposed
	else if (mode == 1)
	{
		for (int x = xp - 2; x > -1; x--)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = xp - 1; l > x; l--)
					if (map->pawns[y][l].color == color || map->pawns[y][l].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}

	return coord;
}

std::pair<char, short> Player::getPawnColumn(char yp, short xp, int mode)
{
	int height = map->getHeight();
	std::pair<char, short> coord;
	coord.first = -1;

	// char to int
	int orygY = yp - 97;
	int y = orygY;

	//Searching for pawn on down of proposed
	if (mode == 0)
	{
		for (int y = orygY + 2; y < height; y++)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][xp].color == color && !(map->pawns[y][xp].free))
			{
				coord.first = y;
				coord.second = xp;

				// Check if between pawns are enemys pawns
				for (int l = orygY + 1; l < y; l++)
					if (map->pawns[l][xp].color == color || map->pawns[l][xp].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}
	//Searching for pawn on up of proposed
	else if (mode == 1)
	{
		for (int y = orygY - 2; y > -1; y--)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][xp].color == color && !(map->pawns[y][xp].free))
			{
				coord.first = y;
				coord.second = xp;

				// Check if between pawns are enemys pawns
				for (int l = orygY - 1; l > y; l--)
					if (map->pawns[l][xp].color == color || map->pawns[l][xp].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}

	return coord;
}

std::pair<char, short> Player::getPawnCross(char yp, short xp, int mode)
{
	int height = map->getHeight();
	int width = map->getWidth();
	std::pair<char, short> coord;
	coord.first = -1;

	// char to int
	int orygY = yp - 97;
	int y = orygY;
	int x = xp;
	int i, j;

	//Searching for pawn on left-up cross of proposed
	if (mode == 0)
	{
		for (int y = orygY - 2, x = xp - 2; y >=0 && x>=0; y--, x--)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = orygY - 1, j = xp - 1; l > y && j>x; l--, j--)
					if (map->pawns[l][j].color == color || map->pawns[l][j].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}
	//Searching for pawn on left-down cross of proposed
	else if (mode == 1)
	{
		for (int y = orygY + 2, x = xp - 2; y < height && x >= 0; y++, x--)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = orygY + 1, j = xp - 1; l < y && j>x; l++, j--)
					if (map->pawns[l][j].color == color || map->pawns[l][j].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}
	//Searching for pawn on right-down cross of proposed
	else if (mode == 2)
	{
		for (int y = orygY + 2, x = xp + 2; y < height && x < width; y++, x++)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = orygY + 1, j = xp + 1; l < y && j<x; l++, j++)
					if (map->pawns[l][j].color == color || map->pawns[l][j].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}
	//Searching for pawn on right-up cross of proposed
	else if (mode == 3)
	{
		for (int y = orygY - 2, x = xp + 2; y >=0 && x < width; y--, x++)
		{
			//Found pawn of the same color and on other field
			if (map->pawns[y][x].color == color && !(map->pawns[y][x].free))
			{
				coord.first = y;
				coord.second = x;

				// Check if between pawns are enemys pawns
				for (int l = orygY - 1, j = xp + 1; l > y && j<x; l--, j++)
					if (map->pawns[l][j].color == color || map->pawns[l][j].free)
					{
						coord.first = -1;
						break;
					}
				//1 pawn on this side is enough
				break;
			}
		}
	}

	return coord;
}

#endif _PLAYER_CPP_