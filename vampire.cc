#include "vampire.h"
#include "game.h"

Vampire::Vampire():Player("Vampire",50,25,25){

}

int Vampire::_attack(NPC* npc){
	int dmg = Player::_attack(npc);
	heal(5);
	game->addAction("PC steals life for 5. ");
	return dmg;
}

int Vampire::heal(int amt){
	hp += amt;
	return amt;
}

int Vampire::attack(Dwarf* d){
	int dmg = Player::_attack(d);
	takeDamage(5);
	game->addAction("PC is allergic to dwarves (-5 health). ");
	return dmg;
}