#pragma once
#include "CommandProcessing.h"
#include <limits>
using namespace std;

// -----------------------------------FileLineReader class ----------------------------------------
FileLineReader::FileLineReader() {
	fileName = "not defined";
}
FileLineReader::FileLineReader(string fileName) {
	this->fileName = fileName;
}

// This method reads a file line by line
string FileLineReader::readLineFromFile(void) {
	ifstream input;
	input.open(fileName);
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

FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
	*fprocessor = FileLineReader(); // stack object
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* processor) {
	fprocessor = processor;
}

// this class is inherited from CommandProcessor, so it can overwrite the getCommand() and change the source to file
Command* FileCommandProcessorAdapter::getCommand() {
	// use adaptee object to read commands from a file
	string input = fprocessor->readLineFromFile();
	Command* temp = CommandProcessor::saveCommand(input);
	return temp;

}


// -----------------------------------CommandProcessor class ----------------------------------------


string CommandProcessor::readCommand(void) {
	string input;	
	getline(cin, input); // get the whole line from user's input	
	return input;
	
}

Command* CommandProcessor::saveCommand(string command) {
	Command* temp = new Command(command);
	commandVector.push_back(temp);
	Notify();
	return temp;
}

//can be used by the GameEngine to read and save a command when needed
Command* CommandProcessor::getCommand(void)
{
	string input = readCommand();
	Command* temp = saveCommand(input);
	return temp;
}


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


vector<Command*>CommandProcessor::getCommandVector() {
	return commandVector;
};

string CommandProcessor::stringToLog() {
	return "Inputted command: " + commandVector.back()->returnCommand();
}

// -----------------------------------Command class ----------------------------------------
Command::Command(string input) {
	this->command = input;
}

string Command::returnCommand(void) {
	return command;
}

string Command::returnEffect(void) {
	return effect;
}

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

string Command::stringToLog() {
	return "Current effect: " + effect;
}

