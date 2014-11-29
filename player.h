#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "character.h"
#include "potion.h"

class NPC;
class Halfling;
class Dwarf;

class Player: public Character{
	std::string type;
	int gold;
	int atkBoost;
	int defBoost;
protected:
	virtual int _attack(NPC* npc);
public:
	Player(std::string type,int hp,int atk,int def);
	std::string getType();

	int getGold();
	void takeGold(int amt);
	void reset();

	using Character::attack;
	virtual int attack(NPC* npc);
	virtual int attack(Halfling* h);
	virtual int attack(Dwarf* d);

	virtual void attackDir(int dx,int dy);
	virtual void move(int xDir,int yDir);
	virtual void use(int xDir,int yDir);
	virtual void drinkPotion(Potion* p);
	virtual void potionEffect(std::string name,int hpBoost,int atkBoost,
		int defBoost);

	virtual int getAttack();
	virtual int getDefense();

	void clearBoost();

	bool isAtStairs();
};

#endif