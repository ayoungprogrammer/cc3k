#include "game.h"
#include "merchant.h"

using namespace std;

Game::Game(string levelFiles[5]){

	Entity::game = this;

	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			grid[i][j] = ' ';
			occupied[i][j] = 0;
			rooms[i][j] = 0;
		}
	}
	actions = "";
	level = 0;
	state = GAME_START;
	cerr<<"test2";
	if(levelFiles != 0){
		for(int i=0;i<5;i++){
			this->levelFiles[i] = levelFiles[i];
		}
	}else{
		this->levelFiles[0] = "floor1.txt";
		this->levelFiles[1] = "floor1.txt";
		this->levelFiles[2] = "floor1.txt";
		this->levelFiles[3] = "floor1.txt";
		this->levelFiles[4] = "floor1.txt";
	}
}

void Game::init(){
	//reset level
	level = 0;
	ifstream ifs(levelFiles[level].c_str());
	//load level 0
	loadLevel(ifs);
	state = GAME_RUNNING;
	//reset merchant hostile flag
	Merchant::hostile = false;
	//reset gold
	player->reset();
	addAction("Player character has spawned. ");
}

void Game::run(){

	if(state != GAME_RUNNING){
		return;
	}

	//Check if player reached stairs
	if(player->isAtStairs()){
		level++;
		if(level >= 5){
			state = GAME_WON;
			return;
		}
		ifstream ifs(levelFiles[level].c_str());
		loadLevel(ifs);
		addAction("Player character went up the stairs. ");
		return;
	}

	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			for(int k=0;k<npcs.size();k++){
				if(occupied[i][j] == npcs[k]){
					npcs[k]->act();
				}
			}
		}
	}

	if(player->hp<=0){
		state = GAME_LOST;
	}
}

GameState Game::getState(){
	return state;
}


bool Game::isStairs(int x,int y){
	return grid[x][y] == '/';
}

void Game::addEntity(int x,int y,Entity* e){
	if(x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH)return;
	if(occupied[x][y] != 0){
		//cerr<<"Something already here"<<endl;
		return;
	}
	occupied[x][y] = e;
}

void Game::removeEntity(int x,int y,Entity* e){
	if(x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH)return;
	if(occupied[x][y] == 0){
		//cerr<<"Nothing to remove"<<endl;
		return;
	}
	if(occupied[x][y] != e){
		cerr<<"Attemping to remove when already removed!";
		return;
	}
	occupied[x][y] = 0;
}

void Game::addNPC(NPC* npc){
	npcs.push_back(npc);
}

void Game::addPotion(Potion* potion){
	potions.push_back(potion);
}

Potion* Game::getPotion(int x,int y){
	if(occupied[x][y] == 0)return 0;
	if(x < 0 || x >= HEIGHT || y < 0 || y>= WIDTH)return 0;
	for(int i=0;i<potions.size();i++){
		if(potions[i] == occupied[x][y]){
			return potions[i];
		}
	}
	return 0;
}

void Game::addTreasure(Treasure* treasure){
	treasures.push_back(treasure);
}

Treasure* Game::getTreasure(int x,int y){
	if(occupied[x][y] == 0)return 0;
	if(x < 0 || x >= HEIGHT || y < 0 || y>= WIDTH)return 0;
	for(int i=0;i<treasures.size();i++){
		if(treasures[i] == occupied[x][y]){
			return treasures[i];
		}
	}
	return 0;
}

Entity* Game::getEntity(int x,int y){
	return occupied[x][y];
}

void Game::setPlayer(Player* p){
	player = p;
}

void Game::getRooms(int x,int y,int roomNum){
	if(x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH)return;
	if(grid[x][y] != '.')return;
	if(rooms[x][y] != 0)return;
	rooms[x][y] = roomNum;
	getRooms(x+1,y,roomNum);
	getRooms(x-1,y,roomNum);
	getRooms(x,y+1,roomNum);
	getRooms(x,y-1,roomNum);
}

pair<int,int> Game::getRandCoords(int chamber){
	int x,y;
	do{
		x = rand() % HEIGHT;
		y = rand() % WIDTH;
	}while(grid[x][y] != '.' || occupied[x][y] != 0 || 
		(rooms[x][y] != chamber && chamber != 0));
	return make_pair(x,y);
}

