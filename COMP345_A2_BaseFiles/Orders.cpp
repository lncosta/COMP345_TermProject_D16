#include "Orders.h"
#include <iostream>
using namespace std; //make sure to add the "only compile this once" keyword

/*
	OrdersList Default Constructor
*/
OrdersList::OrdersList() {

}

/*
	OrdersList Destructor
*/
OrdersList::~OrdersList() {
	for (Order* order : orderList) {
		delete order;
		order = nullptr;
	}
	orderList.clear();
}
/*
	OrdersList Copy Constructor
*/
OrdersList::OrdersList(const OrdersList& olist) {
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
	cout << "CC - Copied OrdersList object successfully." << endl;
}
/*
	Orderlist Assignment Operator
*/
OrdersList& OrdersList::operator=(const OrdersList& olist) //olist is rhs
{
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
			orderList.push_back(new DeployOrder(*vectorlist.at(i)));
			break;
		case OrderType::Advance:
			orderList.push_back(new AdvanceOrder(*vectorlist.at(i)));
			break;
		case OrderType::Bomb:
			orderList.push_back(new BombOrder(*vectorlist.at(i)));
			break;
		case OrderType::Blockade:
			orderList.push_back(new BlockadeOrder(*vectorlist.at(i)));
			break;
		case OrderType::Airlift:
			orderList.push_back(new AirliftOrder(*vectorlist.at(i)));
			break;
		case OrderType::Negotiate:
			orderList.push_back(new NegotiateOrder(*vectorlist.at(i)));
			break;
		}

	}
	cout << "AO - Copied OrdersList object successfully." << endl;
	
	return *this;
};
/*
	OrdersList addOrder function
	It allows us to add a derived order object to the list of orders.
	-Parameters-
	Order* order: an Order pointer to add to the list.
*/
void OrdersList::addOrder(Order* order) {
	this->orderList.push_back(order);
	cout << "Added order successfully." << endl;
};
/*
	OrdersList move function
	It allows us to move an order in the list of orders to a new position.
	-Parameters-
	int toMove: the index of the order we want to move its position in the list.
	int location: the index of the position in the list we want to place this order to.
*/
void OrdersList::move(int toMove, int location) {
	if (toMove < 0 || toMove > getOrderList().size() - 1 || location < 0 || location > getOrderList().size() - 1) {
		cout << "Could not move order at " << toMove << " to " << location << "." << endl;
	}
	else {
		Order* moving = getOrderList().at(toMove);
		this->orderList.erase(orderList.begin() + toMove);
		this->orderList.insert(orderList.begin() + location, moving);
		cout << "Moved order at " << toMove << " to " << location << " successfully." << endl;
	}
};
/*
	OrdersList remove function
	It allows us to remove an order from the list of orders.
	-Parameters-
	int toRemove: the index of the order we want to remove from the list.
*/
void OrdersList::remove(int toRemove) {
	if (toRemove < 0 || toRemove > getOrderList().size() - 1) {
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

/*
	Order Default Constructor
*/
int Order::count = 1;
Order::Order() {
	count++;
	id = count;
}
/*
	Order Constructor overloading with Id
	-Parameters-
	int setId: the id to give to this order
*/
Order::Order(int setId) {
	count++;
	this->id = setId;
}
/*
	Order Destructor
*/
Order::~Order() { }
/*
	Order Copy Constructor
*/
Order::Order(const Order& order) {
	this->id = order.id;
}
/*
	Order Assignment Operator
*/
Order& Order::operator=(const Order& order) {
	this->id = order.id;
	return *this;
};


/*
	DeployOrder Default Constructor
*/
DeployOrder::DeployOrder() : Order(count) { /* deliberately empty */ }
/*
	DeployOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
DeployOrder::DeployOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	DeployOrder Destructor
*/
DeployOrder::~DeployOrder() {  }
/*
	DeployOrder Copy Constructor
*/
DeployOrder::DeployOrder(const DeployOrder& order) {
	this->id = order.id;
}
/*
	DeployOrder Assignment Operator
*/
DeployOrder& DeployOrder::operator=(const DeployOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	DeployOrder Constructor Overloading for passing a base class to the derived class.
*/
DeployOrder::DeployOrder(const Order& order) {
	this->id = order.id;
}
/*
	DeployOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool DeployOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	DeployOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
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

/*
	AdvanceOrder Default Constructor
*/
AdvanceOrder::AdvanceOrder() : Order(count) { /* deliberately empty */ }
/*
	AdvanceOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
AdvanceOrder::AdvanceOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	AdvanceOrder Destructor
*/
AdvanceOrder::~AdvanceOrder() {  }
/*
	AdvanceOrder Copy Constructor
*/
AdvanceOrder::AdvanceOrder(const AdvanceOrder& order) {
	this->id = order.id;
}
/*
	AdvanceOrder Assignment Operator
*/
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	AdvanceOrder Constructor Overloading for passing a base class to the derived class.
*/
AdvanceOrder::AdvanceOrder(const Order& order) {
	this->id = order.id;
}
/*
	AdvanceOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool AdvanceOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	AdvanceOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void AdvanceOrder::execute() {
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

/*
	BombOrder Default Constructor
*/
BombOrder::BombOrder() : Order(count) { /* deliberately empty */ }
/*
	BombOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
BombOrder::BombOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	BombOrder Destructor
*/
BombOrder::~BombOrder() {  }
/*
	BombOrder Copy Constructor
*/
BombOrder::BombOrder(const BombOrder& order) {
	this->id = order.id;
}
/*
	BombOrder Assignment Operator
*/
BombOrder& BombOrder::operator=(const BombOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	BombOrder Constructor Overloading for passing a base class to the derived class.
*/
BombOrder::BombOrder(const Order& order) {
	this->id = order.id;
}
/*
	BombOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool BombOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	BombOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void BombOrder::execute() {
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

/*
	BlockadeOrder Default Constructor
*/
BlockadeOrder::BlockadeOrder() : Order(count) { /* deliberately empty */ }
/*
	BlockadeOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
BlockadeOrder::BlockadeOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	BlockadeOrder Destructor
*/
BlockadeOrder::~BlockadeOrder() {  }
/*
	BlockadeOrder Copy Constructor
*/
BlockadeOrder::BlockadeOrder(const BlockadeOrder& order) {
	this->id = order.id;
}
/*
	BlockadeOrder Assignment Operator
*/
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	BlockadeOrder Constructor Overloading for passing a base class to the derived class.
*/
BlockadeOrder::BlockadeOrder(const Order& order) {
	this->id = order.id;
}
/*
	BlockadeOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool BlockadeOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	BlockadeOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void BlockadeOrder::execute() {
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

/*
	AirliftOrder Default Constructor
*/
AirliftOrder::AirliftOrder() : Order(count) { /* deliberately empty */ }
/*
	AirliftOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
AirliftOrder::AirliftOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	AirliftOrder Destructor
*/
AirliftOrder::~AirliftOrder() {  }
/*
	AirliftOrder Copy Constructor
*/
AirliftOrder::AirliftOrder(const AirliftOrder& order) {
	this->id = order.id;
}
/*
	AirliftOrder Assignment Operator
*/
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	AirliftOrder Constructor Overloading for passing a base class to the derived class.
*/
AirliftOrder::AirliftOrder(const Order& order) {
	this->id = order.id;
}
/*
	AirliftOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool AirliftOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	AirliftOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void AirliftOrder::execute() {
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

/*
	NegotiateOrder Default Constructor
*/
NegotiateOrder::NegotiateOrder() : Order(count) { /* deliberately empty */ }
/*
	NegotiateOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
NegotiateOrder::NegotiateOrder(int theId) : Order(theId) { /* deliberately empty */ }
/*
	NegotiateOrder Destructor
*/
NegotiateOrder::~NegotiateOrder() {  }
/*
	NegotiateOrder Copy Constructor
*/
NegotiateOrder::NegotiateOrder(const NegotiateOrder& order) {
	this->id = order.id;
}
/*
	NegotiateOrder Assignment Operator
*/
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& order) {
	this->id = order.id;
	return *this;
};
/*
	NegotiateOrder Constructor Overloading for passing a base class to the derived class.
*/
NegotiateOrder::NegotiateOrder(const Order& order) {
	this->id = order.id;
}
/*
	NegotiateOrder validate function
	This is a dummy validation to validate whether the order can be executed or not.
*/
bool NegotiateOrder::validate() {
	if (this->id % 2 == 0)
		return true;
	if (this->id % 2 == 1)
		return false;
}
/*
	NegotiateOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void NegotiateOrder::execute() {
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

/*
	Stream insertions
*/
ostream& operator<<(ostream& output, const OrdersList& olist) {
	std::vector<Order*> vectorlist = olist.getOrderList();
	for (int i = 0; i < vectorlist.size(); i++) {
		output << vectorlist.at(i)->id << " - ";
		output << vectorlist.at(i)->getName() << endl;
		output << vectorlist.at(i)->getDesc() << endl;
	}
	return output;
};

ostream& operator<<(ostream& output, const Order& order) {
	output << order.id << " - " << order.getName() << "\n" << order.getDesc() << endl;
	return output;
};

ostream& operator<<(ostream& output, const DeployOrder& dorder) {
	output << dorder.id << " - " << dorder.getName() << "\n" << dorder.getDesc() << endl;
	return output;
}

ostream& operator<<(ostream& output, const AdvanceOrder& aorder) {
	output << aorder.id << " - " << aorder.getName() << "\n" << aorder.getDesc() << endl;
	return output;
}

ostream& operator<<(ostream& output, const BombOrder& border) {
	output << border.id << " - " << border.getName() << "\n" << border.getDesc() << endl;
	return output;
}

ostream& operator<<(ostream& output, const BlockadeOrder& border) {
	output << border.id << " - " << border.getName() << "\n" << border.getDesc() << endl;
	return output;
}

ostream& operator<<(ostream& output, const AirliftOrder& aorder) {
	output << aorder.id << " - " << aorder.getName() << "\n" << aorder.getDesc() << endl;
	return output;
}

ostream& operator<<(ostream& output, const NegotiateOrder& norder) {
	output << norder.id << " - " << norder.getName() << "\n" << norder.getDesc() << endl;
	return output;
}