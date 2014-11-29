#ifndef ELF_H
#define ELF_H

#include "npc.h"
#include "player.h"
#include "drow.h"

class Elf: public NPC{
public:
	Elf();
	
	using NPC::attack;
	int attack(Drow* d);
	int _attack(Player* p);
};

#endif