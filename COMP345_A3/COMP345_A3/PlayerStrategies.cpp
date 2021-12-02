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
Neutral::Neutral() : PlayerStrategy()
{
}
Neutral::Neutral(Player* player) : PlayerStrategy(player)
{
}
void Neutral::issueOrder()
{
	cout << "The Neutral Player cannot issue any orders." << endl;
	p->doneIssuingOrders = true;
}
Order* Neutral::discoverOrderType(string x) {
	Order* newOrder = nullptr;
	return newOrder;
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

Cheater::Cheater(Player* player) : PlayerStrategy(player)
{
}
Order* Cheater::discoverOrderType(string x) {
	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	string options[] = { "reinforcement", "advance", "bomb", "blockade", "airlift", "diplomacy", "unspecified" };
	Order* newOrder = nullptr;
	
	//Since the cheater only issues one type of order, we do not need to call this method to figure out the type.

	return newOrder;
}

//Prints standard order information as well as player's hand
void Cheater::printOrderList(void) {
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
// deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore
void Cheater::issueOrder()
{
	Order* issued;
	Card* played;
	LogObserver* orderObserver = new LogObserver(p->orders);

	vector<Territory*> defend = this->toDefend();
	vector<Territory*> attack = this->toAttack();
	
	cout << "----------------------------------" << endl;
	cout << "Cheater will now advance on all adjacent enemy territories." << endl;
	//cout << "DEBUG: CHEATER - ATTACK SIZE: " << attack.size() << endl;
	//cout << "DEBUG: CHEATER - DEFEND SIZE: " << defend.size() << endl;
	for (Territory* pt : attack) { //Adding advance orders for all adjacent territories
		// Issue the order:
		if (attack.size() > 0 && defend.size() > 0) {
			issued = new AdvanceOrder();
			issued->setOwner(p);
			issued->setTarget(pt);
			issued->setSource(defend.front());
			//cout << "DEBUG: CHEATER - TARGET " << (*pt).getTerritoryName() << endl;
			//cout << "DEBUG: CHEATER - SOURCE " << (*defend.back()).getTerritoryName() << endl;
			issued->setModifier(0);	//Advance set to attack mode
			issued->armyModifier = 1000; // Huge number of armies so that it can conquer any territory 
		}
		else {
			issued = nullptr;
		}

		if (issued == nullptr) {
			cout << "Invalid Order. Could not add it to the list." << endl;
			p->doneIssuingOrders = true;
		}
		else { //Add order to OrdersList
			p->orders->addOrder(issued);
			cout << "Order was issued: " << issued->getName() << endl;
		}
	}

	cout << "Current Player orders: " << endl;
	for (auto p : p->orders->getOrderList()) {
		cout << *p;
	}

	cout << "----------------------------------" << endl;
	delete orderObserver;
	orderObserver = nullptr;
	p->doneIssuingOrders = true;
}


vector<Territory*> Cheater::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack;
	for (auto t : p->towned) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != p ) { 
					attack.push_back(d);
				}

			}

		}
	}

	// Now the vector is sorted from best to worst target, uses the overloaded < operator from Map file
	sort(attack.begin(), attack.end());

	return attack;
}

vector<Territory*> Cheater::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense;
	for (auto t : p->towned) {
		defense.push_back(t);
	}

	sort(defense.begin(), defense.end());

	return defense;
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

	p->printHand();
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

Human::Human() :PlayerStrategy()
{
}

Human::Human(Player* player) : PlayerStrategy(player)
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

		p->doneIssuingOrders = true;
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

