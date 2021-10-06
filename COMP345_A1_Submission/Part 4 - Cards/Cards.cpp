/*
Double check Card and Deck constructor. Needs a destructor for playerOrders
*** Make destructors and check for memory leaks ***

*/
#include "Cards.h";
#include <iostream>;
using std::cout;
using std::endl;

// Temporary for assignment 1
int numberOfTypes = 5;
int numberOfPlayers = 3;

// Constructors
Card::Card() {}
Card::Card(int type) { cardType = Type(type); }
Card::Card(int type, int id) { cardType = Type(type); cardID = id; }
Card::Card(const Card& c) {
	cardType = c.cardType;
	cardID = c.cardID;
}

Hand::Hand() {}
Hand::Hand(const Hand& h) {
	for (Card* pointer : h.handOfCards) {
		Card* temp = new Card(*pointer);
		handOfCards.push_back(temp);
	}
}

Order::Order() { name = "default name"; }
Order::Order(string s) { name = s; }
Order::Order(const Order& o) { name = o.name; }

OrdersList::OrdersList() {}

Player::Player() { playerHand = new Hand(); playerOrders = new OrdersList(); }

Deck::Deck() {
	int counter = 0;
	for (int types = 0; types < numberOfTypes; types++) {
		for (int cards = 0; cards < (1 * numberOfPlayers); cards++) { // creates 3 cards (1 card per for the demo only) per player per type of card
			counter++; // the first card has ID == 1

			Card* pointer = new Card(types, counter);
			deckOfCards.push_back(pointer);
		}
	}
}

Deck::Deck(const Deck& d) {
	for (Card* pointer : d.deckOfCards) {
		Card* temp = new Card(*pointer);
		deckOfCards.push_back(temp);
	}
}

// Accessor methods
Type Card::getType() {
	return cardType;
}
int Card::getCardID() {
	return cardID;
}
vector<Card*> Player::getHandOfCards() {
	return this->playerHand->getHandOfCards();
}
vector<Card*> Hand::getHandOfCards() {
	return handOfCards;
}
vector<Card*> Deck::getDeckOfCards() {
	return deckOfCards;
}

// Mutator methods
void Card::setCardID(int cardID) {
	this->cardID;
}
void Card::setCardType(Type cardType) {
	this->cardType;
}
void Hand::setHandOfCards(vector<Card*>& cards) {
	this->handOfCards = cards;
}
void Deck::setDeckOfCards(vector<Card*>& cards) {
	this->deckOfCards = cards;
}

// Assignment operators
Card& Card::operator =(const Card& c) {
	cardType = c.cardType;
	cardID = c.cardID;
	return *this;
}
Deck& Deck::operator =(const Deck& d) {
	for (Card* pointer : d.deckOfCards) {
		Card* temp = new Card(*pointer);
		deckOfCards.push_back(temp);
	}
	return *this;
}
Hand& Hand::operator =(const Hand& h) {
	for (Card* pointer : h.handOfCards) {
		Card* temp = new Card(*pointer);
		handOfCards.push_back(temp);
	}
	return *this;
}

// Methods

// Basic add card/order methods
void Hand::addCard(Card* card) {
	handOfCards.push_back(card);
}
void Deck::addCard(Card* card) {
	deckOfCards.push_back(card);
}
void OrdersList::addOrder(Order* order) {
	listOfOrders.push_back(order);
}
void Player::addCard(Card* card) {
	this->playerHand->addCard(card);
}
void Player::addOrder(Order* order) {
	this->playerOrders->addOrder(order);
}

// Method to draw a card from the deck and add it to a player's hand
Card Deck::draw(Player& p) {

	// Fisher-Yates shuffle algorithm
	int size = deckOfCards.size();
	for (int i = 0; i < (size - 1); i++) {
		int j = i + rand() % (size - i);
		std::swap(deckOfCards[i], deckOfCards[j]);
	}

	// add the pointer to the last card in the deck to the player's hand
	p.addCard(getDeckOfCards().back());
	// remove that pointer from the deck
	getDeckOfCards().pop_back();
	// return the card that was just added to the player's hand
	return *(p.playerHand->getHandOfCards().back());
}

