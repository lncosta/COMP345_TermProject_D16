#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "LoggingObserver.h"
#include "CommandProcessing.h"

/*COMP 345 Section D - Assignment #2
* Fall 2021
* Due November 12th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/

using namespace std;

class GameEngine : public Subject {

private:
	string state;
	vector<Player*> players;
	Map* map;
	Deck* deck;


public:
	//Neutral Player:
	Player* neutral; 

	//Constructors
	GameEngine(void);
	GameEngine(const GameEngine& other);

	//Destructor:
	~GameEngine(void); 

	//Getter and setter
	void setState(string newState);
	string getState(void);


	//Assignment operator
	GameEngine& operator =(const GameEngine& other);

	//Stream Insertion
	friend ostream& operator << (ostream& out, const GameEngine& g);
	friend istream& operator >> (istream& in, GameEngine& g);

	//Methods
	void startupPhase();
	void transition(string newState);
	void addPlayer(void);
	void reinforcementPhase(void);
	void issueOrdersPhase(void);
	void executeOrdersPhase(void);
	int mainGameLoop(void);
	void addPlayer(string name);
	bool loadMap(string fileName);
	bool assignTerritories(void);
	virtual string stringToLog();

};

