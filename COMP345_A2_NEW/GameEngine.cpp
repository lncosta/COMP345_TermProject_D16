
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
	Notify();
	return temp;
}

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
	cout << "CommandProcessor will write to file gamelog.txt here" << endl;
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
		theEffect = "Player(s) has been added.";
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
	cout << "Command will write to file gamelog.txt here" << endl;
	return "Current effect: " + effect;
}

// -----------------------------------GameEngine class ----------------------------------------


void GameEngine::transition(string newState) {


	this->setState(newState);

	cout << "You are transited to state: " << this->getState() << endl;
	Notify();
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
	out << "The current State is [ " << g.state << " ]" << endl;
	return out;
}

string GameEngine::stringToLog() {
	//cout << "GameEngine will write to file gamelog.txt here" << endl;
	return "Transitioned to state: " + state;
}

int GameEngine::menu(int i)
{

	string currentState;
	CommandProcessor* processor = new CommandProcessor();
	LogObserver* processorObserver = new LogObserver(processor);
	LogObserver* commandObserver;

	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;
		cout << "Enter your command" << endl;
		Command* c = processor->getCommand(); // will use it for save effect
		string input = c->returnCommand();


		commandObserver = new LogObserver(c);

		bool isValid = processor->validate(input, currentState);

		if (!isValid) {
			continue;
		}
		else
		{
			if (input == "loadmap") {
				bool res = loadMap();
				if (res) {
					c->saveEffect(input);
					transition("maploaded");
				}
				else {
					transition("start");
				}
				
			}
			else if (input == "validatemap") {
				map->validateWrapper();

				if (map->getValidity()) {
					c->saveEffect(input);
					transition("mapvalidated");
				}

				else
					transition("start");

			}
			else if (input == "addplayer") {
				
				string playerName;
				cin >> playerName;
				addPlayer(playerName);
				c->saveEffect(input);
				if (players.size() >= 6) {
					cout << "Player limit has been reached. Game will now start." << endl;
					c->saveEffect("gamestart");
					transition("gamestart");
				}
				else {
					transition("playersadded");
				}
				
			}
			else if (input == "gamestart") {
				if (players.size() > 1) {
					assignTerritories();
					c->saveEffect(input);
					transition("assignreinforcement");
					mainGameLoop();
				}
				else {
					cout << "There are not enough players in the game to start yet." << endl;
				}
				
			}
			else if (input == "replay") {
				players.clear();
				delete map;
				c->saveEffect(input);
				transition("start");
			}
			else if (input == "quit") {
				c->saveEffect(input);
				transition("exitprogram");
			}

		}
		delete commandObserver;
		commandObserver = nullptr;
	}

	cout << "-----------------------------";
	for (Command* c : processor->getCommandVector()) {
		cout << c->returnCommand();
		cout << " : " << c->returnEffect() << endl;
	}

	delete processorObserver;
	processorObserver = nullptr;

	return -1;
}


int GameEngine::mainGameLoop(void)

{
	bool loopstop = false;
	// winningCondition needs to be implemented. Set it as false to test executeOrderPhase()
	bool winningCondition = false;



	while (!loopstop) {

		cout << *this << endl;

		//Check for winning condition:
		vector<Player*> winningPlayers;
		for (auto t : map->getTerritoyVector()) {
			if (find(winningPlayers.begin(), winningPlayers.end(), t->getOwner()) == winningPlayers.end()) {
				winningPlayers.push_back(t->getOwner());
			}
		}
		if (winningPlayers.size() <= 1) {
			winningCondition = true;
		}
		else {
			winningCondition = false;
			cout << "No player has yet won. The game continues." << endl;
			int i = 0;
			for (auto p : players) {
				if (find(winningPlayers.begin(), winningPlayers.end(), p) == winningPlayers.end()) {
					//One of the players does not own any territories.
					cout << "Player " << p->getName() << " does not own any territories and thus must be removed from the game." << endl;
					players.erase(players.begin() + i);
				}
				i++;
			}
		}

		if (winningCondition) {
			transition("win");
			loopstop = true;

		}

		if (state == "assignreinforcement") {
			reinforcementPhase();
			transition("issueorders");
		}
		else if (state == "issueorders") {
			issueOrdersPhase();
			transition("executeorders");

		}
		else if (state == "executeorders") {

			if (winningCondition) {
				transition("win");
				loopstop = true;

			}
			else {
				executeOrdersPhase();
				transition("assignreinforcement");
			}

		}

	}
	return 0;

}


