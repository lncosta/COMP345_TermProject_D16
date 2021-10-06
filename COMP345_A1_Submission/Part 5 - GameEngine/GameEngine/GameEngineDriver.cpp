#include "GameEngine.h"

/*COMP 345 Section D - Assignment #1
* Fall 2021
* Due October 8th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/

int main() {
	int currentState = 0;
	int newState = 0;

	GameEngine ge;

	do {
		newState = ge.menu(currentState);
		currentState = newState;

	} while (currentState != -1);

	return 0;
}
