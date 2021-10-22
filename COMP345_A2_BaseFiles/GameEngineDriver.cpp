#include "GameEngine.h"

void print(string s) {
	cout << s << endl;
}

void print(int s) {
	cout << s << endl;
}

int main() {

	//print("type something");
	GameEngine* ge = new GameEngine;
	CommandProcessor* processor = new CommandProcessor;
	Command* c = processor->getCommand();
	string s = c->returnCommand();
	print(s);

	bool value = processor->validate(c, ge);
	print(value);
	



	//int currentState = 0;
	//int newState = 0;
	/*do {
		newState = ge.menu(currentState);
		currentState = newState;

	} while (currentState != -1);*/

	
	
	

	return 0;
}
