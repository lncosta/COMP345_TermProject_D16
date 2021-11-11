#include "Orders.h"
#include <iostream>
using namespace std;

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
	stringToBeLogged = "Order Added: " + order->getName();
	Notify();
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
string OrdersList::stringToLog() {
	return stringToBeLogged;
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
Order::Order(int setId, Player* owner) {
	count++;
	this->id = setId;
	this->orderOwner = owner;
}
Order::Order(Player* owner) {
	count++;
	this->id = count;
	this->orderOwner = owner;
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
string Order::stringToLog() {
	return "unspecified order";
}

//**************** METHOD ************************
bool Order::isTerritoryMine(string territoryToFind) const {

	for (Territory* t : this->getOwner()->getTowned()) {
		if (t->getTerritoryName() == territoryToFind) return true;
	}
}
Territory* Order::findTerritory(string territoryToFind) const {

	for (Territory* t : this->getOwner()->getTowned()) {
		if (t->getTerritoryName() == territoryToFind) return t;
	}
}
//**************** Getter ************************
Player* Order::getOwner() const {
	return orderOwner;
}

Territory* Order::getTarget() const
{
	return target;
}

int Order::getModifier() const
{
	return modifier;
}

Territory* Order::getSource() const {
	return source;
}

void Order::setOwner(Player* owner)
{
	orderOwner = owner;
}

void Order::setTarget(Territory* target)
{
	this->target = target;
}

void Order::setSource(Territory* source)
{
	this->source = source;
}

void Order::setModifier(int modifier)
{
	this->modifier = modifier;
}



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

DeployOrder::DeployOrder(Player* owner) : Order(owner) {
	cout << "Player " << owner->getName() << " has declared a deploy order.\nEnter the source territory: ";
	cin >> sourceTerritory;
	cout << "What is the number of armies to be deployed: ";
	cin >> numberOfArmies;
	cout << "\nThe Order has been confirmed." << endl;
}
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
	int reinforcementPool = 100;
	bool armiesOK = (modifier <= reinforcementPool); // checking if the player's reinforcement pool has enough armies****************************************;
	bool sourceOK = false;
	//	sourceOK = this->isTerritoryMine(sourceTerritory); // checking if the player owns the source territory
	vector<Territory*> tOwned = orderOwner->getTowned();
	for (Territory* p : tOwned) {
		if (target == p)
			sourceOK = true;
	}
	return (sourceOK && armiesOK);
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
		cout << "DEBUG: DEPLOY ORDER IN EXECUTION" << endl;
		cout << "DEBUG: TARGET TERRITORY IS " << target->getTerritoryName() << endl;
		int sourceArmies = target->getArmiesPlaced();

		target->setArmiesPlaced(sourceArmies + modifier);
		cout << "DEBUG: THE TERRITORY NOW HAS " << target->getArmiesPlaced() << " ARMIES ON IT" << endl;

		cout << "This execution was successful!" << endl;
		Notify();
	}
}
/*
	DeployOrder logging function.
*/
string DeployOrder::stringToLog() {
	return "Order Executed: Deploy\nDeploy: " + getDesc();
}


