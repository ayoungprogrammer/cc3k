#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "player.h"
#include "npc.h"
#include "dwarf.h"


class Vampire: public Player{
public:
	Vampire();
	int attack(Dwarf* d); 
	int _attack(NPC* npc);
	int heal(int amt);
};

#endif