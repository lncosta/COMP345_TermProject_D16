#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"


using namespace std;

class GameEngine {
	string state;
	vector<Player*> players;
	Map* map;
	Card* deck; 

public:
	//Constructors
	GameEngine(void);
	GameEngine(const GameEngine& other);

	//Getter and setter
	void setState(string newState);
	string getState();

	//Assignment operator
	GameEngine& operator =(const GameEngine& other);

	//Stream Insertion
	friend ostream& operator << (ostream& out, const GameEngine& g);
	friend istream& operator >> (istream& in, GameEngine& g);
	
	//Methods
	int menu(int i);
	void addPlayer(void);
	void reinforcementPhase(void);
	void mainGameLoop(void);
	bool loadMap(void);

	bool assignTerritories(void);

};