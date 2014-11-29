#include "troll.h"
#include "util.h"
#include "game.h"

Troll::Troll():Player("Troll",120,25,15){

}

void Troll::attackDir(int dx,int dy){
	Player::attackDir(dx,dy);
	int amt = heal(5);
	if(amt > 0)game->addAction("PC heals for "+toString(amt)+" hp. ");
}

void Troll::move(int dx,int dy){
	Player::move(dx,dy);
	int amt = heal(5);
	if(amt > 0)game->addAction("PC heals for "+toString(amt)+" hp. ");
}

void Troll::use(int dx,int dy){
	Player::use(dx,dy);
	int amt = heal(5);
	if(amt > 0)game->addAction("PC heals for "+toString(amt)+" hp. ");
}
