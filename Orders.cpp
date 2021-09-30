#include "Orders.h"
#include <iostream>

using namespace std; //make sure to add the "only compile this once" keyword

//Order default constructor
//OrdersList default constructor
//need guarding constructors (conditions for parameters)

//default constructor 
//copy constructor
//assignment operator
//desctructor

//default constructor 
OrdersList::OrdersList() {

}
OrdersList::~OrdersList() {
	for (Order* order : orderList) { 
		delete order; 
		order = nullptr;
	}
	orderList.clear();
}
//copy constructor
OrdersList::OrdersList(const OrdersList& olist) {
	std::vector<Order*> vectorlist = olist.getOrderList();
	for (int i = 0; i < vectorlist.size(); i++) {
		this->orderList.push_back(new Order(*vectorlist.at(i)));
	}
}

void OrdersList::addOrder(Order* order) {
	this->orderList.push_back(order);
	cout << "Added order successfully." << endl;
};

void OrdersList::move(int toMove, int location) {//move index x to index y
	if (toMove < 1 || toMove > getOrderList().size() || location < 1 || location > getOrderList().size()) {
		cout << "Could not move order at " << toMove << " to " << location << "." << endl;
	}
	else {
		Order* moving = getOrderList().at(toMove);
		this->orderList.erase(orderList.begin() + toMove);
		this->orderList.insert(orderList.begin() + location, moving);
		cout << "Moved order at " << toMove << " to " << location << " successfully." << endl;
	}
};

void OrdersList::remove(int toRemove) {//remove index x 
	if (toRemove < 1 || toRemove > getOrderList().size()) {
		cout << "Could not remove order at " << toRemove << endl;
	}
	else {
		Order* removing = getOrderList().at(toRemove);
		delete removing;
		removing = nullptr;
		this->orderList.erase(orderList.begin() + toRemove);
		cout << "Removed order at " << toRemove << " successfully." << endl;
	}
};

//default constructor 
Order::Order() {//nothing?
	id = 0;
}
Order::Order(int test) {
	this->id = test;
}
Order::~Order() { }
//copy constructor
Order::Order(const Order &order) {
	this->id = order.id;
}

//DeployOrder constructor with filling members of Order
DeployOrder::DeployOrder() : Order(0)  {
	//deliberately empty
}
//Constructor
DeployOrder::DeployOrder(int theId) : Order(theId) {
	//deliberately empty
}
DeployOrder::~DeployOrder() {  }
//copy constructor
DeployOrder::DeployOrder(const DeployOrder& order) {
	this->id = order.id; // call order copy constructor
}

//dummy validation for now
bool DeployOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}

void DeployOrder::execute() {
	bool canExecute = validate();

	cout << "Executing " << this->getName() << "..." << endl;
	if (!canExecute) {
		cout << "This execution is invalid. Skipping this Order." << endl;
		return;
	}
	else {
		//execution occurs...

		cout << "This execution was successful!" << endl;
	}
}
