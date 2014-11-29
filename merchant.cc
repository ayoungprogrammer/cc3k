#include "merchant.h"
#include "game.h"

bool Merchant::hostile = false;

Merchant::Merchant():NPC('M',30,70,5){
	
}

void Merchant::act(){
	if(hp<=0)return;
	Player* p = game->player;
	if(distTo(p)<=2 && hostile){
		attack(p);
	}else{
		wander();
	}
}

void Merchant::drop(){
	Treasure* t = Treasure::makeTreasure(MERCHANT_HOARD);
	t->setLocation(x,y);
	game->addTreasure(t);
}

int Merchant::takeDamage(int amt){
	int ret = NPC::takeDamage(amt);
	hostile = true;
	return ret;
}