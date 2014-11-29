#ifndef NPC_H
#define NPC_H

#include "character.h"

class Player;
class Shade;
class Vampire;
class Goblin;
class Drow;

class NPC: public Character{
public:
	
	NPC(char sym,int hp,int atk,int def);
	void setRoom(int room);

	virtual void act();
	virtual void wander();

	virtual void die();
	virtual void drop();

	using Character::attack;
	virtual int _attack(Player * c);
	virtual int attack(Player* c);
	virtual int attack(Shade* h);
	virtual int attack(Vampire* h);
	virtual int attack(Goblin* g);
	virtual int attack(Drow* d);

	static NPC* createNPC(char type);
};


#endif