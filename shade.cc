#include "shade.h"

Shade::Shade():Player("Shade",125,25,25){

}

int Shade::getScore(){
	return getGold() * 1.5;
}