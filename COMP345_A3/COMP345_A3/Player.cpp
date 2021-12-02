#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
using namespace std;


class Cards;
class Order;
class OrderList;

//Stream insertions:
istream& operator>>(istream& in, Player& p)
{
	in >> p.name;
	return in;
}

ostream& operator<<(ostream& out, const Player& p)
{
	out << "Player: " << p.name << endl;
	out << "ID: " << p.playerID << endl;
	out << "Armies Held: " << p.armiesHeld << endl;
	out << "Territories owned: " << endl;
	for (Territory* i : p.towned) {
		out << *i;
	}
	out << endl;
	out << "Cards owned: " << endl;
	out << *(p.playerHand);
	out << endl;
	out << "Orders issued: " << endl;
	out << *(p.orders);
	return out;
}

//Static variable initalizer:
int Player::playersCreated = 0;

//Constructors:
Player::Player(void)
{
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	playersCreated++;
	name = "Default";
	armiesHeld = 0;
	playerID = playersCreated;
	orders = new OrdersList();
	playerHand = new Hand();
	intelligent = false;

	//Default player is Human:
	ps = new Human(this); 
}

Player::Player(const Player& other)
{
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	playersCreated++;
	name = other.name;
	armiesHeld = other.armiesHeld;
	playerID = other.playerID;
	for (auto p : other.towned) {
		Territory* temp = new Territory(*p);
		towned.push_back(temp);

	}
	playerHand = new Hand();
	for (auto p : other.cards) {
		Card* temp = new Card(*p);
		playerHand->addCard(temp);

	}
	orders = new OrdersList(*other.orders);

}

//Destructor:
Player::~Player() {
	cout << "Player " << this->getName() << " will now be destroyed." << endl;
	if (orders != NULL) {
		delete orders;
	}
	towned.clear();
	cards.clear();

}

//Assignment operators:
Player& Player::operator =(const Player& other) {
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	name = other.name;
	playerID = other.playerID;
	armiesHeld = other.armiesHeld;
	for (Territory* p : other.towned) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	playerHand = new Hand();
	for (auto p : other.cards) {
		Card* temp = new Card(*p);
		playerHand->addCard(temp);

	}
	orders = new OrdersList(*other.orders);

	return *this;
}

void Player::setStrategy(PlayerStrategy* strategy)
{
	ps = strategy; 
}

//Mutators:
void Player::setPlayerID(int playerID)
{
	this->playerID = playerID;
}

void Player::setName(string name)
{
	this->name = name;
}
void Player::setArmiesHeld(int x)
{
	this->armiesHeld = x;
}
void Player::setTOwned(vector<Territory*> const& other)
{
	towned = other;
}

void Player::setCards(vector<Card*>& cards)
{
	this->cards = cards;
}
void Player::setOrdersList(OrdersList* orders)
{
	this->orders = orders;
}
void Player::setConquered(bool answer) {
	this->conqueredThisTurn = answer;
}

//Acessors:
string Player::getName(void) {
	return name;
}

int Player::getPlayerID(void) {
	return playerID;
}
int Player::getArmiesHeld(void) {
	return armiesHeld;
}
vector<Territory*> Player::getTowned(void) {
	return towned;
}
void Player::removeTerritory(Territory* toRemove) {
	towned.erase(std::remove(towned.begin(), towned.end(), toRemove), towned.end());
}
vector<Card*> Player::getCards(void) {
	return cards;
}

OrdersList* Player::getOrders(void) {
	return orders;
}

//-------------------------  Part 3 ------------------------------------

vector<Player*> Player::getCantAttack() {
	return cannotAttack;
}

bool Player::getConquered(void) {
	return conqueredThisTurn;
}

PlayerStrategy* Player::getStrategy(void)
{
	return ps;
}

// From Cards: 

vector<Card*> Player::getHandOfCards() {
	return this->playerHand->getHandOfCards();
}

Hand* Player::getPlayerHand() {
	return playerHand;
}
void Player::printHand()
{
	cout << *getPlayerHand() << endl;
}
//Creates a player strategy based on input string
void Player::determineStrategy(string strategy)
{
	if (ps != NULL) {
		delete ps;
		ps = NULL;
	}
	if (strategy == "Human") {
		ps = new Human(this);
		intelligent = true;
	}
	else if (strategy == "Aggressive") {
		ps = new Aggressive(this);
		intelligent = false;
	}
	else if (strategy == "Benevolent") {
		ps = new Benevolent(this);
		intelligent = false;
	}
	else if (strategy == "Neutral") {
		ps = new Neutral(this);
		intelligent = false;
	}
	else if (strategy == "Cheater") {
		ps = new Cheater(this);
		intelligent = false;
	}
	else {
		ps = new Human(this);
		intelligent = false;
	}
}

