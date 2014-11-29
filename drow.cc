#include "drow.h"

Drow::Drow():Player("Drow",150,25,15){

}

void Drow::potionEffect(std::string name,int hpBoost,int atkBoost,int defBoost){
	Player::potionEffect(name,hpBoost*1.5,atkBoost*1.5,defBoost*1.5);
}