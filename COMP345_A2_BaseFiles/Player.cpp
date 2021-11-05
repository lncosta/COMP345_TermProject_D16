#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

/*COMP 345 Section D - Assignment #1
* Fall 2021
* Due October 8th, 2021
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
	playerID = playersCreated;
	orders = new OrdersList();
	playerHand = new Hand(); 
}

Player::Player(const Player& other)
{
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	playersCreated++;
	name = other.name;
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
	//Currently Territory and Card objects are allocated on the stack, so they are freed automatically at the end of main() and manually deleting the pointers generates an error.
	//Once code is integrated and objects are created using "new", the following must be commented out:
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
	Territory* a = new Territory(1, 2, "Canada");
	Territory* b = new Territory(2, 2, "Japan");
	Territory* c = new Territory(1, 2, "France");
	vector<Territory*> defense;
	defense.push_back(a);
	defense.push_back(b);
	defense.push_back(c);
	return defense;
}

vector<Territory*> Player::toAttack()
{
	Territory* a = new Territory(1, 2, "Canada");
	Territory* b = new Territory(2, 2, "Japan");
	Territory* c = new Territory(1, 2, "France");
	vector<Territory*> attack;
	attack.push_back(a);
	attack.push_back(b);
	attack.push_back(c);
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
}

Order* Player::discoverOrderType(string x) {
	string options[] = { "DEPLOY", "ADVANCE", "BOMB", "BLOCK", "AIRLIFT", "NEGOTIATE", "UNSPECIFIED"};
	Order* newOrder;
	if (x.compare(options[0]) == 0) {
		newOrder = new DeployOrder(2); 
	}
	else if (x.compare(options[1]) == 0) {
		newOrder = new AdvanceOrder(3);
	}
	else if (x.compare(options[2]) == 0) {
		newOrder = new BombOrder(5);
	}
	else if (x.compare(options[3]) == 0) {
		newOrder = new BlockadeOrder(4); 

	}
	else if (x.compare(options[4]) == 0) {
		newOrder = new AirliftOrder(5);
	}
	else if (x.compare(options[5]) == 0) {
		newOrder = new NegotiateOrder(6);
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

	printOrderList();
	cout << "Please type out the order you would like to issue: " << endl;
	cin >> x;
	issued = discoverOrderType(x);
	
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