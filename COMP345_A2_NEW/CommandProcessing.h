#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "commandProcessing.h"
using namespace std;


class Command {
	string command;
	string effect;
public:
	//Constructors
	Command(void);
	~Command(void);
	Command(string command);

	//Getter and setter
	string returnCommand(void);
	string returnEffect(void);

	//Assignment operator
	//Command& operator =(const Command& other);

	//Stream insertion:
	//friend ostream& operator << (ostream& out, const Command& c);
	//friend istream& operator >> (istream& in, Command& c);

	//Member function
	void saveEffect(string effect);
};


class CommandProcessor {
private:
	// Data members	
	vector<Command*> commandVector;

public:
	// constructors
	/*CommandProcessor(void);*/
	//~CommandProcessor(void);

	// getter
	vector<Command*> getCommandVector();

	//Assignment operator
	//CommandProcessor& operator =(const CommandProcessor& other);

	//Stream insertion:
	//friend ostream& operator << (ostream& out, const CommandProcessor& cp);
	//friend istream& operator >> (istream& in, CommandProcessor& cp);

	// Member functions
	// getCommnad(void) is for GameEngine/ Player objects's use, which reads a command and then saves the command
	virtual string readCommand(void);
	Command* saveCommand(string command);
	Command* getCommand(void);
	bool validate(string input, string currentState);

};


class FileLineReader {

	string fileName;
	ifstream input;


public:
	//constructor	
	FileLineReader();
	FileLineReader(string fileName);
	virtual string readLineFromFile(void);
	//Assignment operator
	//FileCommandProcessor& operator =(const FileCommandProcessor& other);

	//Stream insertion:
	//friend ostream& operator << (ostream& out, const FileCommandProcessor& f);
	//friend istream& operator >> (istream& in, FileCommandProcessor& f);

	//Member function

};



// The client is GameEngine::menu()
// The target is CommandProcessor which reads commands from the console
// The adaptee is FileCommandProcessor that reads commands from a file
// FileCommandProcessorAdapter is the adapter
class FileCommandProcessorAdapter : public CommandProcessor {
	// addptee class object
	FileLineReader* fprocessor;

public:
	//constructor
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(FileLineReader* processor);
	Command* getCommand(void);

	//Assignment operator
	//FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter& other);

	//Stream insertion:
	/*friend ostream& operator << (ostream& out, const FileCommandProcessorAdapter& fp);
	friend istream& operator >> (istream& in, FileCommandProcessorAdapter& fp);	 */
};



