#pragma once
#include "LoggingObserver.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;




class GameEngine : public Subject {

private:
	string state;

public:

	const string commandArr[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
	const string stateArr[9] = { "start", "maploaded", "mapvalidated", "playersadded", "assignreinforcement", "issueorders","execute_orders", "win", "exitprogram" };


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
	void transition(int index); // if validated ok ,then call setState;	
	//inherited method
	virtual string stringToLog();



};

class Command : public Subject {
	string command;
	string effect;
	void saveEffect(string effect);
public:
	//Constructors
	Command(void);
	Command(string command);
	string returnCommand(void);
	
	//inherited method
	virtual string stringToLog();
};


class CommandProcessor : public Subject {
private:
	// Data members	
	vector<Command*> commandVector;
	
	// Methods
	string readCommand(void);
	Command* saveCommand(string command);
	//inherited method
	virtual string stringToLog();


public:
	// for GameEngine/ Player objects's use 
	Command* getCommand(void);
	bool validate(Command* cd, GameEngine* ge);
};




