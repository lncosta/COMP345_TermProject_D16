#include "GameEngine.h"

//void print(string s) {
//	cout << s << endl;
//}
//
//void print(int s) {
//	cout << s << endl;
//}

int main() {

	cout << "Type a command "<< endl;
	GameEngine* ge = new GameEngine;
	CommandProcessor* processor = new CommandProcessor;
	Command* c = processor->getCommand();
	string s = c->returnCommand();
	cout << "what you entered is " << s << endl;

	bool value = processor->validate(c, ge);
	



	//int currentState = 0;
	//int newState = 0;
	/*do {
		newState = ge.menu(currentState);
		currentState = newState;

	} while (currentState != -1);*/

	
	
	

	return 0;
}
