#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"

class Character: public Entity{
public:
	int hp,maxHP;
	int atk, def;
public:
	Character(char sym,int hp,int atk,int def);
	virtual int takeDamage(int dmg);
	virtual int heal(int amt);
	virtual int inflict(int atk);
	virtual int attack(Character* c);
	virtual int getAttack();
	virtual int getDefense();
	virtual int getHP();
	virtual void move(int xDir,int yDir);
	virtual void die();
};

#endif