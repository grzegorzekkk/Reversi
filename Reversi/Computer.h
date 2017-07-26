#ifndef _COMPUTER_H_
#define __COMPUTER_H_

#include "Player.h"
class Computer : public Player
{
public:
	Computer(Board *p, int color);
	virtual ~Computer();

	bool move(); 
	void setNick();
};

#endif _COMPUTER_H_