void Player::addTerritory(Territory* ter) {
	ter->setOwner(this);
	towned.push_back(ter);
}

//From Cards:
void Player::addCard(Card* card) {
	playerHand->addCard(card);
}
void Player::addOrder(Order* order) {
	orders->addOrder(order);
}
//Gameplay mechanics:

//Global randomizer seed:
std::random_device rd;
std::default_random_engine rng(rd());

//Returns territories owned by the player
vector<Territory*> Player::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense = ps->toDefend();
	/* CODE TO DELETE:
	for (auto t : towned) {
		defense.push_back(t);
	}
	//At a later development stage, priority will be determined using sorting and the player profile:
	//sort(defense.begin(), defense.end());

	//For testing purposes while priority definition is still not implemented, priority is set to random:
	std::shuffle(std::begin(defense), std::end(defense), rng);
	*/
	return defense;
}

//Returns territories not owned by the Player
vector<Territory*> Player::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack = ps->toAttack();
	/* CODE TO DELETE:
	for (auto t : towned) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != this) {
					attack.push_back(d);
				}

			}

		}
	}
	//At a later development stage, priority will be determined using sorting and the player profile:
	//sort(attack.begin(), attack.end());

	//For testing purposes while priority definition is still not implemented, priority is set to random:
	std::shuffle(std::begin(attack), std::end(attack), rng);
	*/
	return attack;
}

//Determines order target based on toDefend or toAttack methods
void Player::determineTarget(int state, Order* order) {

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	Territory* target;

	if (state == 1) { //Target is one of Player's own territories -> taken from toDefend()
		if (defend.size() == 0) {
			target = NULL;
			//Setting target information to the created order:
			order->setOwner(this);
			order->setTarget(target);
			return;
		}
		cout << "Territories available as a target:" << endl;
		int i = 1;
		for (auto t : defend) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (intelligent) {
			int index;
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (defend.size() >= index && index > 0) {
				cout << "Territory selected as target: " << defend[index - 1]->getTerritoryName() << endl;
				target = defend[index - 1];
			}
			else {
				cout << "Default territory selected as target: " << defend[0]->getTerritoryName() << endl;
				target = defend[0];
			}
		}
		else {	//Default target selection
			cout << "Default territory selected as target: " << defend[0]->getTerritoryName() << endl;
			target = defend[0];
		}


	}
	else {	//Target is one of the enemy territory -> taken from toAttack
		if (attack.size() == 0) {
			target = NULL;
			//Setting target information to the created order:
			order->setOwner(this);
			order->setTarget(target);
			return;
		}
		cout << "Territories available as a target: " << endl;
		int i = 1, index;
		for (auto t : attack) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced() << " - Owner: " << t->getOwner()->getName();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (intelligent) {
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (attack.size() >= index && index > 0) {
				cout << "Territory selected as target: " << attack[index - 1]->getTerritoryName() << endl;
				target = attack[index - 1];
			}
			else {
				cout << "Default territory selected as target: " << attack[0]->getTerritoryName() << endl;
				target = attack[0];
			}
		}
		else {
			cout << "Default territory selected as target: " << attack[0]->getTerritoryName() << endl;
			target = attack[0];
		}

	}

	//Setting target information to the created order:
	order->setOwner(this);
	order->setTarget(target);
}
//Determines order source based on toDefend method
void Player::determineSource(int state, Order* order) {
	vector<Territory*> defend = toDefend();
	Territory* target = order->getTarget();
	Territory* source = NULL;
	if (defend.size() == 0) {
		source = NULL;
		//Setting target information to the created order:
		order->setSource(source);
		return;
	}
	if (target != NULL) {
		cout << "Territories available as a source:" << endl;
		int i = 1;
		for (auto t : defend) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (intelligent) {
			int index;
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (defend.size() >= index && index > 0) {
				cout << "Territory selected as source:" << defend[index - 1]->getTerritoryName() << endl;
				source = defend[index - 1];
			}
			else {
				cout << "Default territory selected as target:" << defend[0]->getTerritoryName() << endl;
				source = defend[0];
			}
		}
		else {	//Default source selection
			cout << "Default territory selected as target:" << defend[0]->getTerritoryName() << endl;
			source = defend[0];
		}

	}
	order->setSource(source);

}
//Prints standard order information as well as player's hand
void Player::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following orders are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player's territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player's territories(source) to an adjacent territory." << endl;
	cout << "TARGET: If the target territory belongs to the current player, the armies are moved to the target.\nIf the target territory belongs to another player, an attack happens between the two territories." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player's territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current player and another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;

	cout << *getPlayerHand();
}
//Sets the number of armies to be deployed
int Player::deployArmies(void) {
	if (!intelligent) {
		return 10;
	}
	cout << "Please indicate how many armies you would like to attempt to deploy:" << endl;
	int x;
	cin >> x;
	if (x >= 1) {
		return x;
	}
	else {
		return 1;
	}
}