/*
	AdvanceOrder Default Constructor
*/
AdvanceOrder::AdvanceOrder() : Order(count) {

}
/*
	AdvanceOrder Constructor overloading with id.
	-Parameters-
	int theId: the id to give to this order
*/
AdvanceOrder::AdvanceOrder(int theId, Player* calledOrder) : Order(theId) {
	orderOwner = calledOrder;
	cout << "Player " << calledOrder->getName() << " has declared an Advance order.";
	cout << "\nHow Many Armies Would You Like to Move: ";
	cin >> armiesToMove;
	cout << "\nThe Order has been confirmed." << endl;


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
	string name = getSource()->getTerritoryName();
	for (Territory* p : playerOwnedT) {
		if (p->getTerritoryName() == name) {
			sourceBelongsToPlayer = true;

			break;
		}
	}
	// Checking that the target is adjacent to the source
	vector<Territory*> adjT = getSource()->getAdjTerritories();
	for (Territory* p : adjT) {
		if (p->getTerritoryName() == getTarget()->getTerritoryName()) {
			targetIsAdjacent = true;
			break;
		}
	}
	if (getSource() != NULL && getSource()->getArmiesPlaced() < armyModifier)
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
	cout << "The Order is Valid: Proceeding with Execution" << endl;
	return true;
}
/*
	AdvanceOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void AdvanceOrder::execute() {											// Last Step is to Give the Player a card if they have conquered this turn
	cout << "Executing " << this->getName() << "..." << endl;
	cout << "DEBUG: ATTEMPTING TO VALIDATE" << endl;
	bool canExecute = validate();
	cout << "DEBUG: VALIDATION COMPLETED" << endl;

	if (!canExecute) {
		cout << "This execution is invalid. Skipping this Order." << endl;
		return;
	}
	else {
		//execution occurs...

		// If the Player is Moving Armies Between Their Territories
		if (getModifier() == 1) {
			int srcArmiesAfter = getSource()->getArmiesPlaced() - armyModifier;
			getSource()->setArmiesPlaced(srcArmiesAfter);
			int targetArmiesAfter = getTarget()->getArmiesPlaced() + armyModifier;
			getTarget()->setArmiesPlaced(targetArmiesAfter);
		}
		// If the Player is Attacking Another
		else {
			// Checking that a Negotiate order is not active
			for (Player* p : this->getOwner()->getCantAttack()) {
				if (getTarget()->getOwner() == p) {
					cout << "There is a Negotiate Order Active Between the Two Players. The Attack has been Canceled." << endl;
					return;
				}
			}
			// Loop continues as long as there are attackers left
			while (armyModifier > 0) {
				// At the beginnings check if defenders are still standing, covers the case where there are no defenders
				if (getTarget()->getArmiesPlaced() <= 0) {
					cout << "The Territory Has Been Conquered. The Remaining Attackers will be moved to it." << endl;
					this->getOwner()->setConquered(true);
					//Remove territory from original owner:
					(getTarget()->getOwner())->removeTerritory(getTarget());
					//Make territory transfer and move armies:
					getTarget()->setOwner(getOwner());
					getOwner()->addTerritory(getTarget());
					int srcArmiesAfter = getSource()->getArmiesPlaced() - armyModifier;
					getSource()->setArmiesPlaced(srcArmiesAfter);
					int targetArmiesAfter = getTarget()->getArmiesPlaced() + armyModifier;
					getTarget()->setArmiesPlaced(targetArmiesAfter);
					break;
				}

				int attackerRoll = (rand() % 10) + 1;
				int defenderRoll = (rand() % 10) + 1;
				// Checking if a defender gets killed
				if (attackerRoll <= 6) {
					getTarget()->setArmiesPlaced(getTarget()->getArmiesPlaced() - 1);
				}
				// Checking if an attacker gets killed
				if (defenderRoll <= 7) {
					armyModifier = armyModifier - 1;
				}
			}
		}
		cout << "This execution was successful!" << endl;
		Notify();
		return;
	}
}

/*
	AdvanceOrder logging function.
*/
Territory* AdvanceOrder::getSource()
{
	return sourceTerritory;
}
void AdvanceOrder::setSource(Territory* source)
{
	sourceTerritory = source;
}
string AdvanceOrder::stringToLog() {
	return "Order Executed: Advance\nAdvance: " + getDesc();
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
	orderOwner = nullptr;
	this->target = nullptr;
}
/*
	BombOrder validate function
*/
bool BombOrder::validate() {
	bool targetBelongsToPlayer = false;
	bool targetIsAdjacent = false;
	bool hasCard = false;

	// Check that the player owns the given card
	for (Card* c : this->getOwner()->getHandOfCards()) {
		if (c->getType() == 0) {
			this->getOwner()->getPlayerHand()->eraseCard(c);
			hasCard = true;
		}
	}
	// If the target belongs to the player that issued the order, the order is invalid.
	vector<Territory*> playerOwnedT = this->getOwner()->getTowned();
	for (Territory* p : playerOwnedT) {
		if (p == target) {
			targetBelongsToPlayer = true;
		}
	}
	// If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the order is invalid.
	vector<Territory*> adjT = getTarget()->getAdjTerritories();
	for (Territory* p : adjT) {
		if (p->getOwner() == getOwner())
			targetIsAdjacent = true;
	}

	if (targetBelongsToPlayer == true) {
		cout << "The Order is Invalid: The Target Territory is Owned By You. " << endl;
		return false;
	}
	else if (targetIsAdjacent == false) {
		cout << "The Order is Invalid: You Do Not Own A Territory Adjacent to the Target. " << endl;
		return false;
	}
	else if (hasCard == false) {
		cout << "The Order is Invalid: You Do Not Have a Bomb Card. " << endl;
		return false;
	}
	cout << "The Order is Valid: Proceeding with Execution. ";
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
		int currentArmies = getTarget()->getArmiesPlaced();
		int newNumArmies = currentArmies / 2; // PLACEHOLDER
		getTarget()->setArmiesPlaced(newNumArmies);
		cout << "This execution was successful!" << endl;
		Notify();
	}
}
/*
	BombOrder logging function.
*/
string BombOrder::stringToLog() {
	return "Order Executed: Bomb\nBomb: " + getDesc();
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
BlockadeOrder::BlockadeOrder(Player* owner) : Order(owner) {
	cout << "Player " << owner->getName() << " has declared a blockade order.\nEnter the target territory: ";
	cin >> targetTerritory;
	cout << "\nThe Order has been confirmed." << endl;
}
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
	bool hasCard = false;
	bool targetOK = this->isTerritoryMine(target->getTerritoryName()); // checking if the player owns the target territory

	return targetOK;
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
		//Set army number to double:
		getTarget()->setArmiesPlaced(2 * getTarget()->getArmiesPlaced());
		// create a neutral player, give them the target territory and double the armies on it
		if (neutralPlayer == NULL) {
			neutralPlayer = new Player();
			neutralPlayer->setName("Neutral");
		}
		neutralPlayer->addTerritory(target);
		getOwner()->removeTerritory(target);

		cout << "The neutral player now owns this territory." << endl;
		cout << "This execution was successful!" << endl;
		//Notify();
	}
}
/*
	BlockadeOrder logging function.
*/
string BlockadeOrder::stringToLog() {
	return "Order Executed: Blockade\nBlockade: " + getDesc();
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
AirliftOrder::AirliftOrder(Player* owner) : Order(owner) {
	cout << "Player " << owner->getName() << " has declared an airlift order.\nEnter the source territory: ";
	cin >> sourceTerritory;
	cout << "What is the number of armies to be airlifted: ";
	cin >> numberOfArmies;
	cout << "Now enter the target territory: ";
	cin >> targetTerritory;
	cout << "\nThe Order has been confirmed." << endl;
}
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
*/
bool AirliftOrder::validate() {
	bool armiesOK = false;
	bool sourceOK = this->isTerritoryMine(sourceTerritory); // checking if the player owns the source territory
	bool targetOK = this->isTerritoryMine(targetTerritory); // checking if the player owns the target territory
	if (sourceOK) armiesOK = (numberOfArmies >= this->findTerritory(sourceTerritory)->getArmiesPlaced()); // checking if the source has enough armies

	return (sourceOK && targetOK && armiesOK);
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
		int sourceArmies = this->findTerritory(sourceTerritory)->getArmiesPlaced();
		int targetArmies = this->findTerritory(targetTerritory)->getArmiesPlaced();

		if (sourceArmies - numberOfArmies >= 0) {
			this->findTerritory(sourceTerritory)->setArmiesPlaced(sourceArmies - numberOfArmies);
			this->findTerritory(targetTerritory)->setArmiesPlaced(targetArmies + numberOfArmies);
		}
		else {
			// if number subtracted is less than 0, set to 0.
			this->findTerritory(sourceTerritory)->setArmiesPlaced(0);
			// so then we add only what is available from the sourceArmies
			this->findTerritory(targetTerritory)->setArmiesPlaced(targetArmies + sourceArmies);
		}

		cout << "This execution was successful!" << endl;
		Notify();
	}
}
/*
	AirliftOrder logging function.
*/
string AirliftOrder::stringToLog() {
	return "Order Executed: Airlift\nAirlift: " + getDesc();
}


