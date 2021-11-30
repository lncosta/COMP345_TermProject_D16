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
	
	string strToLog;

public:
	//Has Human Player:
	
	bool hasHuman = false; 
	//Neutral Player:
	Player* neutral;
	vector<string> winnersPerMap;
	vector< vector<string> > winnersTournament;

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

	//Stream insertion
	friend ostream& operator << (ostream& out, const GameEngine& g);

	//Methods	
	virtual string stringToLog(void);
	void startupPhase(void);
	int mainGameLoop(int);
	bool isThereAwinner(void);
	bool isThereAwinnerS(void);
	void transition(string newState);
	bool loadMap(string fileName);
	void addPlayer(void);
	void addPlayer(string name);
	void addPlayer(string name, string strategy);
	void removePlayer(Player* toRemove);
	bool assignTerritories(void);
	void reinforcementPhase(void);
	void issueOrdersPhase(void);
	void executeOrdersPhase(void);

};
