#ifndef MERCHANT_H
#define MERCHANT_H

#include "npc.h"

class Merchant: public NPC{
public:
	Merchant();

	void act();
	void drop();
	int takeDamage(int amt);
	
	static bool hostile;
};

#endif