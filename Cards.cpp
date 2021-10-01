/*
play() still doesn't work but the rest seems to be working. I'm currently using the .cpp as a driver but 
I'll split it once I'm done my implementation. 

missing some stream insertions (istream), copy constructors and assignment operators

*** The randomizer isn't random, this will get fixed later *** 

*/

#include "Cards.h";
#include <iostream>;

using std::cout;
using std::endl;

int numberOfTypes = 5;
int numberOfPlayers = 5;

void OrdersList::addOrder(Order* order) {
	listOfOrders.push_back(order);
}

// Constructors
Card::Card() {} 
Card::Card(int type) { cardType = Type(type); }
Card::Card(const Card& c) {cardType = c.cardType;}

Hand::Hand() {}
Hand::Hand(const Hand& h) { handOfCards = h.handOfCards; }

Order::Order() { name = "default name"; }

OrdersList::OrdersList() {}

Player::Player(){ playerHand = new Hand(); playerOrders = new OrdersList();}

Deck::Deck() {
	int maxDeckSize = numberOfPlayers * numberOfTypes * 3;
	for (int types = 0; types < numberOfTypes; types++) {
		for (int cards = 0; cards < (3 * numberOfPlayers); cards++) {
			Card c;
			c.cardType = Type(types);
			Card* pointer = new Card(c); // *TEST* adding these two lines and commenting out the other
			deckOfCards.push_back(pointer);

			//deckOfCards.push_back(new Card(c));
		}
	}
}

// Methods
Card Deck::draw(Player& p) {

	// Fisher-Yates shuffle algorithm
	int size = deckOfCards.size();
	for (int i = 0; i < (size - 1); i++) {
		int j = i + rand() % (size - i);
		std::swap(deckOfCards[i], deckOfCards[j]);
	}

	//vector2.push_back(vector1.pop_back());

	// draw a card from the back of the deck and then remove it from the deck
	Card* drawnCard = deckOfCards.back();
	deckOfCards.pop_back();
	// add the card to the player's hand

	p.playerHand->handOfCards.push_back(drawnCard);
	return *drawnCard;

}
//
//void Card::play(Player& p, Deck& d) {
//		Order ord;
//		ord.name = Type(cardType);
//		p.playerOrders.listOfOrders.push_back(ord);
//		std::vector<Card*>::iterator it = std::find(p.playerHand.handOfCards.begin(), p.playerHand.handOfCards.end(), this);
//		if (it != p.playerHand.handOfCards.end()) {
//			//not needed	int index = std::distance(p.playerHand.handOfCards.begin(), it);
//			 Card* cardPlayed = p.playerHand.handOfCards.at(it); 
//			d.deckOfCards.push_back(cardPlayed);
//			p.playerHand.handOfCards.erase(it);
//			
//		}
//		
//		else cout << "ERROR..." << endl;
//	}

// Ostreams

ostream& operator<<(ostream& out, const Card& p)
{
	if (p.cardType == 0) {
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

ostream& operator<<(ostream& out, const OrdersList& p)
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

	Card c1(2);

	cout << "Type of card c1 is: " << c1 << endl;
	Deck d1;
	Player p1;
	cout << "Cards/Orders for p1 (should be empty): " << p1 << endl;
	cout << "Size of the deck before cards are drawn: " << d1.deckOfCards.size() << endl;
	cout << "The drawn cars if of type: " << d1.draw(p1) << endl;
	cout << "The drawn cars if of type: " << d1.draw(p1) << endl;
	cout << "The drawn cars if of type: " << d1.draw(p1) << endl;
	cout << "The drawn cars if of type: " << d1.draw(p1) << endl;
	cout << "The drawn cars if of type: " << d1.draw(p1) << endl;
	cout << "Size of the deck after drawing 5 cards: " << d1.deckOfCards.size() << endl;
	cout << "Size of the player's hand after drawing 5 cards: " << p1.playerHand->handOfCards.size() << endl;
	cout << p1; 
	cout << "-THE END" << endl; 
}
