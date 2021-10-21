#include <iostream>
#include <string>
#include "GameEngine.h"
int main(void) {
	GameEngine* currentGame = new GameEngine(); 
	currentGame->menu(0);
	return 0;
}