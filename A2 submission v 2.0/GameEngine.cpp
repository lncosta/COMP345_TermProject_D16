#include <iostream>
#include <algorithm>
#include <random>
#include "GameEngine.h"

using namespace std;


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

GameEngine::~GameEngine(void)
{
	cout << "Destroying Game Engine" << endl;
	if (neutral != NULL) {
		delete neutral;
		neutral = NULL;
	}
	if (map != NULL) {
		delete map;
		map = NULL;
	}
	if (deck != NULL) {
		delete deck;
		deck = NULL;
	}
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
	return "Transitioned to state: " + state;
}

//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// seperate the input to argument[0](the command) and argument[1](the parameter)
vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

void GameEngine::startupPhase()
{
	string source;
	string currentState;
	Command* c{};
	LogObserver* processorObserver{};
	LogObserver* commandObserver;
	bool isValid;

	// create pointers of target, adaptee and adapter
	CommandProcessor* processor{};
	FileLineReader* fprocessor{};
	FileCommandProcessorAdapter* adapter{};

	// Process user's input to extract the source (console or file wtih fileName) 
	do {


		cout << "Please enter -console or -file <filename> to choose the input source." << endl;
		cin >> source;

		if (source == "console") {
			processor = new CommandProcessor();
			processorObserver = new LogObserver(processor);
		}
		else if (source == "file") {
			string fileName;
			cin >> fileName;
			// copy the source file so that we can delete the top line after reading it
			ifstream inFile(fileName);
			ofstream outFile("copy.txt");
			outFile << inFile.rdbuf();
			inFile.close();
			outFile.close();
			fprocessor = new FileLineReader("copy.txt"); // adaptee
			adapter = new FileCommandProcessorAdapter(fprocessor);// adapter (inherited from target)
			processorObserver = new LogObserver(adapter);
		}

	} while (source != "console" && source != "file");

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;

		string s;


		// depends on user's choice, command is read from commandProcessor object or Adapter object
		// commands can be read from the console using the CommandProcessor class. 
		if (source == "console") {
			string str;
			cout << "Enter your command" << endl;
			c = processor->getCommand();
			s = c->returnCommand();


		}
		else if (source == "file") {
			string str;
			c = adapter->getCommand(); // call readLineFromfile()
			s = c->returnCommand();
			cout << "-----------------The input from the file is------------------ " << s << endl;

		}

		commandObserver = new LogObserver(c);

		// if an input has a parameter, split the parameter from the command itself
		vector<string> v = split(s, " ");
		string input = v[0];
		string parameter = "";
		if (v.size() == 2)
			parameter = v[1];


		isValid = processor->validate(input, currentState);

		if (!isValid) {
			continue;

		}
		else
		{
			if (input == "loadmap") {
				bool res = loadMap(parameter);
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
				if (source == "console") {
					if (parameter == "") {
						cout << "Please add the player's name after the space" << endl;
						continue;
					}
					playerName = parameter;
				}
				else if (source == "file") {

					playerName = parameter;
				}


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
					if (source == "console")
						cout << "There are not enough players in the game to start yet." << endl;
					else if (source == "file") {
						cout << "There are not enough players in the game to start yet." << endl;
						cout << "Please modify your file to provide enough players." << endl;
						exit(0);

					}

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

	delete processorObserver;
	processorObserver = nullptr;

}

void GameEngine::removePlayer(Player* toRemove) {
	players.erase(remove(players.begin(), players.end(), toRemove), players.end());
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
			cout << "Player " << winningPlayers[0]->getName() << " has won!" << endl;
			winningCondition = true;
		}
		else if (players.size() <= 1) {
			cout << "Player " << players[0]->getName() << " has won!" << endl;
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
					removePlayer(p);
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
			p->issueOrder();
			string orderIssued = (p->getOrders())->getOrderList().back()->getName();
			cout << "Would you like to issue more orders? Y/N" << endl;
			if (!p->intelligent && p->getOrders()->getOrderList().size() < 5) {
				result = "Y";
			}
			else if (!p->intelligent) {
				result = "N";
			}
			else {
				cin >> result;
			}

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
				if (p->getConquered() == true) {
					deck->draw(p);
					p->setConquered(false);
				}
				doneCount++;
			}
		}
		if (doneCount >= players.size()) {
			playing = false;
		}
	}


}

bool GameEngine::loadMap(string fileName) {
	int numberOfMaps = -1;
	MapLoader load;
	Map* created = nullptr;
	vector<Map*> mapsCreated;

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
	//Shuffle the vector before assigning territories:
	string result;
	bool intl = false;
	vector<Territory*> copy = map->getTerritoyVector();
	random_shuffle(copy.begin(), copy.end());
	//Determine whether user input will be used:
	cout << "Would you like to use console input to play the game? Y/N" << endl;
	cin >> result;
	while (result != "N" && result != "n" && result != "y" && result != "Y") {
		cin >> result;
	}
	if (result == "Y" || result == "y") {
		intl = true;
	}
	//Create neutral player:
	neutral = new Player();
	neutral->setName("Neutral");
	//Print out players:
	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << endl;
		if (intl) { //Sets intelligence modifier for all players (demo purposes):
			p->intelligent = true;
		}
		//Associate the neutral player with all players:
		p->neutral = neutral;
		//Associate Map with players:
		p->map = map;
	}


	//Assign territories:
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
		//For demo purposes, add a card of each type to the player:
		int counter = 0;
		for (int types = 0; types < 5; types++) {
			for (int cards = 0; cards < (1 * 5); cards++) { // creates 3 cards (1 card for the demo only) per player per type of card
				counter++; // the first card has ID == 1

				Card* pointer = new Card(types, counter);
				p->addCard(pointer);
			}
		}
		cout << "Player " << p->getName() + " has received the following cards: " << endl;
		for (auto c : p->getHandOfCards()) {
			cout << *c;
		}
	}



	//Enter play phase.
	return true;
}