/*
	Aggressive Player Methods
*/
Aggressive::Aggressive() : PlayerStrategy()
{
}
Aggressive::Aggressive(Player* player) : PlayerStrategy(player)
{
}
Order* Aggressive::discoverOrderType(string x) {
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
		newOrder->setOwner(p);
		newOrder->setTarget(defend.back()); // Deploys to the Territory with most armies, ie the last entry of toDefend
		int armiesToPlace = p->armiesHeld;		// Deploy all armies to strongest country

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
	else if (x.compare(options[1]) == 0) {
		cout << "Issued advance order" << endl;
		string cmd;
		if (!p->intelligent) {
			// Creating a 50/50 Chance for the Player to Advance or Attack
			int randNum = (rand() % 10) + 1;
			if (randNum >= 2)
				cmd = "attack";
			else
				cmd = "advance";
		}
		if (cmd == "attack" && attack.size() > 0 && defend.size() > 0) {
			cout << "Advance Order in Attack Mode" << endl;
			newOrder = new AdvanceOrder();
			newOrder->setOwner(p);

			int indexHighestArmies = 0;
			for (int i = 1; i < defend.size(); i++) {
				int temp = i;
				if (defend[temp]->getArmiesPlaced() > defend[indexHighestArmies]->getArmiesPlaced())
					indexHighestArmies = temp;
			}
			newOrder->setSource(defend[indexHighestArmies]);

			newOrder->setTarget(attack[0]); // Player will always attack the lowest army count territory
			//newOrder->setSource(defend[0]); // Deploys From Last Entry of Defend Since the Player always deploys to one place
			newOrder->setModifier(0);	//Advance set to attack mode
			newOrder->armyModifier = 10; // THE PLAYER WILL SEND AN AMOUNT BASED ON WHAT IS DEFENDING

		}
		else if (cmd == "advance" && attack.size() > 0 && defend.size() > 2) { // TODO: When the player needs to advance units to its main force
			cout << "Advance Order in Advance Mode" << endl;
			newOrder = new AdvanceOrder();
			newOrder->setOwner(p);

			// Searching Inside toDefend for the highest armycount territory
			int indexHighestArmies = 0;
			for (int i = 1; i < defend.size(); i++) {
				int temp = i;
				if (defend[temp]->getArmiesPlaced() > defend[indexHighestArmies]->getArmiesPlaced())
					indexHighestArmies = temp;
			}
			newOrder->setTarget(defend[indexHighestArmies]);

			Territory* tempTarget = defend[indexHighestArmies];

			for (Territory* p : defend) {
				if (p != newOrder->getTarget() && p->getArmiesPlaced() > 0) {
					newOrder->setSource(p);
					newOrder->armyModifier = p->getArmiesPlaced(); // Transfers all available units
					cout << "Loop check" << endl;
				}
				else { // If There are No Other Territories with Armies, the advance will not go through
					newOrder->setSource(nullptr);
					cout << "Source is Null" << endl;
				}
			}
			newOrder->setModifier(1); //Advance set to defend mode
		}
		else {
			newOrder = NULL;
		}


	}
	else if (x.compare(options[2]) == 0) {
		cout << "You have issued a bomb order." << endl;
		newOrder = new BombOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(attack.back()); // Targets the highest priority, ie the Attack Target with most units
		newOrder->setModifier(0);

	}
	else if (x.compare(options[3]) == 0) { // Maybe Aggressive Player Should Never Play This Card
		cout << "You have issued a blockade order:" << endl;
		newOrder = new BlockadeOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(defend[0]); // TEMP
		newOrder->setModifier(0);
		newOrder->neutralPlayer = p->neutral;

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order." << endl;
		newOrder = new AirliftOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(defend.back());
		newOrder->setSource(defend.end()[-2]); // This should be the territory with second most units
		newOrder->armyModifier = defend.end()[-2]->getArmiesPlaced(); // Will send all the armies on the source territory
	}
	else if (x.compare(options[5]) == 0) { // Aggressive Player Would Never Play This Card
		cout << "An Aggressive Player Does Not Issue Negotiate Orders." << endl;
		newOrder = NULL;
	}
	else {
		newOrder = NULL;
	}

	return newOrder;
}

//Prints standard order information as well as player's hand
void Aggressive::printOrderList(void) {
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
// deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore
void Aggressive::issueOrder()
{
	Order* issued;
	string x;
	Card* played;
	LogObserver* orderObserver = new LogObserver(p->orders);
	int index = 0;

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
	/*cout << "----------------------------------" << endl;
	cout << "Territories available to defend:" << endl;
	for (auto t : defend) {
		cout << *t << "Army count: " << t->getArmiesPlaced() << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "Territories available to attack: " << endl;
	for (auto t : attack) {
		cout << *t << "Owner: " << (t->getOwner())->getName() << endl;
	}*/
	cout << "----------------------------------" << endl;
	if (p->armiesHeld > 0 && toDefend().size() > 0) { //Deployment phase.

		cout << "Player must deploy armies." << endl;
		cout << "Armies held: " << p->armiesHeld << endl;
		issued = discoverOrderType("reinforcement");
	}
	else { //Attack and Card phase.

		//Attack 
		x = "advance";

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
				//played->play(p);

			}

		}
	}


	if (issued == NULL) {
		cout << "Invalid Order. Could not add it to the list." << endl;
		p->doneIssuingOrders = true;
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

vector<Territory*> Aggressive::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack;
	for (Territory* t : p->towned) {
		for (Territory* d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != p && t->getArmiesPlaced() > 0) { // Checks that the player owned territory has units to deploy
					attack.push_back(d);
				}

			}

		}
	}

	// Now the vector is sorted from best to worst target, uses the overloaded < operator from Map file
	//sort(attack.begin(), attack.end());

	return attack;
}

