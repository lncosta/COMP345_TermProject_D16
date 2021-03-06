#pragma once
#include <vector>
#include <iterator>
#include <string>

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
using namespace std;


class Territory {
public:
	string name;
	string id;
	friend ostream& operator << (ostream& out, const Territory& p);
	friend istream& operator >> (istream& in, Territory& p);
	Territory(Territory& other);
	Territory(void); 
	~Territory(void);

};

class Cards {
public:
	string name;
	friend ostream& operator << (ostream& out, const Cards& p);
	friend istream& operator >> (istream& in, Cards& p);
	Cards(Cards& other);
	Cards(void);
	~Cards(void);
};
class Order {
public:
	string name;
	~Order(void);
};

class OrdersList {
public:
	vector<Order*> listOfOrders;
	int count;
	void addOrder(Order* other);
	friend ostream& operator << (ostream& out, const OrdersList& p);
	friend istream& operator >> (istream& in, OrdersList& p);
	OrdersList(void);
	~OrdersList(void);
};


class Player {
	static int playersCreated;
private:
	//Data members:
	int playerID;
	string name;
	vector<Territory*> towned;
	vector<Cards*> cards; //Will become a Hand* pointer once code is integrated with Part 5 of assignment. For now, a hand is simply considered a collection of cards held by the Player itself. 
	OrdersList* orders;

public:
	//Constructors:
	Player(void);
	Player(const Player& other);

	//Assignment Operators:

	void setPlayerID(int playerID);
	void setName(string name);
	void setTOwned(vector<Territory*> const& other);
	void setCards(vector<Cards*>& cards);
	void setOrdersList(OrdersList* orders);
	Player& operator =(const Player& other); 

	//Accessor methods:
	string getName(void);
	int getPlayerID(void);
	vector<Territory*> getTowned(void);
	vector<Cards*> getCards(void);
	OrdersList* getOrders(void);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	//Destructors:
	~Player(void);
	//Methods:
	void printOrderList(void);
	void discoverOrderType(string x, Order* issued);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	void addTerritory(Territory* ter);
	void addCard(Cards* other);

};