#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "commandProcessing.h"
#include "LoggingObserver.h"

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


class Command : public Subject {
	// Data member	
	string command;
	string effect;
public:
	//Constructor
	Command(void);
	Command(string command);
	Command(const Command& other);

	//Destructor
	~Command(void);

	//Getter and setter
	string returnCommand(void);
	string returnEffect(void);

	//Assignment operator
	Command& operator =(const Command& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const Command& c);

	void saveEffect(string input);

	//Method
	virtual string stringToLog();
};


class CommandProcessor : public Subject {
private:
	// Data member
	vector<Command*> commandVector;

	vector <string> listOfMapFiles;
	vector <string> listOfPlayerStrategies;
	int numberOfGames = 0;
	int maxNumberOfTurns = 0;

protected:
	//Method
	string readCommand(void);
	Command* saveCommand(string command);
public:
	//Constructor
	CommandProcessor(void);
	CommandProcessor(const CommandProcessor& other);

	//Destructor
	~CommandProcessor(void);

	//Getter
	vector<Command*> getCommandVector();

	//Assignment operator
	CommandProcessor& operator =(const CommandProcessor& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const CommandProcessor& cp);

	//Method
	Command* getCommand(void);
	bool validate(string input, string currentState);
	bool validateTournamentParameters();
	void processTournamentInput(string);
	virtual string stringToLog();
};

class FileLineReader {
	//Data member
	string fileName;

public:
	//Constructor	
	FileLineReader();
	FileLineReader(string fileName);
	FileLineReader(const FileLineReader& other);

	//Destructor
	~FileLineReader();

	//Assignment operator
	FileLineReader& operator =(const FileLineReader& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const FileLineReader& f);

	//Method
	virtual string readLineFromFile(void);
};


// The client is GameEngine::menu()
// The target is CommandProcessor which reads commands from the console
// The adaptee is FileCommandProcessor that reads commands from a file
// FileCommandProcessorAdapter is the adapter
class FileCommandProcessorAdapter : public CommandProcessor {

	// addptee class object
	FileLineReader* fprocessor;

public:
	//Constructor
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(FileLineReader* processor);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);

	//Destructor
	~FileCommandProcessorAdapter();

	Command* getCommand(void);

	//Assignment operator
	FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter& other);

	//Stream insertion:
	friend ostream& operator << (ostream& out, const FileCommandProcessorAdapter& fp);
};

// free function
vector<string> split(string s, string delimiter);