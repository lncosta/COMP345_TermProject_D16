#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*COMP 345 Section D - Assignment #2
* Fall 2021
* Due November 12th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/

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
	
	cout << "Player " << this->getName() << "'s Territories will now be destroyed." << endl;
	for (auto p: towned){
			delete p;
	 }
	cout << "Player " << this->getName() << "'s Cards will now be destroyed." << endl;
	for (auto p : cards) {
		 delete p;
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
vector<Card*> Player::getCards(void) {
	return cards;
}

OrdersList* Player::getOrders(void) {
	return orders;
}

// From Cards: 

vector<Card*> Player::getHandOfCards() {
	return this->playerHand->getHandOfCards();
}

Hand* Player::getPlayerHand() {
		return playerHand;
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

vector<Territory*> Player::toDefend()
{
	
	vector<Territory*> defense;
	for (auto t : towned) {
		defense.push_back(t);
	}
	sort(defense.begin(), defense.end());
	
	return defense;
}

vector<Territory*> Player::toAttack()
{
	vector<Territory*> attack;
	for (auto t : towned) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(),d) != attack.end())) {
				if (d->getOwner() != this) {
					attack.push_back(d);
				}
				
			}
			
		}
	}
	sort(attack.begin(), attack.end());
	return attack;
}
void Player::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following commands are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player’s territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player’s territories(source) to an adjacent territory." << endl;
	cout << "TARGET: If the target territory belongs to the current player, the armies are moved to the target.\nIf the target territory belongs to another player, an attack happens between the two territories." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player’s territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current playerand another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;

	cout << *getPlayerHand();
}

