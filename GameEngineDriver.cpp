#include "GameEngine.h"

int main() {
	int currentState = 0;
	int newState = 0;

	GameEngine ge{};

	do {
		newState = ge.menu(currentState);
		currentState = newState;

	} while (currentState != -1);

	return 0;
}