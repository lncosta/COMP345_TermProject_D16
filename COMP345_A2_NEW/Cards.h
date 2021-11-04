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
#pragma once
#include <vector>
#include <string>
#include "Orders.h"
#include "Player.h"
using std::string;
using std::ostream;
using std::istream;
using std::vector;

// Global
enum Type { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };

class Player;
class Order;
class OrdersList; 
class Order;


class Card; // forward declaration
class Deck; 

class Hand {
private:
	// Data members
	vector<Card*> handOfCards;
	Deck* deck; 

public:
	// Constructors
	Hand();

	// Copy constructor
	Hand(const Hand& copy);

	//Accessor methods
	vector<Card*> getHandOfCards();
	Deck* getDeck();

	// Mutator methods
	void setHandOfCards(vector<Card*>& cards);
	void setDeck(Deck* d); 

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
	Card* draw(Player* p);
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
	void play(Player* p);
	string orderType();

	// Destructor
	~Card();
};