Order* Player::discoverOrderType(string x) {
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	
	string options[] = { "reinforcement", "advance", "bomb", "blockade", "airlift", "diplomacy", "unspecified"};
	Order* newOrder;
	//Create the correct order based on command:
	if (x.compare(options[0]) == 0) { //Deployment orders and reinforcement.
		cout << "You have issued a deploy order. Please indicate which of the territories you would like to defend:" << endl;
		cout << "Territories available to defend:" << endl;
		for (auto t : defend) {
			cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string defendTerritory;
		bool searching = true;
		while (true) {
			cin >> defendTerritory;
			auto it = find_if(defend.begin(), defend.end(), [&defendTerritory](Territory* obj) {
				return obj->getTerritoryName() == defendTerritory; });
			if (it != defend.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;
				if (armiesToPlace <= armiesHeld) {
					newOrder = new DeployOrder();
					newOrder->setOwner(this);
					newOrder->setTarget(*it);
					newOrder->setModifier(armiesToPlace);
					armiesHeld -= armiesToPlace; 
					break;
				}
				else {
					cout << "Only the remaining armies will be deployed." << endl;
					newOrder = new DeployOrder();
					newOrder->setOwner(this);
					newOrder->setTarget(*it);
					newOrder->setModifier(armiesHeld);
					armiesHeld = 0;
					break;
				}
				
			}
			else {
				cout << "The territory requested cannot be defended." << endl;
			}
		}

	

	}
	else if (x.compare(options[1]) == 0) { //Still requires the moving from current to target mechanism
		cout << "You have issued an advance order. Please indicate which of the territories you would like to attack:" << endl;
		cout << "Territories available to attack: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string target;
		bool searching = true;
		while (true) {
			cin >> target;
			auto it = find_if(attack.begin(), attack.end(), [&target](Territory* obj) {
				return obj->getTerritoryName() == target; });
			if (it != attack.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;
				newOrder = new AdvanceOrder();
				newOrder->setOwner(this);
				newOrder->setTarget(*it);
				newOrder->setModifier(armiesToPlace);
				break;
			}
			else {
				cout << "The territory requested cannot be attacked." << endl;
			}
		}

	}
	else if (x.compare(options[2]) == 0) {
		cout << "You have issued a bomb order. Please indicate which of the territories you would like to attack:" << endl;
		cout << "Territories available to attack: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string target;
		bool searching = true;
		while (true) {
			cin >> target;
			auto it = find_if(attack.begin(), attack.end(), [&target](Territory* obj) {
				return obj->getTerritoryName() == target; });
			if (it != attack.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;

				newOrder = new BombOrder();
				newOrder->setOwner(this);
				newOrder->setTarget(*it);
				newOrder->setModifier(armiesToPlace);
				break;
			}
			else {
				cout << "The territory requested cannot be attacked." << endl;
			}
		}
	
	}
	else if (x.compare(options[3]) == 0) {
		cout << "You have issued a blockade order. Please indicate which of the territories you would like to attack:" << endl;
		cout << "Territories available to attack: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string target;
		bool searching = true;
		while (true) {
			cin >> target;
			auto it = find_if(attack.begin(), attack.end(), [&target](Territory* obj) {
				return obj->getTerritoryName() == target; });
			if (it != attack.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;

				newOrder = new BlockadeOrder();
				newOrder->setOwner(this);
				newOrder->setTarget(*it);
				newOrder->setModifier(armiesToPlace);
				break;
			}
			else {
				cout << "The territory requested cannot be attacked." << endl;
			}
		}
		

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order. Please indicate which of the territories you would like to attack:" << endl;
		cout << "Territories available to attack: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string target;
		bool searching = true;
		while (true) {
			cin >> target;
			auto it = find_if(attack.begin(), attack.end(), [&target](Territory* obj) {
				return obj->getTerritoryName() == target; });
			if (it != attack.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;

				newOrder = new AirliftOrder();
				newOrder->setOwner(this);
				newOrder->setTarget(*it);
				newOrder->setModifier(armiesToPlace); 
				break;
			}
			else {
				cout << "The territory requested cannot be attacked." << endl;
			}
		}
		
	}
	else if (x.compare(options[5]) == 0) {
		cout << "You have issued a negotiate order. Please indicate which of the territories you would like to attempt diplomacy with:" << endl;
		cout << "Territories available to negotiate with: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Please indicate the target territory: " << endl;
		string target;
		bool searching = true;
		while (true) {
			cin >> target;
			auto it = find_if(attack.begin(), attack.end(), [&target](Territory* obj) {
				return obj->getTerritoryName() == target; });
			if (it != attack.end()) {
				cout << "Valid territory." << endl;
				cout << "How many armies would you like to deploy there?" << endl;
				int armiesToPlace;
				cin >> armiesToPlace;

				newOrder = new NegotiateOrder();
				newOrder->setOwner(this);
				newOrder->setTarget(*it);
				newOrder->setModifier(armiesToPlace);
				break;
			}
			else {
				cout << "The territory requested cannot be negotiated with." << endl;
			}
		}
		
	}
	else {
		newOrder = NULL;
	}

	return newOrder;
}

void Player::issueOrder()
{
	Order* issued;
	string x;

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	cout << "Territories available to defend:" << endl;
	for (auto t : defend) {
		cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
	}

	//Playing the cards:
	cout << "Territories available to attack: " << endl;
	for (auto t : attack) {
		cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
	}

	if (armiesHeld > 0) { //Deployment phase.
		cout << "Player must deploy armies." << endl; 
		cout << "Armies held: " << armiesHeld << endl; 
		issued = discoverOrderType("reinforcement");
	}
	else { //Attack and Card phase.
		printOrderList();
		cout << "Please select a card to play." << endl;
		cin >> x;
		vector<string> options2;
		for (auto name : getPlayerHand()->getHandOfCards()) {	//Check which commands are available based on player's hand of cards
			if (name->getType() == 0) {
				options2.push_back("bomb");
			}
			else if (name->getType() == 1) {
				options2.push_back("reinforcement");
			}
			else if (name->getType() == 2) {
				options2.push_back("blockade");
			}
			else if (name->getType() == 3) {
				options2.push_back("airlift");
			}
			else if (name->getType() == 4) {
				options2.push_back("diplomacy");
			}

		}
		if (!(find(options2.begin(), options2.end(), x) != options2.end())) {	//If the player does not have the necessary card to issue to requested order, return null
			cout << "The command you requested is not available at the time. " << endl;
			issued = NULL;
		}
		else {
			//Play the card and issue the order:
			issued = discoverOrderType(x);

			//Remove correspondent card.
		}
	}
	
	
	
	if (issued == NULL) {
		cout << "Invalid Order. Could not add it to the list." << endl;
	}
	else {
		orders->addOrder(issued);
		cout << "Order was issued: " << issued->getName() << endl;
	
		cout << "Current Player orders: " << endl;
		for (auto p : orders->getOrderList()) {
			cout << *p;
		}
	}
}


template <typename T>
void printVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << endl;
	}
}