#ifndef ORC_H
#define ORC_H

#include "npc.h"
#include "goblin.h"

class Orc: public NPC{
public:
	Orc();
	int attack(Goblin* g);
};

#endif