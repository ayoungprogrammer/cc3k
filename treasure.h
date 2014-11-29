#ifndef TREASURE_H
#define TREASURE_H

#include "entity.h"
#include "npc.h"

enum TreasureType{
	SMALL_HOARD,
	NORMAL_HOARD,
	MERCHANT_HOARD,
	DRAGON_HOARD
};

class Treasure: public Entity{
	
public:
	int value;
	TreasureType type;
	NPC* guard;

	Treasure(int value,TreasureType type);
	bool canPickup();
	void setGuardian(NPC* npc);

	static Treasure* makeTreasure(TreasureType num);
};

#endif