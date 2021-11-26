#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
using namespace std; 
Neutral::Neutral(): PlayerStrategy()
{
}
Neutral::Neutral(Player* player): PlayerStrategy(player)
{
}
void Neutral::issueOrder()
{
}

vector<Territory*> Neutral::toAttack()
{
	vector<Territory*> ret; 
	return ret;
}

vector<Territory*> Neutral::toDefend()
{
	vector<Territory*> ret;
	return ret;
}

Cheater::Cheater()
{
}

Cheater::Cheater(Player* player)
{
}

void Cheater::issueOrder()
{

}

vector<Territory*> Cheater::toAttack()
{
	vector<Territory*> ret;
	return ret;
}

vector<Territory*> Cheater::toDefend()
{
	vector<Territory*> ret;
	return ret;
}


//Returns territories owned by the player
vector<Territory*> Human::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense;
	for (auto t : p->towned) {
		defense.push_back(t);
	}
	//At a later development stage, priority will be determined using sorting and the player profile:
	//sort(defense.begin(), defense.end());

	//For testing purposes while priority definition is still not implemented, priority is set to random:
	std::shuffle(std::begin(defense), std::end(defense), rng);
	return defense;
}

//Returns territories not owned by the Player
vector<Territory*> Human::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack;
	for (auto t : p->towned) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != p) {
					attack.push_back(d);
				}

			}

		}
	}
	//At a later development stage, priority will be determined using sorting and the player profile:
	//sort(attack.begin(), attack.end());

	//For testing purposes while priority definition is still not implemented, priority is set to random:
	std::shuffle(std::begin(attack), std::end(attack), rng);
	return attack;
}

//Determines order target based on toDefend or toAttack methods
void Human::determineTarget(int state, Order* order) {
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	Territory* target;

	if (state == 1) { //Target is one of Player's own territories -> taken from toDefend()
		if (defend.size() == 0) {
			target = NULL;
			//Setting target information to the created order:
			order->setOwner(p);
			order->setTarget(target);
			return;
		}
		cout << "Territories available as a target:" << endl;
		int i = 1;
		for (auto t : defend) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (p->intelligent) {
			int index;
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (defend.size() >= index && index > 0) {
				cout << "Territory selected as target: " << defend[index - 1]->getTerritoryName() << endl;
				target = defend[index - 1];
			}
			else {
				cout << "Default territory selected as target: " << defend[0]->getTerritoryName() << endl;
				target = defend[0];
			}
		}
		else {	//Default target selection
			cout << "Default territory selected as target: " << defend[0]->getTerritoryName() << endl;
			target = defend[0];
		}


	}
	else {	//Target is one of the enemy territory -> taken from toAttack
		if (attack.size() == 0) {
			target = NULL;
			//Setting target information to the created order:
			order->setOwner(p);
			order->setTarget(target);
			return;
		}
		cout << "Territories available as a target: " << endl;
		int i = 1, index;
		for (auto t : attack) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced() << " - Owner: " << t->getOwner()->getName();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (p->intelligent) {
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (attack.size() >= index && index > 0) {
				cout << "Territory selected as target: " << attack[index - 1]->getTerritoryName() << endl;
				target = attack[index - 1];
			}
			else {
				cout << "Default territory selected as target: " << attack[0]->getTerritoryName() << endl;
				target = attack[0];
			}
		}
		else {
			cout << "Default territory selected as target: " << attack[0]->getTerritoryName() << endl;
			target = attack[0];
		}

	}

	//Setting target information to the created order:
	order->setOwner(p);
	order->setTarget(target);
}
//Determines order source based on toDefend method
void Human::determineSource(int state, Order* order) {
	vector<Territory*> defend = toDefend();
	Territory* target = order->getTarget();
	Territory* source = NULL;
	if (defend.size() == 0) {
		source = NULL;
		//Setting target information to the created order:
		order->setSource(source);
		return;
	}
	if (target != NULL) {
		cout << "Territories available as a source:" << endl;
		int i = 1;
		for (auto t : defend) {
			cout << i << " - " << t->getTerritoryName() << " - Army count: " << t->getArmiesPlaced();
			cout << " - Adjacent to: ";
			t->printAdjTerritories();
			i++;
		}
		if (p->intelligent) {
			int index;
			cout << "Please select one of the territories above by typing their index value: " << endl;
			cin >> index;
			if (defend.size() >= index && index > 0) {
				cout << "Territory selected as source:" << defend[index - 1]->getTerritoryName() << endl;
				source = defend[index - 1];
			}
			else {
				cout << "Default territory selected as target:" << defend[0]->getTerritoryName() << endl;
				source = defend[0];
			}
		}
		else {	//Default source selection
			cout << "Default territory selected as target:" << defend[0]->getTerritoryName() << endl;
			source = defend[0];
		}

	}
	order->setSource(source);

}
//Prints standard order information as well as player's hand
void Human::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following orders are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player's territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player's territories(source) to an adjacent territory." << endl;
	cout << "TARGET: If the target territory belongs to the current player, the armies are moved to the target.\nIf the target territory belongs to another player, an attack happens between the two territories." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player's territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current player and another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;

	cout << p->getPlayerHand();
}
//Sets the number of armies to be deployed
int Human::deployArmies(void) {
	if (!p->intelligent) {
		return 10;
	}
	cout << "Please indicate how many armies you would like to attempt to deploy:" << endl;
	int x;
	cin >> x;
	if (x >= 1) {
		return x;
	}
	else {
		return 1;
	}
}

