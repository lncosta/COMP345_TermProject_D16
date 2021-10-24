#include <iostream>
#include <algorithm>
#include <random>
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
				return true;
			}
		}
		else if (input == ge->commandArr[1]) { // validatemap
			if (currentState == ge->stateArr[1]) { // maploaded
				return true;
			}
		}
		else if (input == ge->commandArr[2]) { // addplayer
			if (currentState == ge->stateArr[2] || currentState == ge->stateArr[3]) { // mapvalidated, playersadded
				return true;
			}
		}
		else if (input == ge->commandArr[3]) { // gamestart
			if (currentState == ge->stateArr[3]) {  // playersadded
				return true;
			}
		}
		else if (input == ge->commandArr[4]) { // replay
			if (currentState == ge->stateArr[7]) { //win
				return true;
			}
		}
		else if (input == ge->commandArr[5]) { // quit
			if (currentState == ge->stateArr[7]) { // win
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

	cout << "You are transited to state: " << this->getState() << endl;

}


GameEngine::GameEngine()
{

	state = "start";

	
}

GameEngine::GameEngine(const GameEngine& other)
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




int GameEngine::menu(int i)
{
	CommandProcessor* processor = new CommandProcessor();
	Command* c; 
	string input; 
	bool isValid = false;
	int value = 0;
	
	

	while (i > -1) {
		
		switch (i) {
		case 0:  // current state: Start 
			players.clear();
			delete map;
			
			cout << "Enter \"loadmap\" to load your map " << endl;
		
			c = processor->getCommand();
			input = c->returnCommand();
			isValid = processor->validate(c, this);

			if (isValid) {
				bool res = loadMap();
				if (!res) {
					break;
				}
				this->transition(1);
				++i;
			}
			
			break;

		case 1: // current state: maploaded
			cout << "Enter \"loadmap\" or Enter \"validatemap\" " << endl;

			c = processor->getCommand();
			input = c->returnCommand();
			isValid = processor->validate(c, this);

			if (isValid) {
				if (input == "loadmap") {
					bool res = loadMap();
					if (!res) {
						break;
					}
				}
				else if (input == "validatemap") {
					// call validateMap method
					this->transition(2);
					++i;
				}
			}
			break;

		case 2: // current state: mapvalidated
			cout << "Enter \"addplayer\" to add a player" << endl;

			c = processor->getCommand();
			input = c->returnCommand();
			isValid = processor->validate(c, this);

			if (isValid) {
				addPlayer();
				this->transition(3);
				++i;
			}			
			break;

		case 3: // current state: playersadded
			cout << "Enter \"addplayer\" or \"gamestart\" " << endl;
			
			c = processor->getCommand();
			input = c->returnCommand();
			isValid = processor->validate(c, this);

			if (isValid) {
				if (input == "addplayer") {
					addPlayer();
				}
				else if (input == "gamestart") {
					assignTerritories();
					this->transition(4);					
					++i;					
				}
			}			
			break;			

			
		case 4: // current state: assignreinforcement (red command: issueorder)	
			mainGameLoop(); 
			i = 7;
			break;
		
		case 7: // current state: win
			
			cout << "Enter \"replay\" or \"quit\" " << endl;
			
			c = processor->getCommand();
			input = c->returnCommand();
			isValid = processor->validate(c, this);
			if (isValid) {
				if (input == "replay") {
					this->transition(0);					
					i = 0;
				}
				else if (input == "quit") {
					this->transition(8);
					i = -1;
					
				}
			}			
			break;
		}		
		
		cout << "The current State is [ " << this->getState() << " ]" << endl;
		
	}
	return -1;

}
void GameEngine::addPlayer(void) {
	int n = 0;
	//cout << "Welcome to Warzone!" << endl;
	cout << "This is the Player creation menu." << endl;
	while (n < 1) {
		cout << "Please enter the number of desired players. " << endl;
		cout << "The number should be greater than or equal to one." << endl;
		cin >> n;
	}

	//Creating Player Objects:
	for (int i = 0; i < n; i++)
	{
		Player* temp = new Player();
		string name;
		cout << "Player " << (i + 1) << " - Enter Player's name: " << endl;
		cin >> name;
		(*temp).setName(name);
		cout << "Welcome to Warzone, " << name << "!" << endl;
		players.push_back(temp);
	}

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << (*p).getPlayerID() << " - " << (*p).getName() << endl;
	}
}
void GameEngine::reinforcementPhase(void) {
	for (auto p : players) {
		int count = 0;
		for (auto o : p->getTowned()) {
			count++;
		}
		int toAdd = p->getArmiesHeld() + count / 3;

		p->setArmiesHeld(toAdd);

		//Cheking for player owning all continents:

		for (auto c : map->getContinentVector()) {
			int playerCount = 0;
			int territoryCount = 0;
			for (auto t : c->getSubGraph()) {
				territoryCount++;
				if (t->getOwner()->getPlayerID() == p->getPlayerID()) {

					playerCount++;
				}
			}
			if (territoryCount == playerCount) {
				cout << "Player " << p->getName() << " owns the entirety of " << c->name << " and gains a +" << c->armyValue << " bonus." << endl;
				toAdd += c->armyValue;
			}
		}
		if (toAdd < 3) {
			toAdd = 3;
		}
		p->setArmiesHeld(toAdd);
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << " has received " << toAdd << " armies." << endl;
		cout << "Current army count is: " << p->getArmiesHeld() << endl;
	}
}

void GameEngine::mainGameLoop(void)

{
	bool loopstop = false;
	bool winningCondition = true;

	// need a while loop to keep running inside the mainGameLoop
	while (!loopstop) {
		cout << "The current State is [ " << this->getState() << " ]" << endl;

		if (state == this->stateArr[4]) {
			reinforcementPhase();
			this->transition(5);
		}
		else if (state == this->stateArr[5]) {
			//issueOrdersPhase();
			this->transition(6);

		}
		else if (state == this->stateArr[6]) {
			
			if (winningCondition) {
				this->transition(7);
				loopstop = true;

			}
			else {
				//executeOrdersPhase()
				this->transition(4);
			}

		}

	}	
	
}


bool GameEngine::loadMap(void) {
	int numberOfMaps = -1;
	string fileName;
	MapLoader load;
	Map* created = nullptr;
	vector<Map*> mapsCreated;


	cout << "Enter the name of the Map file you would like to read. Do not forget to add the extension." << endl;
	cin >> fileName;
	try {
		created = load.loadMap(fileName);
		mapsCreated.push_back(created);
		int sum = 0;
		for (Territory* p : created->getTerritoyVector()) {
			sum++;
		}
		cout << "Territories placed: " << sum << endl;
		map = created;
		return true;
	}
	catch (const invalid_argument& e) {
		cout << "The map file provided was invalid. " << endl;
		return false;
	}
}
bool GameEngine::assignTerritories(void) {
	//Should probably shuffle the vector before assigning. Solution from https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
	vector<Territory*> copy = map->getTerritoyVector();
	auto rng = std::default_random_engine{};
	std::shuffle(begin(copy), end(copy), rng);


	int playerCount = players.size();
	int count = 0;
	int index = 0;
	for (auto t : copy) {
		index = count % playerCount;
		t->setOwner(players[index]);
		players[index]->addTerritory(t);
		cout << "Territory " << t->getTerritoryName() << " is now owned by " << t->getOwner()->getName() << endl;
		count++;
	}

	//Shuffle players:
	shuffle(begin(players), end(players), rng);

	//Add initial army value:
	for (auto p : players) {

		p->setArmiesHeld(50);
	}

	//Draw cards;

	//Enter play phase.
	return true;
}




