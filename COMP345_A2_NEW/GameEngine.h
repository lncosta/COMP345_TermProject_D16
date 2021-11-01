#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"


using namespace std;


class GameEngine {

private:
	string state;
	vector<Player*> players;
	Map* map;
	Deck* deck;


public:
	
	//const string stateArr[9] = { "start", "maploaded", "mapvalidated", "playersadded", "assignreinforcement", "issueorders","executeorders", "win", "exitprogram" };
	

	//Constructors
	GameEngine(void);
	GameEngine(const GameEngine& other);

	//Getter and setter
	void setState(string newState);
	string getState(void);


	//Assignment operator
	GameEngine& operator =(const GameEngine& other);

	//Stream Insertion
	friend ostream& operator << (ostream& out, const GameEngine& g);
	friend istream& operator >> (istream& in, GameEngine& g);

	//Methods
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


class Command {
	string command;
	string effect;	
public:
	//Constructors
	Command(void);
	Command(string command);
	string returnCommand(void);
	string returnEffect(void);
	void saveEffect(string effect);

};


class CommandProcessor {
private:
	// Data members	
	vector<Command*> commandVector;

	// Methods
	string readCommand(void);
	Command* saveCommand(string command);



public:
	// for GameEngine/ Player objects's use 

	Command* getCommand(void);
	bool validate(string input, string currentState);
	vector<Command*> getCommandVector();
};

