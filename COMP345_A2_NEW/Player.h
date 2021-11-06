#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <vector>
#include <iterator>
#include <string>


/*COMP 345 Section D - Assignment #1
* Fall 2021
* Due October 8th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/
using namespace std;

class Card;
class OrdersList;
class Hand;
class Order;
class DeployOrder;

class Player {
	static int playersCreated;
private:
	//Data members:
	int playerID;
	int armiesHeld;
	string name;
	vector<Territory*> towned;
	vector<Card*> cards; //Will become a Hand* pointer once code is integrated with Part 5 of assignment. For now, a hand is simply considered a collection of cards held by the Player itself. 
	OrdersList* orders;
	vector<Player*> cannotAttack; // Used with the negotiate to store the players that can't be attacked

	//From Cards
	Hand* playerHand;
	OrdersList* playerOrders;

public:
	//Constructors:
	Player(void);
	Player(const Player& other);

	//Assignment Operators:

	void setPlayerID(int playerID);
	void setName(string name);
	void setArmiesHeld(int x);
	void setTOwned(vector<Territory*> const& other);
	void setCards(vector<Card*>& cards);
	void setOrdersList(OrdersList* orders);
	Player& operator =(const Player& other);

	//Accessor methods:
	string getName(void);
	int getPlayerID(void);
	int getArmiesHeld(void);
	vector<Territory*> getTowned(void);
	vector<Card*> getCards(void);
	OrdersList* getOrders(void);
	vector<Player*> getCantAttack(void);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	//Destructors:
	~Player(void);
	//Methods:
	void printOrderList(void);
	Order* discoverOrderType(string x);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	void addTerritory(Territory* ter);

	//From Cards:
	void addCard(Card* card);
	void addOrder(Order* order);
	vector<Card*> getHandOfCards();
	Hand* getPlayerHand();


	//Friend classes:
	friend class Card;
	friend class Hand;
	friend class OrdersList;
	friend class Deck;

};
#endif // !_PLAYER_H_
