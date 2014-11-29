#include "treasure.h"

Treasure::Treasure(int value,TreasureType type):
	Entity('G'),value(value),type(type),guard(0){
	
}

bool Treasure::canPickup(){
	if(guard == 0)return true;
	return guard->hp <= 0;
}

void Treasure::setGuardian(NPC* npc){
	guard = npc;
}


Treasure* Treasure::makeTreasure(TreasureType type){
	Treasure* t = 0;
	if(type == SMALL_HOARD)t = new Treasure(1,type);
	else if(type == NORMAL_HOARD)t = new Treasure(2,type);
	else if(type == MERCHANT_HOARD)t = new Treasure(4,type);
	else if(type == DRAGON_HOARD)t = new Treasure(6,type);
	return t;
}