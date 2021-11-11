#pragma once
#include "CommandProcessing.h"
#include <limits>
using namespace std;

// -----------------------------------Command class ----------------------------------------
// Constructors
Command::Command(void) {
	command = "Default";
	effect = "Default";
}

Command::Command(string input) : command(input){
}

Command::Command(const Command& other) {
	command = other.command;
	effect = other.effect;
}

// Destructor
Command::~Command(void) {
	cout << "Destroying a command object." << endl;
}

//Getter and Setter
string Command::returnCommand(void) {
	return command;
}

string Command::returnEffect(void) {
	return effect;
}

//Assignment operator
Command& Command::operator =(const Command& other) {
	command = other.command;
	effect = other.effect;
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const Command& c) {
	out << "The command is " << c.command << " and the effect is " << c.effect << endl;
	return out;
}

//The Command::saveEffect() method can be used to save the effect of the command as a string. 
void Command::saveEffect(string input) {

	string theEffect;
	if (input == "loadmap") {
		theEffect = "Map has been successfully loaded.";
	}
	else if (input == "validatemap") {
		theEffect = "Map has been validated.";
	}
	else if (input == "addplayer") {
		theEffect = "The player has been added.";
	}
	else if (input == "gamestart") {
		theEffect = "Reinforcement has been assigned.";
	}
	else if (input == "replay") {
		theEffect = "The last game settings has been erased. Ready to take new settings.";
	}
	else if (input == "quit") {
		theEffect = "Program exits";
	}

	this->effect = theEffect;
	Notify();
}

// redefine the virtual method inherited from Subject class
string Command::stringToLog() {
	return "Current effect: " + effect;
}

// -----------------------------------CommandProcessor class ----------------------------------------

//Constructor
CommandProcessor::CommandProcessor(void) {

	commandVector = vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& other) {
	for (auto p : other.commandVector) {
		Command* temp = new Command(*p);
		commandVector.push_back(temp);
	}
}

//Destructor
CommandProcessor::~CommandProcessor(void) {

	cout << "Destroying CommandProcessor." << endl;
	for (auto p: commandVector) {
		delete p;
	}
	commandVector.clear();

}

//Getter
vector<Command*>CommandProcessor::getCommandVector() {
	return commandVector;
};

//Assignment operator
CommandProcessor& CommandProcessor::operator =(const CommandProcessor& other) {
	for (auto p : other.commandVector) {
		Command* temp = new Command(*p);
		commandVector.push_back(temp);
	}
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const CommandProcessor& cp) {
	for (Command* c : cp.commandVector) {
		out << "Command is " << c->returnCommand() << endl;
		out << "Effect is " << c->returnEffect() << endl;
	}		
	return out;
}

//The protected CommandProcessor::readCommand() method reads a string from the console. 
string CommandProcessor::readCommand(void) {
	string input;
	// get the whole line from user's input
	getline(cin, input); 	
	return input;
}

//The protected CommandProcessor::saveCommand() method saves the command in the list of commands.
Command* CommandProcessor::saveCommand(string command) {
	Command* temp = new Command(command);
	commandVector.push_back(temp);
	Notify();
	return temp;
}

// The public CommandProcessor::getCommand() method can be used by the GameEngine to read and save a command when needed.
Command* CommandProcessor::getCommand(void)
{
	string input = readCommand();
	Command* temp = saveCommand(input);
	return temp;
}

//The CommandProcessor::validate() command can be used to validate if a given command is valid in the current game state.
bool CommandProcessor::validate(string input, string currentState) {

	const string commandArr[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };

	bool isThere = false;

	for (string anyCommand : commandArr) {
		if (input == anyCommand)
			isThere = true;
	}

	if (!isThere) {
		cout << "This command is not valid in Warzone!" << endl;
		return false;
	}
	else {
		if (input == "loadmap") {
			if (currentState == "start" || currentState == "maploaded") {
				return true;
			}
		}
		else if (input == "validatemap") {
			if (currentState == "maploaded") {
				return true;
			}
		}
		else if (input == "addplayer") {
			if (currentState == "mapvalidated" || currentState == "playersadded") {
				return true;
			}
		}
		else if (input == "gamestart") {
			if (currentState == "playersadded" || currentState == "gamestart") {
				return true;
			}
		}
		else if (input == "replay") {
			if (currentState == "win") {
				return true;
			}
		}
		else if (input == "quit") {
			if (currentState == "win") {
				return true;
			}
		}
	}

	cout << "It is a game command, but not valid in the current state" << endl;
	return false;
}

// redefine the virtual method inherited from Subject class
string CommandProcessor::stringToLog() {
	return "Inputted command: " + commandVector.back()->returnCommand();
}

// -----------------------------------FileLineReader class ----------------------------------------

//Constructor
FileLineReader::FileLineReader() {
	fileName = "Default";
}

FileLineReader::FileLineReader(string fileName) {
	this->fileName = fileName;
}

FileLineReader::FileLineReader(const FileLineReader& other) {
	fileName = other.fileName;
}

//Destructor
FileLineReader::~FileLineReader(void) {
	cout << "Destroying FileLineReader." << endl;
}

//Assignment operator
FileLineReader& FileLineReader::operator =(const FileLineReader& other) {
	fileName = other.fileName;
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const FileLineReader& f) {
	out << f.fileName << endl;
	return out;
}

// This method reads a file line by line
string FileLineReader::readLineFromFile(void) {

	ifstream input{};
	input.open(fileName);

	// check if the file is empty
	if (input.peek() == std::ifstream::traits_type::eof()) {
		cout << "The command file is empty!" << endl;
		exit(0);
	}
	string current;

	// get the first line of the file
	getline(input, current);
	input.close();

	// remove the first line from the file
	int count = 0;
	string line;
	ifstream inFile(fileName);
	ofstream outFile("removedfirstline.txt");
	while (getline(inFile, line)) {
		count++;
		if (count != 1) {
			outFile << line << "\n";
		}
	}
	inFile.close();
	outFile.close();

	// delete the original file
	remove("copy.txt");
	// change the file name of removeline.txt to copy.txt
	rename("removedfirstline.txt", "copy.txt");

	return(current);
}

// -----------------------------------FileCommandProcessorAdapter class ----------------------------------------

// Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
	fprocessor = new FileLineReader(); 
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* processor) {
	fprocessor = processor;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other): CommandProcessor(other) {
	this->fprocessor = new FileLineReader(*other.fprocessor);
}

//Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	cout << "Destroying FileCommandProcessorAdapter." << endl;
	delete fprocessor;
	fprocessor = nullptr;
}

//Assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator =(const FileCommandProcessorAdapter& other) {
	CommandProcessor::operator = (other);
	this->fprocessor = new FileLineReader(*other.fprocessor);
	return *this;
}

//Stream insertion:
ostream& operator << (ostream& out, const FileCommandProcessorAdapter& fp) {
	out << fp.fprocessor << endl;
	return out;
}

// this class is inherited from CommandProcessor, so it can overwrite the getCommand() and change the input source from console to file
Command* FileCommandProcessorAdapter::getCommand() {
	// use adaptee object to read commands from a file
	string input = fprocessor->readLineFromFile();
	Command* temp = CommandProcessor::saveCommand(input);
	return temp;
}

