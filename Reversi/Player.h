#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<vector>
#include<set>
#include<stack>
#include<iostream>
#include<algorithm>
#include"Board.h"

class Player
{
public:
	Player(Board *p,int color);
	~Player();

	int getColor() { return color; } 
	void setColor(int id) { color = id; } 
	int getPossesessedPawns(); // Returns number of pawns collected by player on the board
	virtual void setNick() = 0;
	void setNick(std::string arg);
	std::string getNick();

	virtual bool move() = 0; 
	std::vector<std::pair<char, short>> findPlaceToMove(Board *map); // Returns array of fields where player can place pawn
	void placePawn(char y, short x); // Places pawn on board and collects oponnents pawns
protected:
	Board *map;
	std::string nick;
private:
	int color; //Black - 1, white - 2
	int possessedPawns;

	// Returns the coordinates of the pawn in the same row as placed pawn
	// and in case when between these pawns are placed only enemys pawns.
	std::pair<char, short> getPawnRow(char yp, short xp, int mode);
	// Returns the coordinates of the pawn in the same column as placed pawn
	// and in case when between these pawns are placed only enemys pawns.
	std::pair<char, short> getPawnColumn(char yp, short xp, int mode);
	// Returns the coordinates of the pawn in the same cross as placed pawn
	// and in case when between these pawns are placed only enemys pawns.
	std::pair<char, short> getPawnCross(char yp, short xp, int mode);
};

#endif _PLAYER_H_
