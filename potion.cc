#include "potion.h"

Potion::Potion(int hpBoost,int atkBoost,int defBoost,PotionType type):
	Entity('P'),hpBoost(hpBoost),atkBoost(atkBoost),defBoost(defBoost),
	type(type){

}

std::string Potion::getName(){
	if(type == RH_POT)return "Restore Health";
	if(type == BA_POT)return "Boost Attack";
	if(type == BD_POT)return "Boost Defense";
	if(type == PH_POT)return "Poison Health";
	if(type == WA_POT)return "Wound Attack";
	if(type == WD_POT)return "Wound Defense";
	else return "Unknown";
}

Potion* Potion::makePotion(PotionType type){
	Potion *p = 0;
	if(type == RH_POT){
		p = new Potion(10,0,0,type);
	}else if(type == BA_POT){
		p = new Potion(0,5,0,type);
	}else if(type == BD_POT){
		p = new Potion(0,0,5,type);
	}else if(type == PH_POT){
		p = new Potion(-10,0,0,type);
	}else if(type == WA_POT){
		p = new Potion(0,-5,0,type);
	}else if(type == WD_POT){
		p = new Potion(0,0,-5,type);
	}else{
		//cerr<<"Invalid potion choice: "<<num<<endl;
	}
	return p;
}