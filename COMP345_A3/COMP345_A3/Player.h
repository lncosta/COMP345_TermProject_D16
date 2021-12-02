#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "PlayerStrategies.h"
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <array>

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
using namespace std;

class Card;
class OrdersList;
class Hand;
class Order;
class DeployOrder;
class Map;
class PlayerStrategy;


class Player {

private:
	//Data members:
	int playerID;
	int armiesHeld;
	string name;
	vector<Territory*> towned;
	vector<Card*> cards; //Will become a Hand* pointer once code is integrated with Part 5 of assignment. For now, a hand is simply considered a collection of cards held by the Player itself. 
	OrdersList* orders;
	vector<Player*> cannotAttack; // Used with the negotiate to store the players that can't be attacked
	static int playersCreated;
	bool conqueredThisTurn;

	//From Cards
	Hand* playerHand;
	OrdersList* playerOrders;

	//Player Strategy:
	PlayerStrategy* ps;


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
	void setConquered(bool answer);
	Player& operator =(const Player& other);
	void setStrategy(PlayerStrategy* strategy);

	//Accessor methods:
	string getName(void);
	int getPlayerID(void);
	int getArmiesHeld(void);
	vector<Territory*> getTowned(void);
	void removeTerritory(Territory* toRemove);
	vector<Card*> getCards(void);
	OrdersList* getOrders(void);
	vector<Player*> getCantAttack(void);
	bool getConquered(void);
	PlayerStrategy* getStrategy(void);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	//Destructors:
	~Player(void);
	//Methods:
	void printOrderList(void);
	int deployArmies(void);
	Order* discoverOrderType(string x);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void determineTarget(int state, Order* order);
	void determineSource(int state, Order* order);
	void issueOrder();
	void addTerritory(Territory* ter);

	//From Cards:
	void addCard(Card* card);
	void addOrder(Order* order);
	vector<Card*> getHandOfCards();
	Hand* getPlayerHand();
	void printHand(); 

	//Intelligent player:
	bool intelligent;

	//GameEngine parameters:
	Player* neutral;
	Map* map;

	//Friend classes:
	friend class Card;
	friend class Hand;
	friend class OrdersList;
	friend class Deck;
	friend class PlayerStrategy; 
	friend class Human;
	friend class Neutral;
	friend class Cheater;
	friend class Aggressive;
	friend class Benevolent;

	//Determine Player Strategy:
	void determineStrategy(string strategy); 
	bool doneIssuingOrders; 
	bool isNeutral;
};

//Randomizer:
extern random_device rd;
extern std::default_random_engine rng;



#endif // !_PLAYER_H_