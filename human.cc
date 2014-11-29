#include "human.h"
#include "treasure.h"
#include "game.h"

Human::Human():NPC('H',140,20,20){
	
}

void Human::drop(){
	NPC::drop();
	if(game->hasSpaceAround(x,y)){
		int dx=0,dy=0;
		do{
			dx = rand() % 3 - 1;
			dy = rand() % 3 - 1;
		}while(!game->isClear(x+dx,y+dy));
		Treasure* t = Treasure::makeTreasure(NORMAL_HOARD);
		t->setLocation(x+dx,y+dy);
		game->addTreasure(t);
	}
}