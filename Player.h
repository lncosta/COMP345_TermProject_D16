#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <list>
#include <iterator>
#include <string>

#include "Territory.h"
#include "Cards.h"
#include "OrdersList.h"
	
using namespace std;

int playersCreated;

class Player {
	//Data members:
	int playerID;
	string name;
	list<Territory> towned;
	list<Cards> cards;
	OrdersList* orders;

public:
	//Constructors:
	Player(void);
	Player(Player* other);
	Player(int playerID, string name);

	//Assignment Operators:

	void setPlayerID(int playerID);
	void setName(string name);
	void setTOwned(list<Territory> towned);
	void setCards(list<Cards> cards);
	void setOrdersList(OrdersList* orders);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player &p);
	friend istream& operator >> (istream& in, Player& p);
	//Methods:
	list<Territory> toDefend();
	list<Territory> toAttack();
	void issueOrder();

};

#endif 