// Method to find and erase a Card* in a hand. It will take a Card*, find it in the hand, erase it and then return it
Card* Hand::eraseCard(Card* card) {
	std::vector<Card*>::iterator it = std::find(handOfCards.begin(), handOfCards.end(), card);
	if (it != handOfCards.end()) {
		int index = std::distance(handOfCards.begin(), it);
		Card* cardPlayed = handOfCards[index];
		handOfCards.erase(it);
		return cardPlayed;
	}
}

// Method to play a card within a certain hand and return it to a certain deck (passable as parameters)
// It also creates a new order with the same name as the cardType that was played
void Card::play(Player& p, Deck& d) {
		// Create order and add it to the player's orderlist
		Order ord;
		ord.name = "- A " + this->type() + " order";
		Order* ordPointer = new Order(ord);  
		p.addOrder(ordPointer); 

		// new pointer that points to the card
		Card* cardPointer = this;
		// erase the pointer that was in the player's hand
		(*(p.playerHand)).eraseCard(cardPointer); 
		// add the new pointer to the deck (same card, no leak) 
		d.addCard(cardPointer);
		cout << "The card played is of type: " << *cardPointer << endl;
}

// Method to return the cardType as a string
string Card::type() {
	if (cardType == 0)	return "bomb";
	else if (cardType == 1)	return "reinforcement";
	else if (cardType == 2) return "blockade";
	else if (cardType == 3) return "airlift";
	else if (cardType == 4) return "diplomacy";
	else return "Unknown card type";
}

// Ostreams
ostream& operator<<(ostream& out, const Card& c)
{
	if (c.cardType == 0) {
		out << "bomb" << endl;
	}
	else if (c.cardType == 1) {
		out << "reinforcement" << endl;
	}
	else if (c.cardType == 2) {
		out << "blockade" << endl;
	}
	else if (c.cardType == 3) {
		out << "airlift" << endl;
	}
	else if (c.cardType == 4) {
		out << "diplomacy" << endl;
	}
	else out << "Unknown card type" << endl;

	return out;
}

ostream& operator << (ostream& out, const Deck& d) {
	if (d.deckOfCards.size() <= 0) {
		cout << "This deck is empty" << endl;
	}
	else {
		out << "The deck currently contains these cards: " << endl;
		for (Card* c : d.deckOfCards) {
			out << *c;
		}
	}
	return out;
}

ostream& operator << (ostream& out, const Order& o)
{
	out << o.name << endl;
	return out;
}

ostream& operator << (ostream& out, const Hand& h) {
	if (h.handOfCards.size() <= 0) {
		cout << "The player doesn't have any cards" << endl;
	}
	else {
		out << "The player currently has these cards: " << endl;
		for (Card* c : h.handOfCards) {
			out << *c;
		}
	}
	return out;
}

ostream& operator << (ostream& out, const OrdersList& ol)
{
	if (ol.listOfOrders.size() <= 0) {
		cout << "The player doesn't have any orders" << endl;
	}
	else {
		out << "The player has the following list of orders:" << endl;
		for (Order* o : ol.listOfOrders) {
			out << *o;
		}
	}
	return out;
}

ostream& operator << (ostream& out, const Player& p) {
	out << *(p.playerHand) << endl;
	out << *(p.playerOrders) << endl;

	return out;
}

// Istreams
istream& operator >> (istream& in, Hand& h) {
	cout << "Please enter the card type of the card you want to add as a number from 0 to 4:" << endl;
	int temp;
	in >> temp;
	Card* cardPointer = new Card(temp);
	h.addCard(cardPointer);
	return in;
}

istream& operator >> (istream& in, Deck& d) {
	cout << "Please enter the card type of the card you want to add as a number from 0 to 4:" << endl;
	int temp; 
	in >> temp;
	Card* cardPointer = new Card(temp);
	d.addCard(cardPointer);
	return in;
}

istream& operator >> (istream& in, Card& c) {
	cout << "Please enter the card type as a number from 0 to 4:" << endl;
	int temp;
	in >> temp;
	c.cardType = Type(temp);
	return in;
}

// Destructors
Card::~Card() { cout << "Card deleted" << endl; };

Hand::~Hand() {
	for (Card* pointer : handOfCards) {
		delete pointer;
		pointer = nullptr;
	}
	handOfCards.clear();
};

//Deck::~Deck() {
//	for (Card* pointer : deckOfCards) {
//		delete pointer;
//		pointer = nullptr;
//	}
//	deckOfCards.clear();
//};