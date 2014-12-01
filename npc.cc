#include "npc.h"
#include "player.h"
#include "util.h"
#include "game.h"

#include "npclist.h"
#include "treasure.h"
#include <cstdlib>


using namespace std;

NPC::NPC(char sym,int hp,int atk,int def):
	Character(sym,hp,atk,def){
	
}


void NPC::act(){
	if(hp<=0)return;
	Player* p = game->player;
	if(distTo(p)<=2){
		attack(p);
	}else{
		wander();
	}
}

void NPC::die(){
	Character::die();
	drop();
}
 
void NPC::drop(){
	Treasure* t = Treasure::makeTreasure(NORMAL_HOARD);
	t->setLocation(x,y);
	game->addTreasure(t);
}

void NPC::wander(){
	int dirX = 0, dirY = 0;
	do{
		dirX = (rand() % 3) - 1;
		dirY = (rand() % 3) - 1;
	}while(!game->isClear(x+dirX,y+dirY) || (dirX == 0 && dirY ==0)
		|| game->getRoom(x+dirX,y+dirY) < 1);
	move(dirX,dirY);
}

int NPC::_attack(Player* p){

	if(rand () % 2 < 1){
		game->addAction(toString(sym)+ " misses. ");
		return -1;
	}

	int dmg = Character::attack((Character*)p);
	game->addAction(toString(sym)+" deals "+toString(dmg)+
		" damage to PC. ");
	return dmg;
}

int NPC::attack(Player* p){
	int dmg;
	if(p->getType() == "Shade"){
		dmg = attack((Shade*) p);
	}else if(p->getType() == "Vampire"){
		dmg = attack((Vampire*) p);
	}else if(p->getType() == "Goblin"){
		dmg = attack((Goblin*) p);
	}else if(p->getType() == "Drow"){
		dmg = attack((Drow*) p);
	}else{
		//cerr<<"Unkown type: "<<c->getType()<<endl;
		dmg = _attack(p);
	}
	return dmg;
}

int NPC::attack(Shade* p){
	return _attack((Player*)p);
}

int NPC::attack(Vampire* p){
	return _attack((Player*)p);
}

int NPC::attack(Goblin* p){
	return _attack((Player*)p);
}

int NPC::attack(Drow* p){
	return _attack((Player*)p);
}

NPC* NPC::createNPC(char type){
	if(type == 'H')return new Human;
	else if(type == 'W')return new Dwarf;
	else if(type == 'L')return new Halfling;
	else if(type == 'E')return new Elf;
	else if(type == 'O')return new Orc;
	else if(type == 'M')return new Merchant;
	else if(type == 'D')return new Dragon;
	else return 0;
}

/*
void NPC::attack(Shade* h){
	attack((Character*)h);
}

void NPC::attack(Shade* h){
	attack((Character*)h);
}*/