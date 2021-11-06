#include "Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*COMP 345 Section D - Assignment #2
* Fall 2021
* Due November 12th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/

class Cards;
class Order;
class OrderList;
//Stream insertions:


istream& operator>>(istream& in, Player& p)
{
	in >> p.name;
	return in;
}



ostream& operator<<(ostream& out, const Player& p)
{
	out << "Player: " << p.name << endl;
	out << "ID: " << p.playerID << endl;
	out << "Armies Held: " << p.armiesHeld << endl;
	out << "Territories owned: " << endl;
	for (Territory* i : p.towned) {
		out << *i;
	}
	out << endl;
	out << "Cards owned: " << endl;
	out << *(p.playerHand);
	out << endl;
	out << "Orders issued: " << endl;
	out << *(p.orders);
	return out;
}


int Player::playersCreated = 0;

//Constructors:
Player::Player(void)
{
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	playersCreated++;
	name = "Default";
	armiesHeld = 0;
	playerID = playersCreated;
	orders = new OrdersList();
	playerHand = new Hand();
}

Player::Player(const Player& other)
{
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	playersCreated++;
	name = other.name;
	armiesHeld = other.armiesHeld;
	playerID = other.playerID;
	for (auto p : other.towned) {
		Territory* temp = new Territory(*p);
		towned.push_back(temp);

	}
	playerHand = new Hand();
	for (auto p : other.cards) {
		Card* temp = new Card(*p);
		playerHand->addCard(temp);

	}
	orders = new OrdersList(*other.orders);

}

//Destructor:
Player::~Player() {
	cout << "Player " << this->getName() << " will now be destroyed." << endl;
	if (orders != NULL) {
		delete orders;
	}

	cout << "Player " << this->getName() << "'s Territories will now be destroyed." << endl;
	for (auto p : towned) {
		delete p;
	}
	cout << "Player " << this->getName() << "'s Cards will now be destroyed." << endl;
	for (auto p : cards) {
		delete p;
	}

	towned.clear();
	cards.clear();

}

//Assignment operators:
Player& Player::operator =(const Player& other) {
	cout << "A new Player of ID " << playersCreated << " was created." << endl;
	name = other.name;
	playerID = other.playerID;
	armiesHeld = other.armiesHeld;
	for (Territory* p : other.towned) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	playerHand = new Hand();
	for (auto p : other.cards) {
		Card* temp = new Card(*p);
		playerHand->addCard(temp);

	}
	orders = new OrdersList(*other.orders);

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
void Player::setArmiesHeld(int x)
{
	this->armiesHeld = x;
}
void Player::setTOwned(vector<Territory*> const& other)
{
	towned = other;
}

void Player::setCards(vector<Card*>& cards)
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
int Player::getArmiesHeld(void) {
	return armiesHeld;
}
vector<Territory*> Player::getTowned(void) {
	return towned;
}
vector<Card*> Player::getCards(void) {
	return cards;
}

OrdersList* Player::getOrders(void) {
	return orders;
}

vector<Player*> Player::getCantAttack() {
	return cannotAttack;
}

// From Cards: 

vector<Card*> Player::getHandOfCards() {
	return this->playerHand->getHandOfCards();
}

Hand* Player::getPlayerHand() {
	return playerHand;
}

void Player::addTerritory(Territory* ter) {
	ter->setOwner(this);
	towned.push_back(ter);
}

//From Cards:
void Player::addCard(Card* card) {
	playerHand->addCard(card);
}
void Player::addOrder(Order* order) {
	orders->addOrder(order);
}
//Gameplay mechanics:

vector<Territory*> Player::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense;
	for (auto t : towned) {
		defense.push_back(t);
	}
	sort(defense.begin(), defense.end());

	return defense;
}

vector<Territory*> Player::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack;
	for (auto t : towned) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != this) {
					attack.push_back(d);
				}

			}

		}
	}
	sort(attack.begin(), attack.end());
	return attack;
}
void Player::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following commands are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player�s territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player�s territories(source) to an adjacent territory." << endl;
	cout << "TARGET: If the target territory belongs to the current player, the armies are moved to the target.\nIf the target territory belongs to another player, an attack happens between the two territories." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent�s territory that is adjacent to one of the current player�s territories." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player�s territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current playerand another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;

	cout << *getPlayerHand();
}

