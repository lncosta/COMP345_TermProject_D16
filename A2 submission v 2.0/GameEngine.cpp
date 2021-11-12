#include <iostream>
#include <algorithm>
#include <random>
#include "GameEngine.h"

using namespace std;

// Constructor
GameEngine::GameEngine(){
	state = "start";
}

GameEngine::GameEngine(const GameEngine& other){
	state = other.state;
}

// Destructor
GameEngine::~GameEngine(void){
	cout << "Destroying Game Engine" << endl;
	if (neutral != NULL) {
		delete neutral;
		neutral = NULL;
	}
	for (auto t : map->getTerritoyVector()) {
		delete t; 
	}
	if (map != NULL) {
		delete map;
		map = NULL;
	}
	if (deck != NULL) {
		delete deck;
		deck = NULL;
	}
	for (auto p : players) {
		delete p;
	}
}

// Getter and Setter
void GameEngine::setState(string newState){
	state = newState;
}

string GameEngine::getState(void){
	return state;
}

// Assignment operator
GameEngine& GameEngine::operator =(const GameEngine& other){
	state = other.state;
	return *this;
}

// Stream insertion
ostream& operator<<(ostream& out, const GameEngine& g){
	out << "The current State is [ " << g.state << " ]" << endl;
	return out;
}

// Method

// This free function split a string to several components according to the delimiter
//source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
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

// this method sets GameEngine object's state
void GameEngine::transition(string newState) {
	this->setState(newState);
	cout << "You are transited to state: " << this->getState() << endl;
	Notify(); //5.2.4 When the game engine state changes, the new state is written into the log file. 
}

// redefine the virtual method inherited from Subject class
string GameEngine::stringToLog() {
	return "Transitioned to state: " + state;
}

