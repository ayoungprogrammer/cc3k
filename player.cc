#include "player.h"
#include "game.h"
#include "util.h"
#include <string>

using namespace std;

Player::Player(string type,int hp,int atk,int def):
	Character('@',hp,atk,def),type(type){
	atkBoost = 0;
	defBoost = 0;
	gold = 0;
}

void Player::reset(){
	hp = maxHP;
	gold = 0;
	clearBoost();
}

bool Player::isAtStairs(){
	return game->isStairs(x,y);
}

int Player::getGold(){
	return gold;
}

void Player::takeGold(int amt){
	gold += amt;
}

int Player::getAttack(){
	return max(atk + atkBoost,0);
}

int Player::getDefense(){
	return max(def + defBoost,0);
}

void Player::drinkPotion(Potion* p){
	potionEffect(p->getName(),p->hpBoost,p->atkBoost,p->defBoost);
	p->removeSelf();
}

void Player::potionEffect(string name,int hpBoost,int atkBoost,int defBoost){
	hp += hpBoost;
	if(hp > maxHP)hp = maxHP;
	this->atkBoost += atkBoost;
	this->defBoost += defBoost;

	string attr,sign;
	int value;
	if(abs(hpBoost) > 0){
		value = abs(hpBoost);
		attr = "HP";
	}else if(abs(atkBoost)>0){
		value = abs(atkBoost);
		attr = "attack";
	}else if(abs(defBoost)>0){
		value = abs(defBoost);
		attr = "defense";
	}else{
		value = 0;
		attr = "unknown";
	}
	if(hpBoost + atkBoost + defBoost > 0){
		sign = "gain";
	}else{
		sign = "lose";
	}
	game->addAction("PC drinks a "+name+" potion. ");
	game->addAction("PC "+sign+" "+toString(value)+" "+attr+". ");
}

void Player::attackDir(int xDir,int yDir){
	NPC* npc = game->getNPC(x+xDir,y+yDir);
	if(npc == 0){
		game->addAction("PC hits nothing. ");
	}else{
		attack(npc);
	}
}

void Player::use(int xDir,int yDir){
	Potion* potion = game->getPotion(x+xDir,y+yDir);
	if(potion == 0){
		game->addAction("Nothing to use .");
	}else{
		drinkPotion(potion);
	}
}

void Player::move(int xDir,int yDir){
	if(canMoveDir(xDir,yDir,true)){
		Treasure* t = game->getTreasure(x+xDir,y+yDir);
		if(t != 0){
			if(t->canPickup()){
				int val = t->value;
				takeGold(val);
				t->removeSelf();
				moveDir(xDir,yDir);
				game->addAction("PC moves "+getDirName(xDir,yDir)+" and "+
					"picks up "+toString(val)+" gold. ");
			}else{
				game->addAction("PC fails to pickup treasure. ");
			}
		}else{
			moveDir(xDir,yDir);
			game->addAction("PC moves "+getDirName(xDir,yDir)+". ");
		}
	}else{
		game->addAction("PC moves "+getDirName(xDir,yDir)+" and slams into "+
			"something. ");
	}
}

int Player::attack(NPC* npc){
	int dmg = 0;
	if(npc->getSymbol() == 'L'){
		dmg = attack((Halfling*) npc);
	}else if(npc->getSymbol() == 'D'){
		dmg = attack((Dwarf*) npc);
	}else{
		dmg = _attack(npc);
	}
	return dmg;
}

int Player::_attack(NPC* npc){

	int dmg = Character::attack(npc);

	if(npc->getHP()>0){
		game->addAction("PC deals "+toString(dmg)+" to "+ toString(
			npc->getSymbol()) + " (" +toString(npc->getHP())+ " HP). ");
	}else{
		game->addAction("PC deals "+toString(dmg)+" fatal damage to "+
			toString(npc->getSymbol())+". ");
	}

	return dmg;
}

int Player::attack(Dwarf* d){
	return _attack((NPC*)d);
}

int Player::attack(Halfling* l){
	if(rand()%2 < 1){
		game->addAction("PC misses. ");
		return -1;
	}
	return _attack((NPC*)l);
}

string Player::getType(){
	return type;
}

void Player::clearBoost(){
	atkBoost = 0;
	defBoost = 0;
}

