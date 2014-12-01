#include "dragon.h"
#include "game.h"

Dragon::Dragon():NPC('D',150,20,20){
	hoard = 0;
}

void Dragon::setTreasure(Treasure* t){
	hoard = t;
}

void Dragon::act(){
	if(hp<=0)return;
	Player* p = game->player;
	if(distTo(p)<=2 ){
		attack(p);
	}
	else if(hoard != 0){
		if(hoard->distTo(p)<=2){
			attack(p);
		}
	}
}