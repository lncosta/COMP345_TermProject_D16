#include <iostream>
#include <string>
#include "GameEngine.h"

int main(void) {
	ofstream filewriting;
	
	filewriting.open("gamelog.txt");
	
	if (filewriting) {
		//emptying file here
		cout << "Emptying gamelog.txt for this game..." << endl;
		cout << endl;
		filewriting.open("gamelog.txt", std::ofstream::out | std::ofstream::trunc);
		filewriting.close();
	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
	}
  
  
	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine(); 
	LogObserver* obs = new LogObserver(currentGame);
	
	currentGame->menu(0);

	delete obs;
	obs = nullptr;
	return 0;
}