#ifndef TROLL_H
#define TROLL_H

#include "player.h"

class Troll: public Player{
public:
	Troll();
	void attackDir(int dx,int dy);
	void move(int xDir,int yDir);
	void use(int xDir,int yDir);
};

#endif