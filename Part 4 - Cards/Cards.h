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

	// Destructor
	~Order();
};

// dummy class 
class OrdersList {
public:
	// Data members
	vector<Order*> listOfOrders;

	// Constructor
	OrdersList();

	// Stream Insertion
	friend ostream& operator << (ostream& out, const OrdersList& ol);

	// Methods
	void addOrder(Order* other);

	// Destructor
	~OrdersList();
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

	//Accessor methods
	vector<Card*> getHandOfCards();

	// Mutator methods
	void setHandOfCards(vector<Card*>& cards);

	// Assignment Operators
	Hand& operator =(const Hand& h);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Hand& h);
	friend istream& operator >> (istream& in, Hand& h);

	//Methods
	void addCard(Card* card);
	Card* eraseCard(Card* card);

	// Destructor
	~Hand();
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
	~Player();
};

class Deck {
private:
	// Data Members
	vector<Card*> deckOfCards;

public:
	// Constructors
	Deck();

	// Copy constructor
	Deck(const Deck& copy);

	// Accessor methods
	vector<Card*> getDeckOfCards();

	// Mutator methods
	void setDeckOfCards(vector<Card*>& cards);

	// Assignment Operators
	Deck& operator =(const Deck& d);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Deck& d);
	friend istream& operator >> (istream& in, Deck& d);

	// Methods
	Card draw(Player& p);
	void addCard(Card* card);

	// Destructor
	~Deck();
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
	Card(int type, int id);

	// Copy constructor
	Card(const Card& copy);

	// Accessor methods
	Type getType();
	int getCardID();

	// Mutator methods
	void setCardType(Type cardType);
	void setCardID(int cardID);

	// Assignment Operators
	Card& operator =(const Card& c);

	// Stream Insertions
	friend ostream& operator << (ostream& out, const Card& c);
	friend istream& operator >> (istream& in, Card& c);

	// Methods
	void play(Player& p, Deck& d);
	string type();

	// Destructor
	~Card();
};