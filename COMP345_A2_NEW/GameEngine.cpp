#include <iostream>
#include <algorithm>
#include <random>
#include "GameEngine.h"



using namespace std;

// need to fix the invalid file input issues 
// 
// -----------------------------------GameEngine class ----------------------------------------


void GameEngine::transition(string newState) {

	
	setState(newState);

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
	out << "The current State is [ " << g.state << " ]" << endl;
	return out;
}

// solution found on https://www.techiedelight.com/split-string-cpp-using-delimiter/
void split(std::string const& str, const char delim,
	std::vector<std::string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}


int GameEngine::menu(int i)  // client
{
	string source;
	string currentState;
	Command* c = new Command();

	// create pointers of target, adaptee and adapter
	CommandProcessor* processor {};
	FileLineReader* fprocessor {};
	FileCommandProcessorAdapter* adapter {};


	// Process user's input to extract the source (console or file wtih fileName) 
	do {
		string s;		
		char delim = '-';
		vector<string> contents;

		cout << "Please enter -console or -file <filename> to choose the input source." << endl;
		cin >> s;

		split(s, delim, contents);

		for (auto& i : contents) {
			source.append(i);
		}

		// create objects based on user's choice
		if (source == "console") {
			processor = new CommandProcessor(); // target 
		}
						
		else if (source == "file") {  
			string fileName;
			cout << "Enter a file name for loading the commands" << endl;
			cin >> fileName;			
			// copy the source file so that we can delete the top line after reading it
			ifstream inFile(fileName);
			ofstream outFile("copy.txt");
			outFile << inFile.rdbuf();
			inFile.close();
			outFile.close();
			fprocessor = new FileLineReader("copy.txt"); // adaptee
			adapter = new FileCommandProcessorAdapter(fprocessor);// adapter (inherited from target)
		}		
		
	} while (source != "console" && source != "file");
	
	

	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;
		
		string input;
		// depends on user's choice, command is read from commandProcessor object or Adapter object
		if (source == "console") {
			cout << "Enter your command" << endl;
			c = processor->getCommand();
			input = c->returnCommand();

		}
		else if (source == "file") {
			c = adapter->getCommand(); // call readLineFromfile()
			input = c->returnCommand();
			cout << "-----------------The input from the file is------------------ " << input << endl;
			
		}
		
		// validate command string	
		bool isValid = processor->validate(input, currentState);

		if (!isValid) {
			continue;
		}
		else 
		{
			if (input == "loadmap") {
				bool res = loadMap();
				if (!res) {
					continue;
				}
				c->saveEffect(input);
				transition("maploaded");
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
				addPlayer();
				c->saveEffect(input);
				transition("playersadded");
			}
			else if (input == "gamestart") {
				assignTerritories();
				c->saveEffect(input);
				transition("assignreinforcement");
				mainGameLoop();
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
	}

	if (source == "console") {
		cout << "-----------for command array testing------------------" << endl;
		for (Command* c : processor->getCommandVector()) {
			cout << c->returnCommand();
			cout << " : " << c->returnEffect() << endl;
		}

	}
	else if (source == "file") {
		cout << "-----------for command array testing------------------" << endl;
		for (Command* c : adapter->getCommandVector()) {
			cout << c->returnCommand();
			cout << " : " << c->returnEffect() << endl;
		}

	}
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

/*
void GameEngine::addPlayer(string name) {

    //Creating Player Objects:

Player* temp = new Player();
(temp).setName(name);
cout << "Welcome to Warzone, " << name << "!" << endl;
players.push_back(temp);


cout << "All players have been added! Here is who will be playing:" << endl;
for (Player p : players) {
	cout << "Player " << (p).getPlayerID() << " - " << (p).getName() << endl;
}
}

*/

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
void GameEngine::issueOrdersPhase(void) {
	//Issuing orders in round-robin fashion:
	bool round = true;
	string result;
	for (auto p : players) {
		cout << "Player - " << p->getName() << endl;
		round = true;
		while (round) {
			p->issueOrder();
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
		cout << *( p->getOrders()) << endl;
	}

}
void GameEngine::executeOrdersPhase(void) {
	bool playing = true;
	int doneCount = 0;
	while (playing) {
		//First execute deploy orders:
		for (auto p : players) {
			OrdersList* toDeleteFrom = p->getOrders();
			vector<Order*> toexc = toDeleteFrom->getOrderList();
			int i = 0;
			for (auto o : toexc) {
				if (o->getOrderType() == OrderType::Deploy) { //Execute all deploy orders first.
					o->execute(); 
					toDeleteFrom->remove(i); 
				}
				i++;
			}
			
		}
		//Then, execute regular orders:
		for (auto p : players) {
			vector<Order*> toexc = p->getOrders()->getOrderList();
			if (toexc.size() > 0) {
				toexc[0]->execute();
				//Remove executed order:
				OrdersList* toDeleteFrom = p->getOrders(); 
				toDeleteFrom->remove(0); 
			}
			else {
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
	shuffle(begin(players), end(players), rng);

	//Create Deck object:
	
	 deck = new Deck();
	//Add initial army value and draw cards:
	for (auto p : players) {

		p->setArmiesHeld(50);
		deck->draw(p);
		deck->draw(p);
		cout << "Player "<< p->getName() + " has received the following cards: " << endl;
		for (auto c : p->getHandOfCards()) {
			cout << *c;
		}
	}

	//Enter play phase.
	return true;
}







