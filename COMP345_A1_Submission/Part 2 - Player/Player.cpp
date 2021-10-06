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


//Stream insertions:


istream& operator>>(istream& in, Player& p)
{
	in >> p.name;
	return in;
}

ostream& operator<<(ostream& out, const Territory& p)
{
	out << p.name << endl;
	return out;
}

istream& operator>>(istream& in, Territory& p)
{
	in >> p.name;
	return in;
}

ostream& operator<<(ostream& out, const Cards& p)
{
	out << p.name << endl;
	return out;
}


istream& operator>>(istream& in, Cards& p)
{
	in >> p.name;
	return in;
}



ostream& operator<<(ostream& out, const Order& p)
{
	out << p.name << endl;
	return out;

}

ostream& operator<<(ostream& out, const OrdersList& p)
{
	out << "The player has the following list of orders:" << endl;
	for (auto i : p.listOfOrders) {
		out << *i;
	}
	return out;

}

istream& operator>>(istream& in, OrdersList& p)
{
	in >> p.count;
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
	for (Cards* i : p.cards) {
		out << *i;
	}
	out << endl;
	out << "Orders issued: " << endl; 
	for (Order* k : p.orders->listOfOrders) {
		out << *k;
	}
	return out;
}

//Definitions for temporary classes:

void OrdersList::addOrder(Order* other) {
	listOfOrders.push_back(other);
	count++;
}
Order::~Order(void) {
	cout << "Order " << name << " will be deleted." << endl;
}
OrdersList::OrdersList(void) {
	count = 0;
}
OrdersList::~OrdersList(void) {
	cout << "This list of orders will be deleted." << endl;
	for (auto p : listOfOrders) {
		delete p;
	}
}
Territory::Territory(Territory& other) {
	name = other.name;
	id = other.id;
}
Territory::Territory(void) {
	name = "Default";
	id = "0";
}
Territory::~Territory(void) {
	cout <<"The territory " << name <<" was deleted." << endl;
}
Cards::Cards(Cards& other) {
	name = other.name;
}
Cards::Cards(void) {
	name = "Default";
}
Cards::~Cards(void) {
	cout << "The Card " << name << " was deleted." << endl;
}


int Player::playersCreated = 0;

//Constructors:
Player::Player(void)
{
	playersCreated++;
	name = "Default";
	playerID = playersCreated;
	orders = new OrdersList();
}

Player::Player(const Player& other)
{
	playersCreated++;
	name = other.name;
	playerID = other.playerID;
	for (auto p : other.towned) {
		Territory* temp = new Territory(*p); 
		towned.push_back(temp); 
	
	}
	for (auto p : other.cards) {
		Cards* temp = new Cards(*p);
		cards.push_back(temp);
		
	}
	orders = new OrdersList(); 
	for (auto p : other.orders->listOfOrders) {
		Order* temp = new Order();
		temp->name = p->name;
		orders->addOrder(temp);
	}
	
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
	name = other.name;
	playerID = other.playerID;
	for (Territory* p : other.towned) {
		Territory* temp = new Territory(*p);
		addTerritory(temp); 
	}
	for (auto p : other.cards) {
		Cards* temp = new Cards(*p);
		addCard(temp);

	}
	orders = new OrdersList();
	for (auto p : other.orders->listOfOrders) {
		Order* temp = new Order();
		temp->name = p->name;
		orders->addOrder(temp);
	}
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

void Player::setCards(vector<Cards*>& cards)
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
vector<Cards*> Player::getCards(void) {
	return cards;
}

OrdersList* Player::getOrders(void) {
	return orders;
}

void Player::addTerritory(Territory* ter) {
	towned.push_back(ter);
}
void Player::addCard(Cards* other) {
	cards.push_back(other);
}

//Gameplay mechanics:
vector<Territory*> Player::toDefend()
{
	Territory* a = new Territory();
	Territory* b = new Territory();
	Territory* c = new Territory();
	a->name = "Canada";
	b->name = "France";
	c->name = "Japan";
	vector<Territory*> defense;
	defense.push_back(a);
	defense.push_back(b);
	defense.push_back(c);
	return defense;
}

vector<Territory*> Player::toAttack()
{
	Territory* a = new Territory();
	Territory* b = new Territory();
	Territory* c = new Territory();
	a->name = "Canada";
	b->name = "France";
	c->name = "Japan";
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

void Player::discoverOrderType(string x, Order* issued) {
	string options[] = { "DEPLOY", "ADVANCE", "TARGET", "BOMB", "AIRLIFT", "NEGOTIATE" };

	for (int i = 0; i < 6; i++)
	{
		if (options[i].compare(x) == 0) {
			issued->name = options[i];
			return;
		}
	}

	issued->name = "UNKOWN ORDER";
	return;
}

void Player::issueOrder()
{
	Order* issued = new Order();
	string x;

	printOrderList();
	cout << "Please type out the order you would like to issue: " << endl;
	cin >> x;
	discoverOrderType(x, issued);
	orders->addOrder(issued);
	cout << "Order was issued: " << issued->name << endl;
	cout << "Current Player orders: " << endl;
	for (auto p : orders->listOfOrders) {
		cout << *p; 
	}
}


template <typename T>
void printVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << endl;
	}
}