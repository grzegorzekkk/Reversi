#ifndef _HUMAN_H_
#define _HUMAN_H_

#include<sstream>
#include "Player.h"

class Human : public Player
{
public:
	Human(Board *p, int color);
	virtual ~Human();

	bool move(); 
	void setNick(); 
};

#endif _HUMAN_H_

