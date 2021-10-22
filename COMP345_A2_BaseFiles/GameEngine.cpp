#include "GameEngine.h"

using namespace std;

// -----------------------------------CommandProcessor class ----------------------------------------

string CommandProcessor::readCommand(void) {	
	string input;
	cin >> input; 	
	return input;
}

Command* CommandProcessor::saveCommand(string command) {
	Command* temp = new Command(command);
	commandVector.push_back(temp);
	return temp;
}

Command* CommandProcessor::getCommand(void) 
{
	string input = readCommand();
	Command* temp = saveCommand(input);
	return temp;
}


bool CommandProcessor::validate(Command* cd, GameEngine* engine) {

	string input = cd->returnCommand();
	GameEngine* ge = engine;
	string currentState = ge->getState();

	bool isThere = false;

	for (string anyCommand : ge->commandArr) {
		if (input == anyCommand)
			isThere = true;
	}

	if (!isThere) {
		cout << "This command is not valid in Warzone!" << endl;
		return false;
	}
	else {
		if (input == ge->commandArr[0]) { // loadmap
			if (currentState == ge->stateArr[0] || currentState == ge->stateArr[1]) { // start , maploaded
				ge->transition(1); // maploaded
				return true;
			}			
		}
		else if (input == ge->commandArr[1]) { // validatemap
			if (currentState == ge->stateArr[1]) { // maploaded
				ge->transition(2); // mapvalidated
				return true;
			}			
		}
		else if (input == ge->commandArr[2]) { // addplayer
			if (currentState == ge->stateArr[2] || currentState == ge->stateArr[3]) { // mapvalidated, playersadded
				ge->transition(3); // playersadded
				
				return true;
			}			
		}
		else if (input == ge->commandArr[3]) { // gamestart
			if (currentState == ge->stateArr[3]) {  // playersadded
				ge->transition(4); // assignreinforcement
				return true;
			}			
		}
		else if (input == ge->commandArr[4]) { // replay
			if (currentState == ge->stateArr[7]) { //win
				ge->transition(0); // start
				return true;
			}			
		}
		else if (input == ge->commandArr[5]) { // quit
			if (currentState == ge->stateArr[7]) { // win
				ge->transition(8); // exitprogram
				return true;
			}			
		}
	}

		cout << "It is a game command,but not valid in the current state" << endl;
	

	delete ge;
	ge = NULL;
	
	return false;
}





// -----------------------------------Command class ----------------------------------------
Command::Command(string input) {
	this->command = input;
}

string Command::returnCommand(void) {
	return command;
}


// -----------------------------------GameEngine class ----------------------------------------

void GameEngine::transition(int index) {

	string newState = this->stateArr[index];
	this->setState(newState);

	cout << "The command entered was valid. You are transited to state: " << this->getState() << endl;

}
	

GameEngine::GameEngine() 
{

	state = "start";
	//cp = new CommandProcessor;
}

GameEngine:: GameEngine(const GameEngine& other) 
{
	state = other.state;
}

void GameEngine::setState(string newState) 
{
	state = newState;
}


string GameEngine::getState(void)
{
	return state;
}


GameEngine& GameEngine::operator =(const GameEngine& other) 
{
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

//
//int GameEngine::menu(int i) 
//{
//	CommandProcessor processor;
//	
//	switch (i) {
//	case 0:
//		cout << "Welcome to Warzone! Enter \"loadmap\" to load your map " << endl;
//		
//		processor.getCommand();
//		/*if (input == "loadmap") {
//			setState("Map Loaded");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/		
//		break;
//
//	case 1:
//		cout << "Enter \"loadmap\" or Enter \"validatemap\" " << endl;
//		/*cin >> input;
//		if (input == "loadmap") {
//			cout << "[STATE] - " << getState() << endl << endl;
//			return i;
//		}
//		else if (input == "validatemap") {
//			setState("Map Validated");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 2:
//		cout << "Enter \"addplayer\" to add a player" << endl;
//		/*cin >> input;
//		if (input == "addplayer") {
//			setState("Players Added");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 3:
//		cout << "Enter \"addplayer\" or \"assigncountries\" " << endl;
//		/*cin >> input;
//		if (input == "addplayer") {
//			cout << "[STATE] - " << getState() << endl << endl;
//			return i;
//		}
//		else if (input == "assigncountries") {
//			setState("Assign Reinforcement");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 4:
//		cout << "Enter \"issueorder\" " << endl;
//		/*cin >> input;
//		if (input == "issueorder") {
//			setState("Issue Orders");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 5:
//		cout << "Enter \"issueorder\" or \"endissueorders\" " << endl;
//		/*cin >> input;
//		if (input == "issueorder") {
//			cout << "[STATE] - " << getState() << endl << endl;
//			return i;
//		}
//		else if (input == "endissueorders") {
//			setState("Execute Orders");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 6:
//		cout << "Enter \"execorder\" or \"endexecorders\" or \" \"win\" " << endl;
//		/*cin >> input;
//		if (input == "execorder") {
//			cout << "[STATE] - " << getState() << endl << endl;
//			return i;
//		}
//		else if (input == "endexecorders") {
//			setState("Assign Reinforcement");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return 4;
//		}
//		else if (input == "win") {
//			setState("Win");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return ++i;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//
//	case 7:
//		cout << "Enter \"play\" or \"end\" " << endl;
//		/*cin >> input;
//		if (input == "play") {
//			setState("Start");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return (i = 0);
//		}
//		else if (input == "end") {
//			setState("End");
//			cout << "[STATE] - " << getState() << endl << endl;
//			return -1;
//		}
//		else {
//			cout << "---Invalid command" << endl << endl;
//			return i;
//		}*/
//		break;
//	}
//	return 0;
//}

