#include "orc.h"
#include "util.h"
#include "game.h"

Orc::Orc():NPC('O',180,30,25){
	
}


int Orc::attack(Goblin* g){
	int dmg = g->takeDamage(getAttack()*1.5);
	game->addAction(toString(sym)+" deals "+toString(dmg)+
		" damage to PC. ");
	return dmg;
}