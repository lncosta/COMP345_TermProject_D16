#include <iostream>
#include "GameEngine.h"

using namespace std;


GameEngine::GameEngine() 
{
	state = "Start";
}

GameEngine:: GameEngine(const GameEngine& other) 
{
	state = other.state;
}

void GameEngine::setState(string newState) 
{
	state = newState;
}

string GameEngine::getState() 
{
	return state;
}

GameEngine& GameEngine::operator =(const GameEngine& other) {
	state = other.state;
	return *this;
}

istream& operator>>(istream& in, GameEngine& g)
{
	in >> g.state;
	return in;
}

ostream& operator<<(ostream& out, const GameEngine& g)
{
	out << g.state << endl;
	return out;
}


int GameEngine::menu(int i) 
{
	string input;
	switch (i) {
	case 0:
		cout << "Welcome to Warzone! Enter \"loadmap\" to load your map " << endl;
		cin >> input;
		if (input == "loadmap") {
			setState("Map Loaded");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 1:
		cout << "Enter \"loadmap\" or Enter \"validatemap\" " << endl;
		cin >> input;
		if (input == "loadmap") {
			cout << "[STATE] - " << getState() << endl << endl;
			return i;
		}
		else if (input == "validatemap") {
			setState("Map Validated");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 2:
		cout << "Enter \"addplayer\" to add a player" << endl;
		cin >> input;
		if (input == "addplayer") {
			setState("Players Added");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 3:
		cout << "Enter \"addplayer\" or \"assigncountries\" " << endl;
		cin >> input;
		if (input == "addplayer") {
			cout << "[STATE] - " << getState() << endl << endl;
			return i;
		}
		else if (input == "assigncountries") {
			setState("Assign Reinforcement");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 4:
		cout << "Enter \"issueorder\" " << endl;
		cin >> input;
		if (input == "issueorder") {
			setState("Issue Orders");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 5:
		cout << "Enter \"issueorder\" or \"endissueorders\" " << endl;
		cin >> input;
		if (input == "issueorder") {
			cout << "[STATE] - " << getState() << endl << endl;
			return i;
		}
		else if (input == "endissueorders") {
			setState("Execute Orders");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 6:
		cout << "Enter \"execorder\" or \"endexecorders\" or \" \"win\" " << endl;
		cin >> input;
		if (input == "execorder") {
			cout << "[STATE] - " << getState() << endl << endl;
			return i;
		}
		else if (input == "endexecorders") {
			setState("Assign Reinforcement");
			cout << "[STATE] - " << getState() << endl << endl;
			return 4;
		}
		else if (input == "win") {
			setState("Win");
			cout << "[STATE] - " << getState() << endl << endl;
			return ++i;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;

	case 7:
		cout << "Enter \"play\" or \"end\" " << endl;
		cin >> input;
		if (input == "play") {
			setState("Start");
			cout << "[STATE] - " << getState() << endl << endl;
			return (i = 0);
		}
		else if (input == "end") {
			setState("End");
			cout << "[STATE] - " << getState() << endl << endl;
			return -1;
		}
		else {
			cout << "---Invalid command" << endl << endl;
			return i;
		}
		break;
	}
}

