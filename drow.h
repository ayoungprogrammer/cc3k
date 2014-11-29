#ifndef DROW_H
#define DROW_H

#include "player.h"
#include <string>

class Drow: public Player{
public:
	Drow();
	void potionEffect(std::string name, int hpBoost,int atkBoost,
		int defBoost);
};

#endif