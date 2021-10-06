#pragma once
#include <string>
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

#define ORDERS_H

enum class OrderType { Deploy, Advance, Bomb, Blockade, Airlift, Negotiate, Unspecified };

/*
	Order class.
	It is the base class for all kinds of Orders.
*/
class Order {
public:
	int id;
	OrderType type = OrderType::Unspecified;

	Order();
	~Order();
	Order(int test);
	Order(const Order& o);

	virtual bool validate() { return false; }
	virtual void execute() { return; }
	virtual string getName() const { return nameOfOrder; }
	virtual string getDesc() const { return description; }
	virtual OrderType getOrderType() { return type; }
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

/*
	DeployOrder class.
	It derives Order and allows for its execution.
*/
class DeployOrder : public Order {
private:
	const string nameOfOrder = "Deploy";
	const string description = "Place some armies on one of the current player's territories.";
public:
	OrderType type = OrderType::Deploy;

	DeployOrder();
	DeployOrder(int thisId);
	~DeployOrder();
	DeployOrder(const DeployOrder& order);
	DeployOrder(const Order& order);


	bool validate();
	void execute();  // calls validate
	string getName() const { return DeployOrder::nameOfOrder; }
	string getDesc() const { return DeployOrder::description; }
	void setId(int theId) { this->id = theId; }
	OrderType getOrderType() { return type; }

	DeployOrder& operator=(const DeployOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const DeployOrder& dorder) {
		output << dorder.id << "\n" << dorder.getName() << "\n" << dorder.getDesc() << endl;
		return output;
	}
};

/*
	AdvanceOrder class.
	It derives Order and allows for its execution.
*/
class AdvanceOrder : public Order {
private:
	const string nameOfOrder = "Advance";
	const string description = "Move some armies from one of the current player's territories (source) to an adjacent territory (target).";
public:
	OrderType type = OrderType::Advance;

	AdvanceOrder();
	AdvanceOrder(int thisId);
	~AdvanceOrder();
	AdvanceOrder(const AdvanceOrder& order);
	AdvanceOrder(const Order& order);

	void execute(); // calls validate
	bool validate();
	string getName() const { return AdvanceOrder::nameOfOrder; }
	string getDesc() const { return AdvanceOrder::description; }
	void setId(int theId) { this->id = theId; }
	OrderType getOrderType() { return type; }

	AdvanceOrder& operator=(const AdvanceOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const AdvanceOrder& aorder) {
		output << aorder.id << "\n" << aorder.getName() << "\n" << aorder.getDesc() << endl;
		return output;
	}
};

/*
	BombOrder class.
	It derives Order and allows for its execution.
*/
class BombOrder : public Order {
private:
	const string nameOfOrder = "Bomb";
	const string description = "Destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories.";
public:
	OrderType type = OrderType::Bomb;

	BombOrder();
	BombOrder(int thisId);
	~BombOrder();
	BombOrder(const BombOrder& order);
	BombOrder(const Order& order);

	void execute(); // calls validate
	bool validate();
	string getName() const { return BombOrder::nameOfOrder; }
	string getDesc() const { return BombOrder::description; }
	void setId(int theId) { this->id = theId; }
	OrderType getOrderType() { return type; }

	BombOrder& operator=(const BombOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const BombOrder& border) {
		output << border.id << "\n" << border.getName() << "\n" << border.getDesc() << endl;
		return output;
	}
};

/*
	BlockadeOrder class.
	It derives Order and allows for its execution.
*/
class BlockadeOrder : public Order {
private:
	const string nameOfOrder = "Blockade";
	const string description = "Triple the number of armies on one of the current player's territories and make it a neutral territory.";
public:
	OrderType type = OrderType::Blockade;

	BlockadeOrder();
	BlockadeOrder(int thisId);
	~BlockadeOrder();
	BlockadeOrder(const BlockadeOrder& order);
	BlockadeOrder(const Order& order);

	void execute(); // calls validate
	bool validate();
	string getName() const { return BlockadeOrder::nameOfOrder; }
	string getDesc() const { return BlockadeOrder::description; }
	void setId(int theId) { this->id = theId; }
	OrderType getOrderType() { return type; }