vector<Territory*> Aggressive::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense;
	for (auto t : p->towned) {
		if (t != nullptr)
			defense.push_back(t);
	}

	/*
	cout << "Checking contents on defend" << endl;
	for (auto t : defense)
		cout << t << endl;
	cout << "Done Checking contents on defend" << endl;

*/

	//sort(defense.begin(), defense.end());

	//For testing purposes while priority definition is still not implemented, priority is set to random:
	//std::shuffle(std::begin(defense), std::end(defense), rng);
	return defense;
}

/*
	Benevolent Player Methods
*/
Benevolent::Benevolent() : PlayerStrategy()
{
}

Benevolent::Benevolent(Player* player) : PlayerStrategy(player)
{
}

Order* Benevolent::discoverOrderType(string x) {
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
		newOrder->setOwner(p);
		newOrder->setTarget(defend[0]);
		int armiesToPlace = 10;		// Set to 10 by default but can change

		if (armiesToPlace <= p->armiesHeld) {
			newOrder->setModifier(armiesToPlace);
			newOrder->armyModifier = armiesToPlace;
			p->armiesHeld -= armiesToPlace;
			//newOrder->setOwner(p);
		}
		else {
			cout << "Only the remaining armies will be deployed." << endl;
			newOrder->setModifier(p->armiesHeld);
			newOrder->armyModifier = p->armiesHeld;
			p->armiesHeld = 0;
			//newOrder->setOwner(p);
		}
	}
	else if (x.compare(options[1]) == 0) { //Still requires the moving from current to target mechanism
		string cmd;
		if (!p->intelligent) {
			cmd = "attack";
		}

		if (cmd == "attack") { // Benevolent Player Will Never Attack
			cout << "Benevolent Type Player Does Not Issue Attack Orders" << endl;
			newOrder = NULL;
		}
		else { // TODO: When the player needs to advance units to its main force
			newOrder = new AdvanceOrder();
			newOrder->setOwner(p);
			newOrder->setTarget(defend[0]);
			newOrder->setSource(defend[1]);
			newOrder->setModifier(1); //Advance set to defend mode
			newOrder->armyModifier = 10; // Transfers 10 units at a time to keep them spread out
		}


	}
	else if (x.compare(options[2]) == 0) {
		cout << "Benevolent Type Player Does Not Issue Bomb Orders" << endl;
		newOrder = NULL;
	}
	else if (x.compare(options[3]) == 0) { // Transfers the territory with fewest Units to the Neutral Player
		cout << "You have issued a blockade order:" << endl;
		newOrder = new BlockadeOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(defend[0]);
		newOrder->setModifier(0);
		newOrder->neutralPlayer = p->neutral;

	}
	else if (x.compare(options[4]) == 0) {
		cout << "You have issued an airlift order." << endl;
		newOrder = new AirliftOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(defend[0]);
		newOrder->setSource(defend[1]);
		newOrder->armyModifier = 10; // Will send 10 armies at once
	}
	else if (x.compare(options[5]) == 0) { // Initiates a Negotiation with a Player in the Attack List
		cout << "You have issued a negotiate order. Please indicate which of the territories you would like to attempt diplomacy with:" << endl;
		newOrder = new NegotiateOrder();
		newOrder->setOwner(p);
		newOrder->setTarget(attack[0]);
	}
	else {
		newOrder = NULL;
	}

	return newOrder;
}

//Prints standard order information as well as player's hand
void Benevolent::printOrderList(void) {
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
void Benevolent::issueOrder()
{
	Order* issued;
	string x;
	Card* played;
	LogObserver* orderObserver = new LogObserver(p->orders);
	int index = 0;

	vector<Territory*> defend = toDefend();
	vector<Territory*> attack = toAttack();
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
		p->doneIssuingOrders = true;
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

vector<Territory*> Benevolent::toAttack()
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

	return attack;
}

vector<Territory*>Benevolent::toDefend()
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