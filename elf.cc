#include "elf.h"
#include "util.h"

Elf::Elf():NPC('E',140,30,10){
	
}

int Elf::_attack(Player* p){
	int dmg1 = NPC::_attack(p);
	int dmg2 = NPC::_attack(p);
	return dmg1 + dmg2;
}


int Elf::attack(Drow* d){
	return NPC::_attack(d);
}