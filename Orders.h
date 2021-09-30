#include <string>
#include <iostream>
#include <vector>

using namespace std;

#pragma once
#define ORDERS_H

//All classes must implement 
//a correct copy constructor, assignment operator, and stream insertion operator.
//only class members that are user-defined types are to be pointers

class Order {
public:
	int id;

	Order();
	~Order();
	Order(int test);
	Order(const Order& o);

	string getName() const { return nameOfOrder; }
	string getDesc() const { return description; }
	void operator=(const Order& order) {
		this->id = order.id;
	};

	friend ostream& operator<<(ostream& output, const Order& order) {
		output << order.id << "\n" << order.getName() << "\n" << order.getDesc() << endl;
		return output;
	};
private:
	const string nameOfOrder = "Unspecified Order";
	const string description = "Unspecified order description";
};

class OrdersList {
public:
	//bool isEmpty; // do this?

	OrdersList();
	~OrdersList();
	OrdersList(const OrdersList& list);
	const std::vector<Order*>& getOrderList() const { return orderList; }
	
	//also make sure the Order class cannot be added, only subclasses
	void addOrder(Order* order);
	void move(int toMove, int location); 
	void remove(int toRemove); 
	int getCount() { orderList.size(); }
	
	void operator=(const OrdersList& olist) {
		std::vector<Order*> vectorlist = olist.getOrderList();
		for (int i = 0; i < vectorlist.size(); i++) {
			this->orderList.push_back(new Order(*vectorlist.at(i)));
		}
	};
	
	friend ostream& operator<<(ostream& output, const OrdersList& list) {
		std::vector<Order*> vectorlist = list.getOrderList();
		for (int i = 0; i < vectorlist.size(); i++) {
			output << *vectorlist.at(i) << endl;
		}
		return output;
	};
	
private:
	std::vector<Order*> orderList; 
};

class DeployOrder : public Order {
public:
	DeployOrder();
	DeployOrder(int thisId);
	~DeployOrder(); //for pointers
	DeployOrder(const DeployOrder& order);
	
	bool validate();
	void execute();  // calls validate
	string getName() const { return nameOfOrder; }
	string getDesc() const { return description; }
	void setId(int theId) { this->id = theId; }
	void operator=(const DeployOrder& order) {
		Order::operator=(order);
	};

	friend ostream &operator<<(ostream &output, const DeployOrder &order) {
		output << order.id << "\n" << order.getName() << "\n" << order.getDesc() << endl;
		return output;
	}
private:
	const string nameOfOrder = "Deploy";
	const string description = "Place some armies on one of the current player's territories.";
};

//order subclasses + validate() + execute()
/*
class AdvanceOrder : public Order {
public:
	void execute();
private:
	bool validate();
	const string nameOfOrder = "Advance";
	const string description = "Move some armies from one of the current player’s territories (source) to an adjacent territory (target).";
};

class BombOrder : public Order {
public:
	void execute();
private:
	bool validate();
	const string nameOfOrder = "Bomb";
	const string description = "Destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories.";
};

class BlockadeOrder : public Order {
public:
	void execute();
private:
	bool validate();
	const string nameOfOrder = "Blockade";
	const string description = "Triple the number of armies on one of the current player’s territories and make it a neutral territory.";
};

class AirliftOrder : public Order {
public:
	void execute();
private:
	bool validate();
	const string nameOfOrder = "Airlift";
	const string description = "Advance some armies from one of the current player’s territories to any another territory.";
};

class NegotiateOrder : public Order {
public:
	void execute();
private:
	bool validate();
	const string nameOfOrder = "Negotiate";
	const string description = "Prevent attacks between the current player and another player until the end of the turn.";
};
*/
