#pragma once
#include <string>
#include <iostream>

using namespace std;

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

class GameEngine {
	string state;

public:
	//Constructors:
	GameEngine(void);
	GameEngine(const GameEngine& other);

	//Assignment Operators:
	void setState(string newState);

	//Accessor methods:
	string getState();

	//Stream Insertion:
	friend ostream& operator << (ostream& out, const GameEngine& g);
	friend istream& operator >> (istream& in, GameEngine& g);
	
	//Methods:
	int menu(int i);
};
