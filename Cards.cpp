/*
I'm currently using the .cpp as a driver but 
I'll split it once I'm done my implementation. 

missing some stream insertions (istream), copy constructors and assignment operators

Player Order's out stream doesn't work... need to fix it 
*/

#include "Cards.h";
#include <iostream>;

using std::cout;
using std::endl;

int numberOfTypes = 5;
int numberOfPlayers = 5;

// Accessor methods:
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
int Deck::getMaxDeckSize() {
	return maxDeckSize;
}

//Assignment operators
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
void Deck::setMaxDeckSize(int maxDeckSize) {
	this->maxDeckSize = maxDeckSize;
}

// Constructors
Card::Card() {}
Card::Card(int type) { cardType = Type(type); }
Card::Card(const Card& c) { cardType = c.cardType; cardID = c.cardID; }

Hand::Hand() {}
Hand::Hand(const Hand& h) { handOfCards = h.handOfCards; }

Order::Order() { name = "default name"; }
Order::Order(string s) { name = s; }
Order::Order(const Order& o) { name = o.name; }

OrdersList::OrdersList() {}

Player::Player(){ playerHand = new Hand(); playerOrders = new OrdersList();}

Deck::Deck() {
	maxDeckSize = numberOfPlayers * numberOfTypes * 3;
	int counter = 0; 
	for (int types = 0; types < numberOfTypes; types++) {
		for (int cards = 0; cards < (3 * numberOfPlayers); cards++) { // creates 3 cards per player per type of card
			counter++; // the first card has ID == 1
			Card c(types); 
			c.setCardID(counter);
			Card* pointer = new Card(c); 
			deckOfCards.push_back(pointer);
		}
	}
}

// Methods

// Basic add card/order methods
void Hand::addCard(Card* card) {
	handOfCards.push_back(card);
}
void Deck::addCard(Card* card) {
	deckOfCards.push_back(card);
}
void Player::addCard(Card* card) {
	this->playerHand->addCard(card);
}
void Player::addOrder(Order* order) {
	this->playerOrders->addOrder(order);
}
void OrdersList::addOrder(Order* order) {
	listOfOrders.push_back(order);
}

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
	return *(p.playerHand->getHandOfCards().back()); // broken
}

// method to find and erase a Card* in a hand. It will take a Card*, find it in the hand, erase it and then return it
Card* Hand::eraseCard(Card* card) {
	std::vector<Card*>::iterator it = std::find(handOfCards.begin(), handOfCards.end(), card);
	if (it != handOfCards.end()) {
		int index = std::distance(handOfCards.begin(), it);
		Card* cardPlayed = handOfCards[index];
		handOfCards.erase(it);
		return cardPlayed;
	}
}


void Card::play(Player& p, Deck& d) {
		Order ord; // Should be able to trim those lines and change the order directly from the pointer
		ord.name = "TESTTTTTT"; // Does not do what I want  
		Order* ordPointer = &ord;
		p.addOrder(ordPointer);

		// new pointer that points to the card
		Card* cardPointer = this;
		// erase the pointer that was in the player's hand
		(*(p.playerHand)).eraseCard(cardPointer); 
		// add the new pointer to the deck (same card, no leak) 
		d.addCard(cardPointer);
		cout << "The card played is of type: " << *cardPointer << endl;
	}

// Ostreams

ostream& operator<<(ostream& out, const Card& p)
{
	if (p.cardType == 0 || p.cardType == BOMB) {
		out << "bomb" << endl;
	}
	else if (p.cardType == 1) {
		out << "reinforcement" << endl;
	}
	else if (p.cardType == 2) {
		out << "blockade" << endl;
	}
	else if (p.cardType == 3) {
		out << "airlift" << endl;
	}
	else if (p.cardType == 4) {
		out << "diplomacy" << endl;
	}
	else out << "Unknown card type" << endl;

	return out;
}

ostream& operator << (ostream& out, const Deck& p) {
	if (p.deckOfCards.size() <= 0) {
		cout << "This deck is empty" << endl;
	}
	else {
		out << "The deck currently contains these cards: " << endl;
		for (Card* c : p.deckOfCards) {
			out << *c;
		}
	}
	return out;
}

ostream& operator<<(ostream& out, const Order& p)
{
	out << p.name << endl;
	return out;

}

ostream& operator << (ostream& out, const Hand& p) {
	if (p.handOfCards.size() <= 0) {
		cout << "The player doesn't have any cards" << endl;
	}
	else {
		out << "The player currently has these cards: " << endl;
		for (Card* c : p.handOfCards) {
			out << *c;
		}
	}
	return out;
}

ostream& operator << (ostream& out, const OrdersList& p)
{
	if (p.listOfOrders.size() <= 0) {
		cout << "The player doesn't have any orders" << endl;
	}
	else {
		out << "The player has the following list of orders:" << endl;
		for (Order* o : p.listOfOrders) {
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


int main() {

	srand(time(0)); // initialize the seed for the random number generator
	Card c1(2);

	cout << "Type of card c1 is: " << c1 << endl;
	cout << endl << endl; 
//	//cout << Type(c1.cardType) << "    Output" << endl;
	Deck d1;
	Player p1;
	/*Card* cPointer = &c1;
	cout << "Before: " << p1 << endl;
	p1.addCard(cPointer);
	cout << "After: " << p1 << endl;*/

//	for (int i = 0; i < 5; i++) {
//		Card* pointer = new Card(i); 
//		p1.playerHand->handOfCards.push_back(pointer);
//}
//	cout << p1 << endl << endl;
//
//	Order testOrder("testing");
//	Order* ordPointer = &testOrder; 
//	p1.playerOrders->listOfOrders.push_back(ordPointer);
//
//	cout << p1 << endl; 

	/*cout << "Cards/Orders for p1 (should be empty): " << endl << p1 << endl;
	cout << "Size of the deck before cards are drawn: " << d1.getDeckOfCards().size() << endl;

	cout << "The drawn card is of type: " << d1.draw(p1) << endl;
	cout << "The drawn card is of type: " << d1.draw(p1) << endl;
	cout << "The drawn card is of type: " << d1.draw(p1) << endl;
	cout << "The drawn card is of type: " << d1.draw(p1) << endl;
	cout << "The drawn card is of type: " << d1.draw(p1) << endl;

	cout << "Size of the deck after drawing 5 cards: " << d1.getDeckOfCards().size() << endl;
	cout << "Size of the player's hand after drawing 5 cards: " << p1.playerHand->getHandOfCards().size() << endl;
	cout << *(p1.playerHand); */

	Card* cPointer = &c1;
	p1.addCard(cPointer);
	cout << "Size of the deck before a player plays a card: " << d1.getDeckOfCards().size() << endl;
	cout << "Player hand before playing a card: " << *(p1.playerHand) << endl; 
	(*cPointer).play(p1, d1);
	cout << "Player hand after playing a card: " << *(p1.playerHand) << endl;
	cout << "Size of the deck after a player plays a card: " << d1.getDeckOfCards().size() << endl;

	OrdersList ol1; 
	Order o1; 
	o1.name = "OLALALA";
	Order* op1 = &o1; 
	ol1.addOrder(op1);
	cout << ol1; 
	cout << "-THE END" << endl; 
}
