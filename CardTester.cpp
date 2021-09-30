// *** What is currently wrong with this program *** 
// - Needs classes instead of structs
// - Needs to use pointers
// - Needs to be split in header and cpp files
// - needs copy constructors, assignment operator and stream insertion operator
// What is right with this program? It runs! (except for play() -.- )

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;


enum Type { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };

int numberOfTypes = 5;
int numberOfPlayers = 4; 


struct Order {
	string name; 
};

struct OrderList {
	vector<Order> list; 
	int numberOfOrders;
};

struct Card {
	Type cardType;
	void type() {
		if (cardType == 0) {
			cout << "bomb" << endl;
		}
		else if (cardType == 1) {
			cout << "reinforcement" << endl;
		}
		else if (cardType == 2) {
			cout << "blockade" << endl;
		}
		else if (cardType == 3) {
			cout << "airlift" << endl;
		}
		else if (cardType == 4) {
			cout << "diplomacy" << endl;
		}
		else cout << "Unknown card type" << endl;
	}

	// https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/

	//void play(Player p, Deck d) {
	//	Order ord;
	//	ord.name = Type(cardType);
	//	p.playerOrderList.list.push_back(ord);
	//	std::vector<Card>::iterator it = std::find(p.playerHand.handOfCards.begin(), p.playerHand.handOfCards.end(), this);
	//	if (it != p.playerHand.handOfCards.end()) {
	//		//not needed	int index = std::distance(p.playerHand.handOfCards.begin(), it);
	//		p.playerHand.handOfCards.erase(it);
	//	}
	//	// Card cardPlayed = this; 
	//	//d.deckOfCards.push_back(cardPlayed);
	//	else cout << "ERROR..." << endl;

	//}
	Card() {}
	~Card() {}
	Card(Type(type)) {
		cardType = type;
	}
};

struct Hand {
	vector<Card> handOfCards;
	Hand() {}
	~Hand() {}
};

struct Player {
	Hand playerHand;
	OrderList playerOrderList;
	Player() {}
	~Player() {}
	void printHand() {
		if (playerHand.handOfCards.empty()) {
			cout << "This hand is empty" << endl;
		}
		for (Card c : playerHand.handOfCards) {
			c.type();
		}
	}
	void printOrderList() {
		if (playerOrderList.list.empty()) {
			cout << "This order list is empty" << endl;
		}
		for (Order o : playerOrderList.list) {
			cout << "This order is of type: " << o.name << endl;
		}
	}
};


struct Deck {
	vector<Card> deckOfCards;
	int maxDeckSize = numberOfPlayers * numberOfTypes * 3;
	Deck() {
		for (int types = 0; types < numberOfTypes; types++) {
			for (int cards = 0; cards < (3 * numberOfPlayers); cards++) {
				Card c;
				c.cardType = Type(types);
				deckOfCards.push_back(c);
			}
		}
	}
	~Deck() {}
	// Goes through the whole deck and print the type
	void printDeck() {
		for (Card c : deckOfCards) {
			c.type();
		}
	}
	// Draws a card, removes it from the deck and adds it to the player's hand and then return it 
	// I can either draw a random card or shuffle the deck and then draw the first card
	Card draw(Player& p) {

		//Card drawnCard = deckOfCards[rand() % deckOfCards.size()];    <----- Need to delete
		
		// Fisher-Yates shuffle algorithm
		int size = deckOfCards.size();
		for (int i = 0; i < (size - 1); i++) {
			int j = i + rand() % (size - i);
			std::swap(deckOfCards[i], deckOfCards[j]);
		}
		// draw a card from the back of the deck and then remove it from the deck
		Card drawnCard = deckOfCards.back();
		deckOfCards.pop_back();
		// add the card to the player's hand
		p.playerHand.handOfCards.push_back(drawnCard);
		return drawnCard;
	}
};
int main() {
	
	cout << endl;
	Deck d1; 
	Player p1; 
	p1.printHand(); 
	cout << "The size of the deck is: " << d1.deckOfCards.size() << endl;
	cout << endl;
	cout << "The drawn card is of type: ";  d1.draw(p1).type(); cout << endl;
	cout << "The drawn card is of type: ";  d1.draw(p1).type(); cout << endl;
	cout << "The drawn card is of type: ";  d1.draw(p1).type(); cout << endl;
	cout << "The drawn card is of type: ";  d1.draw(p1).type(); cout << endl;
	cout << "The drawn card is of type: ";  d1.draw(p1).type(); cout << endl;

	cout << "The size of the deck is: " << d1.deckOfCards.size() << endl;
	cout << endl;
	p1.printHand();
	cout << endl;
	cout << "UPDATE!!!" << endl;
	//d1.printDeck();
	system("pause > 0");

}
