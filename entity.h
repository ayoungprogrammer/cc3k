#ifndef ENTITY_H
#define ENTITY_H

class Game;

class Entity{
protected:
	int x,y;
	char sym;
public:
	char getSymbol();
	Entity(char sym);
	void moveDir(int dx,int dy);
	bool canMoveDir(int dx,int dy,bool ignoreTreasure = false);
	void setLocation(int x,int y);
	void removeSelf();
	void addSelf();
	int distTo(Entity* e);

	~Entity();

	static Game* game;
};

#endif