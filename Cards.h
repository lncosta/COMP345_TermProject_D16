#pragma once
#include <vector>
#include <string>
using std::string;
using std::ostream;
using std::istream;
using std::vector; 

enum Type { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };


struct Order {
	string name;
	Order();

	// Stream Insertion
	friend ostream& operator << (ostream& out, const Order& p);
	friend istream& operator >> (istream& in, Order& p);
};

struct OrdersList {
	vector<Order*> listOfOrders;
	OrdersList();

	// Stream Insertion
	friend ostream& operator << (ostream& out, const OrdersList& p);
	friend istream& operator >> (istream& in, OrdersList& p);

	// Methods
	void addOrder(Order* other);
};

struct Card {

	// Data Members
	Type cardType;

	// Constructors
	Card(); 
	Card(int type);

	// Copy constructor
	Card(const Card& copy);

	// Assignment Operators
	void setCardtype(int cardType);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Card& p);
	friend istream& operator >> (istream& in, Card& p);

	// Methods
	//void play(Player& p, Deck& d);

	// Destructor
	// ~Card();
};

struct Hand {

	// Data Members
	vector<Card*> handOfCards;

	// Constructors
	Hand();

	// Copy constructor
	Hand(const Hand& copy);

	// Assignment Operators
	void setHandOfCards(vector<Card*>& cards);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Hand& p);
	friend istream& operator >> (istream& in, Hand& p);

	// Destructor
	// ~Hand();
};

struct Player {

	// Data Members
	Hand* playerHand;
	OrdersList* playerOrders; 

	// Constructors
	Player();

	// Copy constructor
	Player(const Player& copy);

	// Assignment Operators
	void setPlayerHand(Hand* hand);
	void setOrdersList(OrdersList* orders);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	// Destructor
	// ~Player();
};

struct Deck {
	// Data Members
	vector<Card*> deckOfCards;
	int maxDeckSize;

	// Constructors
	Deck();
	

	// Copy constructor
	Deck(const Deck& copy);

	// Assignment Operators
	void setDeckOfCards(vector<Card*>& cards);
	void setMaxDeckSize(int maxDeckSize);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Deck& p);
	friend istream& operator >> (istream& in, Deck& p);

	// Methods
	Card draw(Player& p);
	void printDeck();

	// Destructor
	// ~Deck();
};