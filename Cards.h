#pragma once
#include <vector>
#include <string>
using std::string;
using std::ostream;
using std::istream;
using std::vector; 

// Global
enum Type { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };

// dummy class 
class Order { 
public: 
	// Data members
	string name;

	// Constructor
	Order();
	Order(string s);

	// Copy Constructor
	Order(const Order& o);

	// Stream Insertion
	friend ostream& operator << (ostream& out, const Order& o);
};

// dummy class 
class OrdersList {
public:
	// Data members
	vector<Order*> listOfOrders;

	// Constructor
	OrdersList();

	// Stream Insertion
	friend ostream& operator << (ostream& out, const OrdersList& p);

	// Methods
	void addOrder(Order* other);
};

class Card; // forward declaration

class Hand {
private:
	// Data members
	vector<Card*> handOfCards;

public:
	// Constructors
	Hand();

	// Copy constructor
	Hand(const Hand& copy);

	//Accessor methods:
	vector<Card*> getHandOfCards();

	// Assignment Operators
	void setHandOfCards(vector<Card*>& cards);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Hand& p);
	friend istream& operator >> (istream& in, Hand& p);

	//Methods
	void addCard(Card* card);
	Card* eraseCard(Card* card);
	// Destructor
	// ~Hand();
};

// dummy class 
class Player {
public:
	// Data Members
	Hand* playerHand;
	OrdersList* playerOrders; 

	// Constructors
	Player();

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Player& p);

	// Methods
	void addCard(Card* card);
	void addOrder(Order* order);
	vector<Card*> getHandOfCards();


	// Destructor
	// ~Player();
};

class Deck {
private:
	// Data Members
	vector<Card*> deckOfCards;
	int maxDeckSize;

public:
	// Constructors
	Deck();
	
	// Copy constructor
	Deck(const Deck& copy);

	// Accessor methods:
	vector<Card*> getDeckOfCards();
	int getMaxDeckSize();

	// Assignment Operators
	void setDeckOfCards(vector<Card*>& cards);
	void setMaxDeckSize(int maxDeckSize);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Deck& p);
	friend istream& operator >> (istream& in, Deck& p);

	// Methods
	Card draw(Player& p);
	void printDeck();
	void addCard(Card* card);

	// Destructor
	// ~Deck();
};

class Card {
private:
	// Data Members
	Type cardType;
	int cardID;

public:
	// Constructors
	Card();
	Card(int type);

	// Copy constructor
	Card(const Card& copy);

	// Accessor methods:
	Type getType();
	int getCardID();

	// Assignment Operators
	void setCardType(Type cardType);
	void setCardID(int cardID);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Card& p);
	friend istream& operator >> (istream& in, Card& p);

	// Methods
	void play(Player& p, Deck& d);
	string type();

	// Destructor
	// ~Card();
};