#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"


using namespace std;


class GameEngine {

private:
	string state;
	vector<Player*> players;
	Map* map;
	Deck* deck;

public:	

	//Constructors
	GameEngine(void);
	~GameEngine(void);
	GameEngine(const GameEngine& other);

	//Getter and setter
	void setState(string newState);
	string getState(void);

	//Assignment operator
	GameEngine& operator =(const GameEngine& other);

	//Stream Insertion
	friend ostream& operator << (ostream& out, const GameEngine& g);
	friend istream& operator >> (istream& in, GameEngine& g);

	//Member function
	int menu(int i);
	void transition(string newState); 
	void addPlayer(void);
	void reinforcementPhase(void);
	void issueOrdersPhase(void);
	void executeOrdersPhase(void);
	int mainGameLoop(void);
	bool loadMap(void);
	bool assignTerritories(void);
};
