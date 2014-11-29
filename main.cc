#include <iostream>
#include <fstream>
#include <string>

#include "main.h"
#include "util.h"

using namespace std;



int main(){
	Game game;
	Player* player = 0;

	cout<<endl;

	for(int i=0;i<WIDTH;i++){
		cout<<"X";
	}
	cout<<endl;
	for(int i=0;i<HEIGHT-2+6;i++){
		cout<<"X";
		if(i == 12){
			cout<<"      ";
			cout<<"Please resize your screen so this fills your screen.";
			cout<<"                   X"<<endl;
		}else if(i == 13){
			cout<<"      ";
			cout<<"Press [Enter] to continue.";
			cout<<"                                             X"<<endl;
		}else{
			for(int j=0;j<WIDTH-2;j++){
				cout<<" ";
			}
			cout<<"X"<<endl;
		}
	}
	for(int i=0;i<WIDTH-1;i++){
		cout<<"X";
	}
	cin.get();
	
	char ch;
	do{
		cout<<"Welcome to Creature Crawler 3000 (CC3k)"<<endl;
		cout<<"Created by: Michael Young"<<endl;
		cout<<"CS 246 Fall 2014 A5 Project"<<endl;
		cout<<"======================================"<<endl;
		cout<<"Select your player character:"<<endl;
		cout<<"- [S]hade (125 HP, 25 Atk, 25 Def)"<<endl;
		cout<<"- [D]row (150 HP, 25 Atk, 15 Def; 50\% Potion Effect)"<<endl;
		cout<<"- [V]ampire (50 HP, 25 Atk, 25 Def; Gain 5 HP per atk, unlim hp)"
			<<endl;
		cout<<"- [T]roll (120 HP, 25 Atk, 15 Def; 5 HP regen per turn)"<<endl;
		cout<<"- [G]oblin (110 HP, 15 Atk, 20 Def; get 5 gold per kill)"<<endl;
	 	for(int i=0;i<20;i++){
	 		cout<<endl;
	 	}
	 	cout<<"Selection: ";
		cin >> ch;
		if(ch == 'S' || ch == 's'){
			player = new Shade;
		}else if(ch == 'D' || ch == 'd'){
			player = new Drow;
		}else if(ch == 'V' || ch == 'v'){
			player = new Vampire;
		}else if(ch == 'T' || ch == 't'){
			player = new Troll;
		}else if(ch == 'G' || ch == 'g'){
			player = new Goblin;
		}
	}while(player == 0);

	game.setPlayer(player);

	game.init();

	string cmd;
	while(game.getState() == GAME_RUNNING){
		cout<<game<<"Command (? for help): ";
		cin>>cmd;
		game.clearActions();
		
		if(cmd == "m" || cmd == "a" || cmd == "u"){
			string str;
			cin>>str;
			pair<int,int> dir = getDirection(str);	
			if(dir == make_pair(0,0)){
				cout<<"Invalid direction"<<endl;
				continue;
			}
			int dx = dir.first;
			int dy = dir.second;
			if(cmd == "m"){
				player->move(dx,dy);
			}else if(cmd == "a"){
				player->attackDir(dx,dy);
			}else if(cmd == "u"){
				player->use(dx,dy);
			}
		}else if(cmd == "r"){
			game.init();
		}else if(cmd == "q"){
			break;
		}else if(cmd == "?"){
			cin.ignore();
			do{
				cout<<"############ HELP MANUAL ############"<<endl;
				cout<<"m <dir> - move in direction"<<endl;
				cout<<"u <dir> - use potion in direction"<<endl;
				cout<<"a <dir> - attack in direction"<<endl;
				cout<<"r - reset game"<<endl;
				cout<<"q - quit game"<<endl;
				cout<<"Directions: "<<endl;
				cout<<"no - north"<<endl;
				cout<<"ea - east"<<endl;
				cout<<"we - west"<<endl;
				cout<<"so - south"<<endl;
				cout<<"ne - northeast"<<endl;
				cout<<"nw - northwest"<<endl;
				cout<<"se - southeast"<<endl;
				cout<<"sw - southwest"<<endl;
				cout<<"Legend:"<<endl;
				cout<<"H - Human"<<endl;
				cout<<"D - Dragon"<<endl;
				cout<<"W - Dwarf"<<endl;
				cout<<"L - Halfling"<<endl;
				cout<<"O - Orc"<<endl;
				cout<<"E - Elf"<<endl;
				cout<<"M - Merchant"<<endl;
				cout<<"G - Gold"<<endl;
				cout<<"P - Potion"<<endl;
				for(int i=0;i<4;i++)cout<<endl;
				cout<<"[Enter to continue]"<<endl;
			}while(cin.get() != '\n');
			continue;
		}else{
			continue;
		}
		game.run();
	}
	if(game.getState() == GAME_WON){
		cout<<"You win!"<<endl;
	}else if(game.getState() == GAME_LOST){
		cout<<"You lose!"<<endl;
	}


}