//3.2.4 A player can create any kind of order, inlcuding those that can only be created using cards.
//Given a string, issue the corresponding order
Order* Human::discoverOrderType(string x) {
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();

	string options[] = { "reinforcement", "advance", "bomb", "blockade", "airlift", "diplomacy", "unspecified" };
	Order* newOrder;
	//Create the correct order based on command:
	if (x.compare(options[0]) == 0) { //Deployment orders and reinforcement.
		cout << "You have issued a deploy order." << endl;
		if (p->armiesHeld <= 0) {
			cout << "Player does not own enough armies to deploy to a new territory." << endl;
			newOrder = NULL;
			return newOrder;

		}
		if (toDefend().size() == 0) {
			cout << "Player does not own a territory." << endl;
			newOrder = NULL;
			return newOrder;
		}
		newOrder = new DeployOrder();
		determineTarget(1, newOrder);
		int armiesToPlace = deployArmies();

		if (armiesToPlace <= p->armiesHeld) {
			newOrder->setModifier(armiesToPlace);
			newOrder->armyModifier = armiesToPlace;
			p->armiesHeld -= armiesToPlace;

		}
		else {
			cout << "Only the remaining armies will be deployed." << endl;
			newOrder->setModifier(p->armiesHeld);
			newOrder->armyModifier = p->armiesHeld;
			p->armiesHeld = 0;

		}
	}
	else if (x.compare(options[1]) == 0) { //Still requires the moving from current to target mechanism
		string cmd;
		if (!p->intelligent) {
			cmd = "attack";
		}
		else {
			cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
			cin >> cmd;
			while (cmd != "attack" && cmd != "defend") {
				cout << "You have issued an advance order. Please indicate whether you would like to attack another player's territory or defend one of your own:" << endl;
				cin >> cmd;
			}
		}

		if (cmd == "attack") {
			newOrder = new AdvanceOrder();
			newOrder->setOwner(p);
			determineTarget(0, newOrder);
			determineSource(0, newOrder);
			newOrder->setModifier(0);	//Advance set to attack mode
			newOrder->armyModifier = deployArmies();

		}
		else {
			newOrder = new AdvanceOrder();
			newOrder->setOwner(p);
			determineTarget(1, newOrder);
			determineSource(1, newOrder);
			newOrder->setModifier(1); //Advance set to defend mode
			newOrder->armyModifier = deployArmies();
		}


	}
	else if (x.compare(options[2]) == 0) {
		cout << "You have issued a bomb order." << endl;
		newOrder = new BombOrder();
		newOrder->setOwner(p);
		determineTarget(0, newOrder);
		newOrder->setModifier(0);

	}
	else if (x.compare(options[3]) == 0) {
		cout << "You have issued a blockade order:" << endl;
		newOrder = new BlockadeOrder();
		newOrder->setOwner(p);
		determineTarget(1, newOrder);
		newOrder->setModifier(0);
		newOrder->neutralPlayer = p->neutral;

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order." << endl;
		newOrder = new AirliftOrder();
		newOrder->setOwner(p);
		determineTarget(1, newOrder);
		determineSource(1, newOrder);
		newOrder->armyModifier = deployArmies();
	}
	else if (x.compare(options[5]) == 0) {
		cout << "You have issued a negotiate order. Please indicate which of the territories you would like to attempt diplomacy with:" << endl;
		newOrder = new NegotiateOrder();
		newOrder->setOwner(p);
		determineTarget(0, newOrder);

	}
	else {
		newOrder = NULL;
	}

	return newOrder;
}

