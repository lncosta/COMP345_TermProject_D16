#pragma once
#include "Player.h"

class Order;
class Player;

// 1.2.9 Not all classes implement a copy constructor, assignment operator, and stream insertion operator.
// due to redundancy as discussed in class

//1.3.3 Presence of a PlayerStrategy abstract class that is a superclass of all the player strategy behavioral classes.
//1.3.5 Each of the ConcreteStrategy classes implement their own version of the issueOrder(), toAttack(), and toDefend() methods.
class PlayerStrategy {
public:
	Player* p;
	virtual void issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;

	PlayerStrategy();
	PlayerStrategy(Player* player);
	virtual ~PlayerStrategy();

	void setPlayer(Player* player);
	Player* getPlayer(void);
};

// 1.3.4 For each strategy as described above, you have a ConcreteStrategy class: HumanPlayerStrategy, AggressivePlayerStrategy, 
// BenevolentPlayerStrategy, and NeutralPlayerStrategy that are subclasses of the PlayerStrategy class.
// 1.2.4 Neutral player: computer player that never issues any order. 
class Neutral : public PlayerStrategy {
public:
	Neutral();
	Neutral(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	Order* discoverOrderType(string x);
};

// 1.2.5 Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories (only once per turn).
class Cheater : public PlayerStrategy {
public:
	Cheater();
	Cheater(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	//Auxilliary:
	Order* discoverOrderType(string x);
	void printOrderList(void);
};

// 1.2.1 Human player: requires user interactions to make decisions
class Human : public PlayerStrategy {
public:
	Human();
	Human(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	//Auxiliary methods:
	void printOrderList(void);
	int deployArmies(void);
	Order* discoverOrderType(string x);
	void determineTarget(int state, Order* order);
	void determineSource(int state, Order* order);


};

// 1.2.2 Aggressive player : computer player that focuses on attack(deploys or advances armies on its strongest country, 
//then always advances to enemy territories until it cannot do so anymore).
class Aggressive : public PlayerStrategy {
public:
	Aggressive();
	Aggressive(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	//Auxilliary:
	Order* discoverOrderType(string x);
	void printOrderList(void);

};

// 1.2.3 Benevolent player : computer player that focuses on protecting its weak countries
//(deploys or advances armies on its weakest countries, never advances to enemy territories).
class Benevolent : public PlayerStrategy {
public:
	Benevolent();
	Benevolent(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	// Auxilliary:
	void printOrderList(void);
	Order* discoverOrderType(string x);
};