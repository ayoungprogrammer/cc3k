#ifndef DRAGON_H
#define DRAGON_H

#include "npc.h"
#include "treasure.h"

class Dragon: public NPC{
public:
	Dragon();
	Treasure* hoard;

	void setTreasure(Treasure* t);

	void act();
};

#endif