#ifndef GAME_H
#define GAME_H

#define HEIGHT 25
#define WIDTH 79
#define CHAMBERS 5

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "entity.h"
#include "character.h"
#include "player.h"
#include "npc.h"
#include "potion.h"
#include "treasure.h"
#include "dragon.h"

enum GameState{
	GAME_START,
	GAME_WON,
	GAME_LOST,
	GAME_RUNNING,
};

class Game{
private:
	GameState state;
	int level;
	char grid[HEIGHT][WIDTH];
	int rooms[HEIGHT][WIDTH];
	Entity* occupied[HEIGHT][WIDTH];
	std::string levelFiles[5];

	std::vector<NPC*> npcs;
	std::vector<Potion*> potions;
	std::vector<Treasure*> treasures;
	std::string actions;

	//Helper methods
	void getRooms(int x,int y,int roomNum);
	std::pair<int,int> getRandCoords(int chamber);

public:
	Player* player;

	Game(std::string levelFiles[5] = 0);
	void init();
	void run();

	GameState getState();
	int getLevel() const;

 	std::string getAction() const;
	void clearActions();
	void addAction(std::string str);

	int getRoom(int x,int y);
	bool isClear(int x,int y,bool ignore=false);
	bool hasSpaceAround(int x,int y);
	bool isStairs(int x, int y);

	void setPlayer(Player* p);
	void loadLevel(std::istream& is);

	void addNPC(NPC* npc);
	NPC* getNPC(int x,int y);

	void addPotion(Potion* potion);
	Potion* getPotion(int x,int y);

	void addTreasure(Treasure* t);
	Treasure* getTreasure(int x,int y);

	void addEntity(int x,int y,Entity* e);
	Entity* getEntity(int x,int y);
	void removeEntity(int x,int y, Entity* e);

	void clear();
	~Game();

	friend std::ostream& operator<<(std::ostream &out, const Game &game);
};

#endif