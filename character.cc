#include "character.h"
#include <cmath>

using namespace std;

Character::Character(char sym,int hp,int atk,int def):
	Entity(sym),hp(hp),maxHP(hp),atk(atk),def(def){
}

int Character::getHP(){
	return hp;
}

int Character::getAttack(){
	return atk;
}

int Character::getDefense(){
	return def;
}

int Character::takeDamage(int dmg){
	hp -= dmg;
	if(hp <= 0){
		hp = 0;
		die();
	}
	return dmg;
}

void Character::die(){
	removeSelf();
}

int Character::heal(int amt){
	if(hp+amt > maxHP){
		hp = maxHP;
		return maxHP - hp;
	}else{
		hp += amt;
		return amt;
	}
}

int Character::inflict(int atk){
	int dmg = ceil((100.0/(100.0+getDefense()))*atk);
	takeDamage(dmg);
	return dmg;
}

void Character::move(int xDir,int yDir){
	if(canMoveDir(xDir,yDir)){
		moveDir(xDir,yDir);
	}
}

int Character::attack(Character *c){
	return c->inflict(getAttack());
	//cerr<<"Not implemented!"<<endl;
}
