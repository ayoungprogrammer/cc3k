#include "entity.h"
#include "game.h"

Game* Entity::game = NULL;

Entity::Entity(char sym):sym(sym){
	x = -1;
	y = -1;
}

void Entity::setLocation(int x,int y){
	removeSelf();
	this->x = x;
	this->y = y;
	addSelf();
}

void Entity::addSelf(){
	game->addEntity(x,y,this);
}

void Entity::removeSelf(){
	game->removeEntity(x,y,this);
}

char Entity::getSymbol(){
	return sym;
}

bool Entity::canMoveDir(int dirX,int dirY,bool ignore){
	return game->isClear(x+dirX,y+dirY,ignore);
}

void Entity::moveDir(int dirX,int dirY){
	setLocation(x+dirX,y+dirY);
} 

int Entity::distTo(Entity* e){
	return (e->x - x) * (e->x - x) + (e->y - y) * (e->y - y);
}

Entity::~Entity(){
	
}