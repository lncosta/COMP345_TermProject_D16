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
	string command;
	string effect;
public:
	//Constructors
	Command(void);
	Command(string command);
	string returnCommand(void);
	string returnEffect(void);
	//The Command::saveEffect() method can be used to save the effect of the command as a string. 
	void saveEffect(string input);

	virtual string stringToLog();
};


class CommandProcessor : public Subject {
private:
	// Data members	
	vector<Command*> commandVector;

protected:
	//The protected CommandProcessor::readCommand() method reads a string from the console. 
	string readCommand(void);
	//The protected CommandProcessor::saveCommand() method saves the command in the list of commands.
	Command* saveCommand(string command);
public:
	// The public CommandProcessor::getCommand() method can be used by the GameEngine to read and save a command when needed. 
	Command* getCommand(void); 
	//The CommandProcessor::validate() command can be used to validate if a given command is valid in the current game state. 
	bool validate(string input, string currentState);
	vector<Command*> getCommandVector();
	virtual string stringToLog();
};



class FileLineReader {

	string fileName;
	//ifstream input;


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