Human::Human():PlayerStrategy()
{
}

Human::Human(Player* player): PlayerStrategy(player)
{
}

//Issues a order for the Player
void Human::issueOrder()
{
	Order* issued;
	string x;
	Card* played;
	LogObserver* orderObserver = new LogObserver(p->orders);
	int index = 0;

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	cout << "----------------------------------" << endl;
	cout << "Territories available to defend:" << endl;
	for (auto t : defend) {
		cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "Territories available to attack: " << endl;
	for (auto t : attack) {
		cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
	}
	cout << "----------------------------------" << endl;
	if (p->armiesHeld > 0 && toDefend().size() > 0) { //Deployment phase.

		cout << "Player must deploy armies." << endl;
		cout << "Armies held: " << p->armiesHeld << endl;
		issued = discoverOrderType("reinforcement");
	}
	else { //Attack and Card phase.
		printOrderList();
		cout << "0 - ADVANCE" << endl;
		if (!p->intelligent) {

			if (p->getHandOfCards().size() < 1) {
				x = "advance";
				played = new Card();
			}
			else {
				index = 1 + (rand() % static_cast<int>(p->getHandOfCards().size() - 1 + 1));
				played = p->getPlayerHand()->getHandOfCards()[index - 1];
				x = played->orderType();
			}
		}
		else {
			cout << "Please select a card to play (type the correct integer)." << endl;

			cin >> index;
			// If the given index is out of range, an advance order is issued by default
			if (index == 0 || index < 0 || index > p->getPlayerHand()->getHandOfCards().size()) {
				x = "advance";
				played = new Card();
			}
			else {
				played = p->getPlayerHand()->getHandOfCards()[index - 1];
				x = played->orderType();
			}
		}

		vector<string> options2;
		for (auto name : p->getPlayerHand()->getHandOfCards()) {	//Check which commands are available based on player's hand of cards
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
				played->play(p);

			}

		}
	}


	if (issued == NULL) {
		cout << "Invalid Order. Could not add it to the list." << endl;
	}
	else { //Add order to OrdersList
		p->orders->addOrder(issued);
		cout << "Order was issued: " << issued->getName() << endl;

		cout << "Current Player orders: " << endl;
		for (auto p : p->orders->getOrderList()) {
			cout << *p;
		}
	}
	cout << "----------------------------------" << endl;
	delete orderObserver;
	orderObserver = nullptr;
}
Aggressive::Aggressive()
{
}
Aggressive::Aggressive(Player* player)
{
}
void Aggressive::issueOrder()
{
}

vector<Territory*> Aggressive::toAttack()
{
	vector<Territory*> ret;
	return ret;
}

vector<Territory*> Aggressive::toDefend()
{
	vector<Territory*> ret;
	return ret;
}

Benevolent::Benevolent()
{
}

Benevolent::Benevolent(Player* player)
{
}

void Benevolent::issueOrder()
{
}

vector<Territory*> Benevolent::toAttack()
{
	vector<Territory*> ret;
	return ret;
}

vector<Territory*>Benevolent::toDefend()
{
	vector<Territory*> ret;
	return ret;
}

PlayerStrategy::PlayerStrategy()
{
	p = NULL; 
}

PlayerStrategy::PlayerStrategy(Player* player)
{
	p = player;
}

PlayerStrategy::~PlayerStrategy()
{
	p = NULL; 
}

void PlayerStrategy::setPlayer(Player* player)
{
	p = player;
}

Player* PlayerStrategy::getPlayer(void)
{
	return p;
}