//This method implements the WarZone game flow, which includes a command-based user interaction mechanism 
// to proceed with the game startup phase
void GameEngine::startupPhase()
{
	string source;
	string currentState;
	Command* c{};
	LogObserver* processorObserver{};
	LogObserver* commandObserver{};
	bool isValid{};

	// create pointers of the target, adaptee and adapter
	CommandProcessor* processor{};
	FileLineReader* fprocessor{};
	FileCommandProcessorAdapter* adapter{};

	
	do {

		// 1.2.1 Upon starting the application, a command line option is set to either read commands from the console or from a given file.  
		cout << "Please enter -console or -file <filename> to choose the input source." << endl;
		cin >> source;		

		// 1.2.2 Commands can be read from the console 
		if (source == "console") {
			processor = new CommandProcessor();
			processorObserver = new LogObserver(processor);			
		}
		// 1.2.3 Commands can be read from a file
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

	// remove the "enter" from the cin buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	// The game will run until the game state transits to "exitprogram"
	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;
		string s;

		// 1.2.4 getCommand() reads commands and save commands in a list via commandProcessor object or Adapter object 
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

		//1.2.5 Commands are validated by the command processor
		isValid = processor->validate(input, currentState);

		if (!isValid) {
			//2.2.9 Invalid commands for the current state are rejected(no effect). 
			continue;
		}
		else
		{
			//2.2.1 In the start state, the loadmap command results in successfully loading a readable map, transitioning to the maploaded state
			if (input == "loadmap") {
				bool res = loadMap(parameter);
				if (res) {
					c->saveEffect(input);
					transition("maploaded");
				}
				
			}
			//2.2.2 In the maploaded state, the validatemap command is used to validate the map. 
			//If successful, the game transitions to the mapValidated state
			else if (input == "validatemap") {
				map->validateWrapper();

				if (map->getValidity()) {
					c->saveEffect(input);
					transition("mapvalidated");
				}
				else
					transition("start");
			}
			//2.2.3 In the mapValidated state, the addplayer command can be used to create new players and insert them in the game (2-6 players). 
			else if (input == "addplayer") {
				if (source == "console") {
					if (parameter == "") {
						cout << "Please add the player's name after the space." << endl;
						continue;
					}					
				}

				// check number of players, only 2-6 are allowed
				if (players.size() == 0) {
					//create new players and insert them in the game. 
					addPlayer(parameter);
					c->saveEffect(input);
					transition("playersadded");
				}
				
				else if (players.size() < 6) {
					addPlayer(parameter);
					c->saveEffect(input);
				}		
				else {
					cout << "Player limit has been reached. Please enter \"gamestart\"" << endl;
				}
			}
			else if (input == "gamestart") {
				if (players.size() > 1) {
					//assignTerritories() fulfill the following tasks:
					//2.2.4 fairly distributing the territories among all players
					//2.2.5 randomly determine the order of play of the players in the game
					//2.2.6 giving 50 initial armies to each player
					//2.2.7 Each player draws 2 cards each from the deck
					assignTerritories();
					c->saveEffect(input);
					transition("assignreinforcement");	
					//2.2.8 the gamestart command results transiting to the play phase
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

	if (source == "console") {
		delete processor;
		processor = nullptr;
	}
	else if (source == "file") {
		delete adapter;
		adapter = nullptr;	
	}
}

// This method removes players who do not own any territories and checks if there is a winner who controls all the territories
bool GameEngine::isThereAwinner() {
	cout << "Checking for a Winner." << endl; 
	vector<Player*> winningPlayers;
	// find those players who owns at least one territory and save them in the winningPlayers vector
	for (auto t : map->getTerritoyVector()) {
		if (find(winningPlayers.begin(), winningPlayers.end(), t->getOwner()) == winningPlayers.end() && t->getOwner()->getName() != "Neutral") {
			winningPlayers.push_back(t->getOwner());
		}
	}
	// if there is only one player in the the winningPlayers vector, that player is the winner
	if (winningPlayers.size() == 1) {
		cout << "Player " << winningPlayers[0]->getName() << " has won!" << endl;
		return true;
	}
	else if (winningPlayers.size() == 0) { //Handles the case where all available territories belong to the Neutral player
		cout << "The game has resulted in a tie. Better luck next time!" << endl; 
		return true; 
	}
	// if there is only one player in the the players vector because other players are removed from the game, that player is the winner
	else if (players.size() <= 1) {
		cout << "Player " << players[0]->getName() << " has won!" << endl;
		return true;
	}
	else {
		
		cout << "No player has yet won. The game continues." << endl;
		int i = 0;
		vector<Player*> copyP = players;
		for (auto p : copyP) {
			if (find(winningPlayers.begin(), winningPlayers.end(), p) == winningPlayers.end()) {
				//One of the players does not own any territories, and has to be removed from the players vector
				cout << "Player " << p->getName() << " does not own any territories and thus must be removed from the game." << endl;
				removePlayer(p);
			}
			i++;
		}
	}
	return false;
}

// This method does a simple check of whether any player has won
bool GameEngine::isThereAwinnerS(void) {
	vector<Player*> winningPlayers;
	// find those players who owns at least one territory and save them in the winningPlayers vector
	for (auto t : map->getTerritoyVector()) {
		if (find(winningPlayers.begin(), winningPlayers.end(), t->getOwner()) == winningPlayers.end() && t->getOwner()->getName() != "Neutral") {
			winningPlayers.push_back(t->getOwner());
		}
	}
	// if there is only one player in the the winningPlayers vector, that player is the winner
	if (winningPlayers.size() == 1) {
		return true;
	}
	else if (winningPlayers.size() == 0) { //Handles the case where all available territories belong to the Neutral player
		return true;
	}
	// if there is only one player in the the players vector because other players are removed from the game, that player is the winner
	else if (players.size() <= 1) {
		return true;
	}
	
	return false;
}


// The methods implemnts the play phase, where players can issue orders and the system executes orders 
int GameEngine::mainGameLoop(void)
{
	bool loopstop = false;

	while (!loopstop) {

		cout << *this << endl;


		if (state == "assignreinforcement") {
			if (isThereAwinner()) {
				transition("win");
				loopstop = true;
			}
			reinforcementPhase();
			transition("issueorders");
		}
		else if (state == "issueorders") {
			issueOrdersPhase();
			transition("executeorders");
		}
		else if (state == "executeorders") {

			//3.2.7 If during order execution one player controls all territories, the game goes to the win state
			if (isThereAwinner()) {
				transition("win");
				loopstop = true;
			}

			//3.2.6 Once all orders have been executed, the game engine goes back to the reinforcement phase.
			executeOrdersPhase();
			// check if ther is a winner, if yes, finish the mainGameLoop function, if not, back to assignreinforcement state.
			if (isThereAwinner()) {
				transition("win");
				loopstop = true;
			}
			else
				transition("assignreinforcement");
		}		
	}
	return 0;
}


// This methods takes a map's file name to create a Map object 
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

// This method removes a player from the game
void GameEngine::removePlayer(Player* toRemove) {
	players.erase(remove(players.begin(), players.end(), toRemove), players.end());
	delete toRemove;
}

// This method takes player's name as the parameter to create a player object 
void GameEngine::addPlayer(string name) {

	//Creating Player Objects:
	Player* temp = new Player();
	temp->setName(name);
	cout << "Welcome to Warzone, " << name << "!" << endl;
	players.push_back(temp);
}

// This method asks player's name from the console to create a player object 
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

// This method sets up the necessary components for the game to start
bool GameEngine::assignTerritories(void) {
	//Shuffle the vector before assigning territories:
	auto rng = std::default_random_engine{};
	string result;
	bool intl = false;
	vector<Territory*> copy = map->getTerritoyVector();
	std::shuffle(std::begin(copy), std::end(copy), rng);
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

	//2.2.4 Fairly distributing the territories among all players
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

	//2.2.5 Randomly determine the order of play of the players in the game
	std::shuffle(std::begin(players), std::end(players), rng);
	//Create Deck object:
	deck = new Deck();

	//Add initial army value and draw cards:
	for (auto p : players) {
		p->getPlayerHand()->setDeck(deck);
		// 2.2.6 Give 50 initial armies to each player
		p->setArmiesHeld(50);

		//2.2.7 Each player draws 2 cards each from the deck
		deck->draw(p);
		deck->draw(p);
		//For demo purposes, add a card of each type to the player:
		int counter = 0;
		if (!p->intelligent) {
			for (int types = 0; types < 5; types++) {
				for (int cards = 0; cards < 5 ; cards++) { // creates 3 cards (1 card for the demo only) per player per type of card
					counter++; // the first card has ID == 1

					Card* pointer = new Card(types, counter);
					p->addCard(pointer);
				}
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



//-------------------------  Part 3 ------------------------------------
//3.3.2
//3.2.1  Distributes new armies according to number of territories owned by each player
void GameEngine::reinforcementPhase(void) {
	for (auto p : players) {
		p->getCantAttack().empty(); //Clear Negotiate effect
		int originalArmies = p->getArmiesHeld();
		//Count territories owened and divide by 3
		int count = 0;
		for (auto o : p->getTowned()) {
			count++;
		}
		int toAdd = count / 3;

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
			// if so, get a bonus
			if (territoryCount == playerCount) {
				cout << "Player " << p->getName() << " owns the entirety of " << c->name << " and gains a +" << c->armyValue << " bonus." << endl;
				toAdd += c->armyValue;
			}
		}
		//Default minimum to 3
		if (toAdd < 3) {
			toAdd = 3;
		}
		p->setArmiesHeld(toAdd + originalArmies);
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << " has received " << toAdd << " armies." << endl;
		cout << "Current army count is: " << p->getArmiesHeld() << endl;

	}

}
//3.3.3
//3.2.2 Has players issue orders in a round-robin fashion until no Player wants to add more orders
//3.2.3 After all players have signified that they dont have any more orders to isse, the orders execution phases starts. 
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
			if (!p->intelligent && p->getOrders()->getOrderList().size() < 5) {	//Non-intelligent player issues 5 orders per turn
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
//3.3.4
//3.2.5 Executes top order from each player in a round-robin fashion
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

					toDeleteFrom->remove(0); //Remove top order
					if (isThereAwinnerS()) {
						cout << "/////////////////////////////////////" << endl;
						return;
					}
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
				// if there is a winner, return to mainGameLoop(), where players are removed and output the winner's name
				if (isThereAwinnerS()) {
					cout << "/////////////////////////////////////" << endl;
					return;
				}
			}
			else {
				//Draw card if the player has conquered a territory over their round
				//A  player  receives  a  card  at  the  end  of  his  turn  if  they  successfully  conquered  at  least  one  territory 
				//during their turn.
				if (p->getConquered() == true) {
					deck->draw(p);
					p->setConquered(false);
				}
				doneCount++;
			}
			
		}
		if (doneCount >= players.size()) {	//Return to main game loop once all orders have been executed
			playing = false;
		}
	}
}