void Game::loadLevel(istream& is){

	srand(time(NULL));
	clear();

	//Read in grid
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			is.get(grid[i][j]);
			rooms[i][j] = 0;
			occupied[i][j] = 0;
		}
		is.ignore();
	}
	//Figure out room tiles
	int roomNum = 1;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(grid[i][j] == '.' && rooms[i][j] == 0){
				getRooms(i,j,roomNum);
				roomNum++;
			}
		}
	}

	//Spawn player
	int playerChamber = rand() % CHAMBERS + 1;
	pair<int,int> playerCoords = getRandCoords(playerChamber);
	player->setLocation(playerCoords.first,playerCoords.second);

	//Spawn stairs
	int stairChamber;
	do{
		stairChamber = rand() % CHAMBERS + 1;;
	}while(stairChamber != playerChamber); //#debug
	pair<int,int> stairCoords = getRandCoords(stairChamber);
	grid[stairCoords.first][stairCoords.second] = '/';

	//Spawn Potions
	for(int i = 0; i < 10; i++){
		int chamber = rand()%5+1;
		pair<int,int> coords = getRandCoords(chamber);
		Potion* potion = Potion::makePotion((PotionType)(rand()%6));
		potion->setLocation(coords.first,coords.second);
		addPotion(potion);
	}

	//Spawn treasure
	for(int i=0; i < 10;i++){
		int chamber = rand()%5 + 1;
		pair<int,int> coords = getRandCoords(chamber);
		int rnd = rand() % 8;
		TreasureType type;
		if(rnd < 5){
			type = NORMAL_HOARD;
		}
		else if(rnd < 7){
			type = SMALL_HOARD;
		}else{
			type = DRAGON_HOARD;
		}
		Treasure* t = Treasure::makeTreasure(type);
		t->setLocation(coords.first,coords.second);
		addTreasure(t);
		if(type == DRAGON_HOARD){
			if(hasSpaceAround(coords.first,coords.second)){
				Dragon* drag = new Dragon;
				t->setGuardian(drag);
				drag->setTreasure(t);
				int x=0,y=0;
				do{
					x = rand() % 3 - 1;
					y = rand() % 3 - 1;
				}while(!isClear(x + coords.first,y + coords.second));
				drag->setLocation(x + coords.first,y + coords.second);
				addNPC(drag);
			}
		}
	}

	//Spawn enemies
	for(int i = 0; i < 20; i++){
		pair<int,int> coords = getRandCoords(0);
		int rnd = rand() % 18;
		char type;
		if(rnd < 4)type = 'H';
		else if(rnd < 7)type = 'W';
		else if(rnd < 12)type = 'L';
		else if(rnd < 14)type = 'E';
		else if(rnd < 16)type = 'O';
		else type = 'M';
		NPC* npc = NPC::createNPC(type);
		npc->setLocation(coords.first,coords.second);
		addNPC(npc);
	}

	player->clearBoost();
}

int Game::getRoom(int x,int y){
	return rooms[x][y];
}

NPC* Game::getNPC(int x,int y){
	if(occupied[x][y] == 0)return 0;
	if(x < 0 || x >= HEIGHT || y < 0 || y>= WIDTH)return 0;
	for(int i=0;i<npcs.size();i++){
		if(npcs[i] == occupied[x][y]){
			return npcs[i];
		}
	}
	return 0;
}

bool Game::isClear(int x,int y,bool ignoreCoin){
	if(x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH)return false;
	if(occupied[x][y] != 0){
		if(ignoreCoin && occupied[x][y]->getSymbol() == 'G')return true;
		return false;
	}
	if(ignoreCoin && grid[x][y] == '/')return true;
	return (grid[x][y] == '.' || grid[x][y] == '#' || grid[x][y] == '+');
}

bool Game::hasSpaceAround(int x,int y){
	bool hasSpace = false;
	for(int dx = -1;dx <= 1; dx++){
		for(int dy = -1; dy <= 1; dy++){
			if(dx == 0 && dy == 0)continue;
			if(isClear(x+dx,y+dy)){
				hasSpace = true;
			}
		}
	}
	return hasSpace;
}

string Game::getAction() const {
	return actions;
}
void Game::clearActions(){
	actions = "";
}

void Game::addAction(std::string str){
	actions += str;
}

void Game::clear(){
	actions = "";
	for(int i=0;i<npcs.size();i++){
		delete npcs[i];
	}
	npcs.clear();
	for(int i=0;i<potions.size();i++){
		delete potions[i];
	}
	potions.clear();
	for(int i=0;i<treasures.size();i++){
		delete treasures[i];
	}
	treasures.clear();
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			occupied[i][j] = 0;
		}
	}
}

int Game::getLevel() const{
	return level;
}

Game::~Game(){
	clear();
}

ostream& operator<<(ostream &out, const Game &game){
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(game.occupied[i][j] != 0){
				out<<game.occupied[i][j]->getSymbol();
			}else{
				out<<game.grid[i][j];
			}
		}
		out<<endl;
	}
	out<<"Race: "<<game.player->getType()<<" ";
	out<<"Gold: "<<game.player->getGold();
	out<<"\t\t\t"<<game.getLevel()<<endl;
	out<<"HP: "<<game.player->getHP()<<endl;
	out<<"Atk: "<<game.player->getAttack()<<endl;
	out<<"Def: "<<game.player->getDefense()<<endl;
	out<<"Action: "<<game.getAction()<<endl;
	return out;
}