void GameEngine::addPlayer(string name) {

	//Creating Player Objects:

	Player* temp = new Player();
	temp->setName(name);
	cout << "Welcome to Warzone, " << name << "!" << endl;
	players.push_back(temp);



}



void GameEngine::addPlayer(void) {
	int n = 0;
	cout << "This is the Player creation menu." << endl;
	while (n < 2 || n > 6) {
		cout << "Please enter the number of desired players. " << endl;
		cout << "The number should be between 2 and 6." << endl;
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
void GameEngine::issueOrdersPhase(void) {
	//Issuing orders in round-robin fashion:
	bool round = true;
	string result;
	for (auto p : players) {
		cout << "Player - " << p->getName() << endl;
		round = true;
		while (round) {
			if (p->getPlayerHand()->getHandOfCards().size() < 1 && p->getArmiesHeld() < 1) {
				cout << "The player does not own any armies and has an empty hand of cards. Player may not issue any orders." << endl;
				round = false;
				break;
			}
			p->issueOrder();
			string orderIssued = (p->getOrders())->getOrderList().back()->getName();
			cout << "Would you like to issue more orders? Y/N" << endl;
			cin >> result;
			while (result != "N" && result != "n" && result != "y" && result != "Y") {
				cin >> result;
			}
			if (result == "N" || result == "n") {
				round = false;
			}
		}
		cout << "The final list of orders is: " << endl;
		cout << *(p->getOrders()) << endl;
	}

}
void GameEngine::executeOrdersPhase(void) {
	bool playing = true;
	int doneCount = 0;
	while (playing) {
		LogObserver* orderObserver;
		//First execute deploy orders:
		for (auto p : players) {
			OrdersList* toDeleteFrom = p->getOrders();
			vector<Order*> toexc = toDeleteFrom->getOrderList();
			for (auto o : toexc) {
				if (o->getOrderType() == OrderType::Deploy) { //Execute all deploy orders first.
					orderObserver = new LogObserver(o);

					o->execute();

					delete orderObserver; //delete the observer before deleting the order
					orderObserver = nullptr; //if we used smart pointers we wouldn't have to do this deletion here

					toDeleteFrom->remove(0);
				}
			}

		}
		//Then, execute regular orders:
		for (auto p : players) {
			vector<Order*> toexc = p->getOrders()->getOrderList();
			int terrOwned = p->getTowned().size();
			if (toexc.size() > 0) {
				orderObserver = new LogObserver(toexc[0]);

				toexc[0]->execute();

				delete orderObserver; //delete the observer before deleting the order
				orderObserver = nullptr; //if we used smart pointers we wouldn't have to do this deletion here
				//Remove executed order:
				OrdersList* toDeleteFrom = p->getOrders();
				toDeleteFrom->remove(0);
			}
			else {
				int newTerritorySize = p->getTowned().size();
				if (newTerritorySize > terrOwned) {
					deck->draw(p);
				}
				doneCount++;
			}
		}
		if (doneCount >= players.size()) {
			playing = false;
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
	//Shuffle the vector before assigning. Solution from https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
	vector<Territory*> copy = map->getTerritoyVector();
	auto rng = std::default_random_engine{};
	std::shuffle(begin(copy), end(copy), rng);

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << endl;
	}

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

	//Shuffle players to determine play order:
	random_shuffle(players.begin(), players.end());

	//Create Deck object:

	deck = new Deck();
	//Add initial army value and draw cards:
	for (auto p : players) {
		p->getPlayerHand()->setDeck(deck);
		p->setArmiesHeld(50);
		deck->draw(p);
		deck->draw(p);
		cout << "Player " << p->getName() + " has received the following cards: " << endl;
		for (auto c : p->getHandOfCards()) {
			cout << *c;
		}
	}

	//Enter play phase.
	return true;
}
