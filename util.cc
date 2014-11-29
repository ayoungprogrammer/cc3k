#include "util.h"

using namespace std;

string toString(char ch){
	string str = "0";
	str[0] = ch;
	return str;
}

string toString(int n){
	ostringstream ss;
	ss << n;
	return ss.str();
}

string getDirName(int xDir,int yDir){
	if(xDir == -1 && yDir == 0)return "north";
	else if(xDir == 1 && yDir == 0)return "south";
	else if(xDir == 0 && yDir == -1)return "west";
	else if(xDir == 0 && yDir == 1)return "east";
	else if(xDir == -1 && yDir == -1)return "northwest";
	else if(xDir == -1 && yDir == 1)return "northeast";
	else if(xDir == 1 && yDir == -1)return "southwest";
	else if(xDir == 1 && yDir == 1)return "southeast";
	else return "nowhere";
}

pair<int,int> getDirection(string str){
	if(str == "no")return make_pair(-1,0);
	else if(str == "no")return make_pair(-1,0);
	else if(str == "so")return make_pair(1,0);
	else if(str == "ea")return make_pair(0,1);
	else if(str == "we")return make_pair(0,-1);
	else if(str == "ne")return make_pair(-1,1);
	else if(str == "nw")return make_pair(-1,-1);
	else if(str == "se")return make_pair(1,1);
	else if(str == "sw")return make_pair(1,-1);
	else return make_pair(0,0);
}