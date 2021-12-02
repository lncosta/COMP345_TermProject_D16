#pragma once
#include "Player.h"

class Order;
class Player;


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

class Neutral : public PlayerStrategy {
public:
	Neutral();
	Neutral(Player* player);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	Order* discoverOrderType(string x);
};
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