	BlockadeOrder& operator=(const BlockadeOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const BlockadeOrder& border) {
		output << border.id << "\n" << border.getName() << "\n" << border.getDesc() << endl;
		return output;
	}
};

/*
	AirliftOrder class.
	It derives Order and allows for its execution.
*/
class AirliftOrder : public Order {
private:
	const string nameOfOrder = "Airlift";
	const string description = "Advance some armies from one of the current player's territories to any another territory.";
public:
	OrderType type = OrderType::Airlift;

	AirliftOrder();
	AirliftOrder(int thisId);
	~AirliftOrder();
	AirliftOrder(const AirliftOrder& order);
	AirliftOrder(const Order& order);

	void execute(); // calls validate
	bool validate();
	string getName() const { return AirliftOrder::nameOfOrder; }
	string getDesc() const { return AirliftOrder::description; }
	void setId(int theId) { this->id = theId; }
	OrderType getOrderType() { return type; }

	AirliftOrder& operator=(const AirliftOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const AirliftOrder& aorder) {
		output << aorder.id << "\n" << aorder.getName() << "\n" << aorder.getDesc() << endl;
		return output;
	}
};

/*
	NegotiateOrder class.
	It derives Order and allows for its execution.
*/
class NegotiateOrder : public Order {
private:
	const string nameOfOrder = "Negotiate";
	const string description = "Prevent attacks between the current player and another player until the end of the turn.";
public:
	OrderType type = OrderType::Negotiate;

	NegotiateOrder();
	NegotiateOrder(int thisId);
	~NegotiateOrder();
	NegotiateOrder(const NegotiateOrder& order);
	NegotiateOrder(const Order& order);

	void execute(); // calls validate
	bool validate();
	string getName() const { return NegotiateOrder::nameOfOrder; }
	string getDesc() const { return NegotiateOrder::description; }
	OrderType getOrderType() { return type; }
	void setId(int theId) { this->id = theId; }

	NegotiateOrder& operator=(const NegotiateOrder& order) {
		this->id = order.id;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const NegotiateOrder& norder) {
		output << norder.id << "\n" << norder.getName() << "\n" << norder.getDesc() << endl;
		return output;
	}
};

/*
	OrdersList class.
	It acts as a list of orders and enables its manipulation.
*/
class OrdersList {
private:
	std::vector<Order*> orderList;
public:
	OrdersList();
	~OrdersList();
	OrdersList(const OrdersList& list);
	const std::vector<Order*>& getOrderList() const { return orderList; }

	void addOrder(Order* order);
	void move(int toMove, int location);
	void remove(int toRemove);
	int getCount() { orderList.size(); }

	OrdersList& operator=(const OrdersList& olist) {
		// first check if lhs is equal to rhs
		if (this == &olist) {
			return *this;
		}
		//empty current list to start the copy
		for (Order* individualOrder : orderList) {
			delete individualOrder;
			individualOrder = nullptr;
		}
		orderList.clear();

		//fill the vector with the copy
		std::vector<Order*> vectorlist = olist.getOrderList();
		for (int i = 0; i < vectorlist.size(); i++) {

			switch ((*vectorlist.at(i)).getOrderType()) {
			case OrderType::Deploy:
				this->orderList.push_back(new DeployOrder(*vectorlist.at(i)));
				break;
			case OrderType::Advance:
				this->orderList.push_back(new AdvanceOrder(*vectorlist.at(i)));
				break;
			case OrderType::Bomb:
				this->orderList.push_back(new BombOrder(*vectorlist.at(i)));
				break;
			case OrderType::Blockade:
				this->orderList.push_back(new BlockadeOrder(*vectorlist.at(i)));
				break;
			case OrderType::Airlift:
				this->orderList.push_back(new AirliftOrder(*vectorlist.at(i)));
				break;
			case OrderType::Negotiate:
				this->orderList.push_back(new NegotiateOrder(*vectorlist.at(i)));
				break;
			}

		}
		cout << "AO - Copied OrdersList object successfully." << endl;
		return *this;
	};

	friend ostream& operator<<(ostream& output, const OrdersList& list) {
		std::vector<Order*> vectorlist = list.getOrderList();
		for (int i = 0; i < vectorlist.size(); i++) {
			output << vectorlist.at(i)->id << endl;
			output << vectorlist.at(i)->getName() << endl;
			output << vectorlist.at(i)->getDesc() << endl;
		}
		return output;
	};

};
