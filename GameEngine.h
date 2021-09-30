#include <iostream>
class GameEngine {
	std::string state;
public:

	GameEngine();
	std::string getState();
	void setState(std::string newState);
	int menu(int i);
};