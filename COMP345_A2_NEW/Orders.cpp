#include "Orders.h"
#include <iostream>
#include <fstream>
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
	OrdersList logging function.
*/
void OrdersList::stringToLog() {
	cout << "OrdersList will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "Orderslist log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
	}
}


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
	DeployOrder logging function.
*/
void DeployOrder::stringToLog() {
	cout << "DeployOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "DeployOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
AdvanceOrder::AdvanceOrder(int theId, Player* calledOrder) : Order(theId) { 
	orderOwner = calledOrder;
	cout << "Player " << calledOrder->getName() << " has declared an Advance order.\nEnter the source territory: ";
	cin >> sourceTerritory;
	cout << "\nEnter the target territory: ";
	cin >> targetTerritory;
	cout << "\nHow Many Armies Would You Like to Move: ";
	cin >> armiesToMove;
	cout << "\nThe Order has been confirmed." << endl;

	source = nullptr; // Will be assigned later
	target = nullptr; // Will be assigned later
}
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
	bool sourceBelongsToPlayer = false; 
	bool targetIsAdjacent = false;
	bool notEnoughArmies = false;
	
	// Checking that the player owns the source territory
	vector<Territory*> playerOwnedT = orderOwner->getTowned();
	for (Territory* p : playerOwnedT) {
		if (p->getTerritoryName() == sourceTerritory) {
			source = p;
			sourceBelongsToPlayer = true;
		}
	}
	// Checking that the target is adjacent to the source
	vector<Territory*> adjT = source->getAdjTerritories();
	for (Territory* p : adjT) {
		if (p->getTerritoryName() == targetTerritory) {
			target = p;
			targetIsAdjacent = true;
		}
	}
	if (source->getArmiesPlaced() < armiesToMove)
		notEnoughArmies = true;

	if (sourceBelongsToPlayer == false) {
		cout << "The Order is Invalid: The Source Territory is Not Owned By You" << endl;
		return false;
	}
	else if (targetIsAdjacent == false) {
		cout << "The Order is Invalid: The Target Territory is Not Adjacent to the Source" << endl;
		return false;
	}
	else if (notEnoughArmies == true) {		// Maybe Not a Case for Invalidity since not in document
		cout << "The Order is Invalid: The Source Territory Does Not Have Enough Armies to Move" << endl;
		return false;
	}
	cout << "The Order is Valid: Proceeding with Execution";
	return true;
	
}
/*
	AdvanceOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void AdvanceOrder::execute() {
	cout << "Executing " << this->getName() << "..." << endl;
	bool canExecute = validate();

	if (!canExecute) {
		cout << "This execution is invalid. Skipping this Order." << endl;
		return;
	}
	else {
		//execution occurs...
		// If the Player is Moving Armies Between Their Territories
		if (target->getOwner() == source->getOwner()) {
			int srcArmiesAfter = source->getArmiesPlaced() - armiesToMove;
			source->setArmiesPlaced(srcArmiesAfter);
			int targetArmiesAfter = target->getArmiesPlaced() + armiesToMove;
			target->setArmiesPlaced(targetArmiesAfter);
		}
		// If the Player is Attacking Another
		if (target->getOwner() != source->getOwner()) {

		}
		cout << "This execution was successful!" << endl;
	}
}
/*
	AdvanceOrder logging function.
*/
void AdvanceOrder::stringToLog() {
	cout << "AdvanceOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "AdvanceOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
BombOrder::BombOrder(int theId, Player* calledOrder) : Order(theId) { 
	orderOwner = calledOrder;
	cout << "Player " << calledOrder->getName() << " has declared a bomb order.\nEnter the target territory: ";
	cin >> targetTerritory;
	cout << "\nThe Order has been confirmed." << endl;
	target = nullptr; // Will be assigned later
}
/*
	BombOrder Destructor
*/
BombOrder::~BombOrder() {  }
/*
	BombOrder Copy Constructor
*/
BombOrder::BombOrder(const BombOrder& order) {
	this->id = order.id;
	this->orderOwner = order.orderOwner;
	this->target = order.target;
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
	this->orderOwner = nullptr;
	this->target = nullptr;
}
/*
	BombOrder validate function
*/
bool BombOrder::validate() {
	bool targetBelongsToPlayer = false;
	bool targetIsAdjacent = false;
	// If the target belongs to the player that issued the order, the order is invalid.
	vector<Territory*> playerOwnedT = orderOwner->getTowned();
	for (Territory* p : playerOwnedT) {
		if (p->getTerritoryName() == targetTerritory) {
			target = p;
			targetBelongsToPlayer = true;
		}
	}
	// If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the order is invalid.
	for (Territory* p : playerOwnedT) {
		vector<Territory*> adjT = p->getAdjTerritories();
		for (Territory* q : adjT) {
			if (q->getTerritoryName() == targetTerritory)
				targetIsAdjacent = true;
		}
	}

	if (targetBelongsToPlayer == true) {
		cout << "The Order is Invalid: The Target Territory is Owned By You" << endl;
		return false;
	}
	else if (targetIsAdjacent == false){
		cout << "The Order is Invalid: You Do Not Own A Territory Adjacent to the Target" << endl;
		return false;
	}
	cout << "The Order is Valid: Proceeding with Execution";
	return true;
}
/*
	BombOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void BombOrder::execute() {
	cout << "Executing " << this->getName() << "..." << endl;
	bool canExecute = validate();

	
	if (!canExecute) {
		cout << "This execution is invalid. Skipping this Order." << endl;
		return;
	}
	else {
		//execution occurs...
		int currentArmies = target->getArmiesPlaced();
		int newNumArmies = currentArmies/2; // PLACEHOLDER
		target->setArmiesPlaced(newNumArmies);
		cout << "This execution was successful!" << endl;
	}
}
/*
	BombOrder logging function.
*/
void BombOrder::stringToLog() {
	cout << "BombOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "BombOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
	BlockadeOrder logging function.
*/
void BlockadeOrder::stringToLog() {
	cout << "BlockadeOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "BlockadeOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
	AirliftOrder logging function.
*/
void AirliftOrder::stringToLog() {
	cout << "AirliftOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "AirliftOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
	NegotiateOrder logging function.
*/
void NegotiateOrder::stringToLog() {
	cout << "NegotiateOrder will write to file gamelog.txt here" << endl;

	ofstream filewriting;

	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << "NegotiateOrder log data" << endl; //call saveEffect here?
		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
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
