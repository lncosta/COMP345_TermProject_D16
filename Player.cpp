#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

void OrdersList::addOrder(Order& other) {
	listOfOrders.push_back(other);
	count++;
}
OrdersList::OrdersList(void) {
	count = 0;
}

int Player::playersCreated = 0;
Player::Player(void)
{
	playersCreated++;
	name = "Default";
	playerID = playersCreated;
	orders = new OrdersList();
	
	
}

Player::Player(const Player &other)
{
	playersCreated++;
	name = other.name;
	playerID = other.playerID;
	towned = other.towned;
	cards = other.cards;
	orders = other.orders;

	
}
//Destructor:

//Player::~Player() { delete[] orders; }

void Player::setPlayerID(int playerID)
{
	this->playerID = playerID;
}

void Player::setName(string name)
{
	this->name = name;
}

void Player::setTOwned(vector<Territory*> const &other)
{
	towned = other;
}

void Player::setCards(vector<Cards*>& cards)
{
	this->cards = cards;
}

string Player::getName(void) {
	return name;
}

int Player::getPlayerID(void) {
	return playerID;
}
void Player::setOrdersList(OrdersList* orders)
{
	this->orders = orders;
}
void Player::addTerritory(Territory* ter) {
	towned.push_back(ter);
}
void Player::addCard(Cards* other) {
	cards.push_back(other);
}
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
	cout << "The following commands are avaialable: " << endl;
	cout << "DEPLOY: place some armies on one of the current player’s territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player’s territories(source) to an adjacent territory." << endl;
	cout << "TARGET: If the target territory belongs to the current player, the armies are moved to the target.\nIf the target territory belongs to another player, an attack happens between the two territories." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player’s territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current playerand another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;
}

void Player::discoverOrderType(string x, Order &issued) {
	string options[] = { "DEPLOY", "ADVANCE", "TARGET", "BOMB", "AIRLIFT", "NEGOTIATE" };

	for (int i = 0; i < 6; i++)
	{
		if (options[i].compare(x) == 0) {
			issued.name = options[i];
			return;
		}
	}

	issued.name = "UNKOWN ORDER";
	return;
}

void Player::issueOrder()
{
	Order issued;
	string x;
	
	printOrderList();
	cout << "Please type out the order you would like to issue: " << endl;
	cin >> x;
	discoverOrderType(x, issued);
	(*orders).addOrder(issued);
	cout << "Order was issued: " << issued.name << endl;
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
	out << *(p.orders);
	return out;
}

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
	for (Order i : p.listOfOrders) {
		out << i;
	}
	return out;

}

istream& operator>>(istream& in, OrdersList& p)
{
	in >> p.count;
	return in;
}

template <typename T>
void printVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << endl;
	}
}