//3.2.4 A player can create any kind of order, inlcuding those that can only be created using cards.
//Given a string, issue the corresponding order
Order* Player::discoverOrderType(string x) {
	Order* newOrder;
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();

	string options[] = { "reinforcement", "advance", "bomb", "blockade", "airlift", "diplomacy", "unspecified" };
	
	//Create the correct order based on command:
	if (x.compare(options[0]) == 0) { //Deployment orders and reinforcement.
		cout << "You have issued a deploy order." << endl;
		if (armiesHeld <= 0) {
			cout << "Player does not own enough armies to deploy to a new territory." << endl;
			newOrder = NULL;
			return newOrder;

		}
		if (toDefend().size() == 0) {
			cout << "Player does not own a territory." << endl;
			newOrder = NULL;
			return newOrder;
		}
		newOrder = new DeployOrder();
		determineTarget(1, newOrder);
		int armiesToPlace = deployArmies();

		if (armiesToPlace <= armiesHeld) {
			newOrder->setModifier(armiesToPlace);
			newOrder->armyModifier = armiesToPlace;
			armiesHeld -= armiesToPlace;

		}
		else {
			cout << "Only the remaining armies will be deployed." << endl;
			newOrder->setModifier(armiesHeld);
			newOrder->armyModifier = armiesHeld;
			armiesHeld = 0;

		}
	}
	else if (x.compare(options[1]) == 0) { //Still requires the moving from current to target mechanism
		string cmd;
		if (!intelligent) {
			cmd = "attack";
		}
		else {
			cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
			cin >> cmd;
			while (cmd != "attack" && cmd != "defend") {
				cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
				cin >> cmd;
			}
		}

		if (cmd == "attack") {
			newOrder = new AdvanceOrder();
			newOrder->setOwner(this);
			determineTarget(0, newOrder);
			determineSource(0, newOrder);
			newOrder->setModifier(0);	//Advance set to attack mode
			newOrder->armyModifier = deployArmies();

		}
		else {
			newOrder = new AdvanceOrder();
			newOrder->setOwner(this);
			determineTarget(1, newOrder);
			determineSource(1, newOrder);
			newOrder->setModifier(1); //Advance set to defend mode
			newOrder->armyModifier = deployArmies();
		}


	}
	else if (x.compare(options[2]) == 0) {
		cout << "You have issued a bomb order." << endl;
		newOrder = new BombOrder();
		newOrder->setOwner(this);
		determineTarget(0, newOrder);
		newOrder->setModifier(0);

	}
	else if (x.compare(options[3]) == 0) {
		cout << "You have issued a blockade order:" << endl;
		newOrder = new BlockadeOrder();
		newOrder->setOwner(this);
		determineTarget(1, newOrder);
		newOrder->setModifier(0);
		newOrder->neutralPlayer = neutral;

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order." << endl;
		newOrder = new AirliftOrder();
		newOrder->setOwner(this);
		determineTarget(1, newOrder);
		determineSource(1, newOrder);
		newOrder->armyModifier = deployArmies();
	}
	else if (x.compare(options[5]) == 0) {
		cout << "You have issued a negotiate order. Please indicate which of the territories you would like to attempt diplomacy with:" << endl;
		newOrder = new NegotiateOrder();
		newOrder->setOwner(this);
		determineTarget(0, newOrder);

	}
	else {
		newOrder = NULL;
	}
	
	return newOrder;
}

//Issues a order for the Player
void Player::issueOrder()
{
	ps->issueOrder();
}