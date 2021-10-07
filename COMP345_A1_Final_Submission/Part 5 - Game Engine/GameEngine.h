#pragma once
#include <string>
#include <iostream>

using namespace std;

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