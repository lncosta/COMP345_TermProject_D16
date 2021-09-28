#pragma once
#include <vector>
#include <iterator>
#include <string>

//#include "Territory.h"
//#include "Cards.h"
//#include "OrdersList.h"

using namespace std;


class Territory {
public:
	string name;
	string id;
	friend ostream& operator << (ostream& out, const Territory& p);
	friend istream& operator >> (istream& in, Territory& p);

};

class Cards {
public:
	string name;
	friend ostream& operator << (ostream& out, const Cards& p);
	friend istream& operator >> (istream& in, Cards& p);
};
class Order {
public:
	string name;
};

class OrdersList {
public:
	vector<Order> listOfOrders;
	int count;
	void addOrder(Order& other);
	friend ostream& operator << (ostream& out, const OrdersList& p);
	friend istream& operator >> (istream& in, OrdersList& p);
	OrdersList(void);
};


class Player {
static int playersCreated;
private:
	//Data members:
	int playerID;
	string name;
	vector<Territory*> towned;
	vector<Cards*> cards;
	OrdersList* orders;

public:
	//Constructors:
	Player(void);
	Player(const Player &other);

	//Assignment Operators:

	void setPlayerID(int playerID);
	void setName(string name);
	void setTOwned(vector<Territory*> const &other);
	void setCards(vector<Cards*>& cards);
	void setOrdersList(OrdersList* orders);

	//Accessor methods:
	string getName(void);
	int getPlayerID(void);
	
	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	//Destructors:
	//~Player(void);
	//Methods:
	void printOrderList(void);
	void discoverOrderType(string x, Order& issued);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	void addTerritory(Territory* ter);
	void addCard(Cards* other);

};

