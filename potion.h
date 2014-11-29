#ifndef POTION_H
#define POTION_H

#include <string>
#include "entity.h"

enum PotionType{
	RH_POT,
	BA_POT,
	BD_POT,
	PH_POT,
	WA_POT,
	WD_POT
};

class Potion: public Entity{
public:
	int hpBoost;
	int atkBoost;
	int defBoost;
	PotionType type;
	Potion(int hpBoost,int atkBoost,int defBoost,PotionType type);
	std::string getName();
	static Potion* makePotion(PotionType num);
};

#endif