#include "goblin.h"
#include "util.h"
#include "game.h"

Goblin::Goblin():Player("Goblin",110,15,20){

}

int Goblin::attack(NPC* npc){
	int amt = Player::attack(npc);
	if(npc->hp <= 0){
		takeGold(5);
		game->addAction("Stole 5 gold from "+toString(npc->getSymbol())+". ");
	}
	return amt;
}
