#include <iostream>
#include <string>
#include "GameEngine.h"
int main(void) {

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();
	currentGame->menu(0);
	return 0;
}