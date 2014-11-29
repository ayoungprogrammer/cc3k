#include "dragon.h"
#include "game.h"

Dragon::Dragon():NPC('D',150,20,20){
	
}

void Dragon::setTreasure(Treasure* t){
	hoard = t;
}

void Dragon::act(){
	if(hp<=0)return;
	Player* p = game->player;
	if(distTo(p)<=2 || hoard->distTo(p)<=2){
		attack(p);
	}
}