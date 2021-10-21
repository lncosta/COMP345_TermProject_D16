#include <iostream>
#include <algorithm>
#include <random>
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
	while (i > -1) {
		switch (i) {
		case 0:
			players.clear();
			delete map;

			cout << "Welcome to Warzone! Enter \"loadmap\" to load your map " << endl;
			cin >> input;
			if (input == "loadmap") {
				bool res = loadMap(); 
				if (!res) {
					break; 
				}
				setState("Map Loaded");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
			}
			break;

		case 1:
			cout << "Enter \"loadmap\" or Enter \"validatemap\" " << endl;
			cin >> input;
			if (input == "loadmap") {
				cout << "[STATE] - " << getState() << endl << endl;
			}
			else if (input == "validatemap") {
				setState("Map Validated");
				cout << "[STATE] - " << getState() << endl << endl;
				 ++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;

			}
			break;

		case 2:
			cout << "Enter \"addplayer\" to add a player" << endl;
			cin >> input;
			if (input == "addplayer") {
				addPlayer();
				setState("Players Added");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
			}
			break;

		case 3:
			cout << "Enter \"addplayer\" or \"assigncountries\" " << endl;
			cin >> input;
			if (input == "addplayer") {
				addPlayer();
				cout << "[STATE] - " << getState() << endl << endl;
			}
			else if (input == "assigncountries") {
				assignTerritories();
				setState("Assign Reinforcement");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
		
			}
			break;

		case 4:
			cout << "Enter \"issueorder\" " << endl;
			cin >> input;
			if (input == "issueorder") {
				setState("Issue Orders");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
	
			}
			break;

		case 5:
			cout << "Enter \"issueorder\" or \"endissueorders\" " << endl;
			cin >> input;
			if (input == "issueorder") {
				cout << "[STATE] - " << getState() << endl << endl;
			}
			else if (input == "endissueorders") {
				setState("Execute Orders");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
			}
			break;

		case 6:
			cout << "Enter \"execorder\" or \"endexecorders\" or \" \"win\" " << endl;
			cin >> input;
			if (input == "execorder") {
				cout << "[STATE] - " << getState() << endl << endl;
			}
			else if (input == "endexecorders") {
				setState("Assign Reinforcement");
				cout << "[STATE] - " << getState() << endl << endl;
				i = 4;
			}
			else if (input == "win") {
				setState("Win");
				cout << "[STATE] - " << getState() << endl << endl;
				++i;
			}
			else {
				cout << "---Invalid command" << endl << endl;
			
			}
			break;

		case 7:
			cout << "Enter \"play\" or \"end\" " << endl;
			cin >> input;
			if (input == "play") {
				setState("Start");
				cout << "[STATE] - " << getState() << endl << endl;
				i = 0;;
			}
			else if (input == "end") {
				setState("End");
				cout << "[STATE] - " << getState() << endl << endl;
				i =-1;
			}
			else {
				cout << "---Invalid command" << endl << endl;
			}
			break;
		}
		mainGameLoop(); 
	}
	return 0;
	
}
void GameEngine::addPlayer(void) {
	int n = 0; 
	cout << "Welcome to Warzone!" << endl;
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
		int toAdd = p->getArmiesHeld() + count/3;

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
	if (state == "Assign Reinforcement") { //Reinforcement
		reinforcementPhase(); 
	}
	else if (state == "Issue Orders") { //Issue Orders

	}
	else if (state == "Execute Orders") { //Execute Orders

	}
	else {

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
	return true; 
}