/*
	NegotiateOrder Default Constructor
*/
NegotiateOrder::NegotiateOrder() : Order(count) {

}
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
	this->targetPlayer = order.targetPlayer;
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
	Player* targetPlayer = getTarget()->getOwner();
	// Checking that the Player who called the order isnt the target
	if (getOwner() == targetPlayer) {
		cout << "The Order is Invalid: You Cannot Negotiate with Yourself" << endl;
		return false;
	}

	cout << "The Order is Valid: Proceeding with Execution";
	return true;
}
/*
	NegotiateOrder execute function
	This method calls the validate function, then executes the order if it is validated or invalid.
*/
void NegotiateOrder::execute() {
	cout << "Executing " << this->getName() << "..." << endl;
	bool canExecute = validate();

	if (!canExecute) {
		cout << "This execution is invalid. Skipping this Order." << endl;
		return;
	}
	else {
		//execution occurs...
		Player* targetPlayer = getTarget()->getOwner();
		getOwner()->getCantAttack().push_back(targetPlayer);
		targetPlayer->getCantAttack().push_back(this->getOwner());
		cout << "This execution was successful!" << endl;

		Notify();
		return;

	}
}
/*
	NegotiateOrder logging function.
*/
string NegotiateOrder::stringToLog() {
	return "Order Executed: Negotiate\nNegotiate: " + getDesc();
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