Order* Player::discoverOrderType(string x) {
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();

	string options[] = { "reinforcement", "advance", "bomb", "blockade", "airlift", "diplomacy", "unspecified" };
	Order* newOrder;
	//Create the correct order based on command:
	if (x.compare(options[0]) == 0) { //Deployment orders and reinforcement.
		cout << "You have issued a deploy order." << endl;
		cout << "Territories available to defend:" << endl;
		for (auto t : defend) {
			cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
		}
		cout << "Territory to defend:" << defend[0]->getTerritoryName() << endl;
		cout << "How many armies would you like to deploy there?" << endl;
		int armiesToPlace;
		cin >> armiesToPlace;
		if (armiesHeld <= 0) {
			cout << "Player does not own enough armies to deploy to a new territory." << endl;
			newOrder = NULL;

		}
		if (armiesToPlace <= armiesHeld) {
			newOrder = new DeployOrder();
			newOrder->setOwner(this);
			newOrder->setTarget(defend[0]);
			newOrder->setModifier(armiesToPlace);
			armiesHeld -= armiesToPlace;

		}
		else {
			cout << "Only the remaining armies will be deployed." << endl;
			newOrder = new DeployOrder();
			newOrder->setOwner(this);
			newOrder->setTarget(defend[0]);
			newOrder->setModifier(armiesHeld);
			armiesHeld = 0;

		}



	}
	else if (x.compare(options[1]) == 0) { //Still requires the moving from current to target mechanism
		cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
		string cmd;
		cin >> cmd;
		while (cmd != "attack" && cmd != "defend") {
			cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
			cin >> cmd;
		}
		if (cmd == "attack") {
			cout << "Territories available to attack: " << endl;
			for (auto t : attack) {
				cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
			}
			cout << "Territory to advance upon:" << attack[0]->getTerritoryName() << endl;
			cout << "How many armies would you like to deploy there?" << endl;
			int armiesToPlace;
			cin >> armiesToPlace;
			static_cast<AdvanceOrder*>(newOrder);
			newOrder = new AdvanceOrder();
			newOrder->setOwner(this);
			newOrder->setTarget(attack[0]);
			newOrder->setModifier(armiesToPlace);	//Advance set to attack mode
		}
		else {
			cout << "Territory to defend:" << defend[0]->getTerritoryName() << endl;
			newOrder = new AdvanceOrder();
			newOrder->setOwner(this);
			newOrder->setTarget(defend[0]);
			newOrder->setModifier(1); //Advance set to defend mode
		}


	}
	else if (x.compare(options[2]) == 0) {
		cout << "You have issued a bomb order." << endl;
		cout << "Territories available to attack: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Territory to bomb:" << attack[0]->getTerritoryName() << endl;
		cout << "How many armies would you like to deploy there?" << endl;
		int armiesToPlace;
		cin >> armiesToPlace;
		newOrder = new BombOrder();
		newOrder->setOwner(this);
		newOrder->setTarget(attack[0]);
		newOrder->setModifier(armiesToPlace);

	}
	else if (x.compare(options[3]) == 0) {
		cout << "You have issued a blockade order. Please indicate which of the territories you would like to block:" << endl;
		cout << "Territories available to blockade:" << endl;
		for (auto t : defend) {
			cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
		}
		cout << "Territory to block:" << defend[0]->getTerritoryName() << endl;
		int armiesToPlace = defend[0]->getArmiesPlaced() * 2;
		newOrder = new BlockadeOrder();
		newOrder->setOwner(this);
		newOrder->setTarget(defend[0]);
		newOrder->setModifier(armiesToPlace);

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order. Please indicate which of the territories you would like to attack:" << endl;
		cout << "Territories available to airlift to:" << endl;
		for (auto t : defend) {
			cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
		}
		cout << "Territory to airlift to:" << defend[0]->getTerritoryName() << endl;
		newOrder = new AirliftOrder();
		newOrder->setOwner(this);
		newOrder->setTarget(defend[0]);
	}
	else if (x.compare(options[5]) == 0) {
		cout << "You have issued a negotiate order. Please indicate which of the territories you would like to attempt diplomacy with:" << endl;
		cout << "Territories available to negotiate with: " << endl;
		for (auto t : attack) {
			cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
		}
		cout << "Valid territory:" << attack[0]->getTerritoryName() << endl;

		newOrder = new NegotiateOrder();
		newOrder->setOwner(this);
		newOrder->setTarget(attack[0]);

	}
	else {
		newOrder = NULL;
	}

	return newOrder;
}

void Player::issueOrder()
{
	Order* issued;
	string x;
	Card* played;

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	cout << "Territories available to defend:" << endl;
	for (auto t : defend) {
		cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
	}

	cout << "Territories available to attack: " << endl;
	for (auto t : attack) {
		cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
	}

	if (armiesHeld > 0) { //Deployment phase.
		cout << "Player must deploy armies." << endl;
		cout << "Armies held: " << armiesHeld << endl;
		issued = discoverOrderType("reinforcement");
	}
	else { //Attack and Card phase.
		printOrderList();
		cout << "*0* - ATTACK" << endl;
		cout << "Please select a card to play (type the correct integer)." << endl;
		int index;
		cin >> index;
		if (index == 0) {
			x = "advance";
			played = new Card();
		}
		else {
			played = getPlayerHand()->getHandOfCards()[index - 1];
			x = played->orderType();
		}


		vector<string> options2;
		for (auto name : getPlayerHand()->getHandOfCards()) {	//Check which commands are available based on player's hand of cards
			if (name->getType() == 0) {
				options2.push_back("bomb");
			}
			else if (name->getType() == 1) {
				options2.push_back("reinforcement");
			}
			else if (name->getType() == 2) {
				options2.push_back("blockade");
			}
			else if (name->getType() == 3) {
				options2.push_back("airlift");
			}
			else if (name->getType() == 4) {
				options2.push_back("diplomacy");
			}

		}
		options2.push_back("advance");
		if (!(find(options2.begin(), options2.end(), x) != options2.end())) {	//If the player does not have the necessary card to issue to requested order, return null
			cout << "The command you requested is not available at the time. " << endl;
			issued = NULL;
		}
		else {
			// Issue the order:

			issued = discoverOrderType(x);
			if (index != 0) {
				//Remove correspondent card if order was issued through a card.
				played->play(this);

			}

		}
	}


	if (issued == NULL) {
		cout << "Invalid Order. Could not add it to the list." << endl;
	}
	else {
		orders->addOrder(issued);
		cout << "Order was issued: " << issued->getName() << endl;

		cout << "Current Player orders: " << endl;
		for (auto p : orders->getOrderList()) {
			cout << *p;
		}
	}
}


template <typename T>
void printVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << endl;
	}
}