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
#include "Cards.h"
#include <iostream>
using std::cout;
using std::endl;

void cardDriver() {
	srand(time(0)); // initialize the seed for the random number generator

	cout << "Welcome to the Warzone's card tester program" << endl;
	cout << "Creating a deck of cards and a player with a hand of cards..." << endl << "Beep Boop..." << endl << endl;
	Deck deck1;
	Player player1;
	cout << "Deck of cards, player and hand of cards succesfuly created!" << endl << endl;
	cout << "Here are the contents of the deck:" << endl << deck1 << endl;
	cout << "The player's hand currently contains this:" << endl << endl << *(player1.playerHand) << endl;
	cout << "Let's draw some cards from the deck:" << endl << endl;
	cout << "The first card drawn is of type: " << deck1.draw(player1) << endl;
	cout << "The first card drawn is of type: " << deck1.draw(player1) << endl;
	cout << "The first card drawn is of type: " << deck1.draw(player1) << endl;
	cout << "The first card drawn is of type: " << deck1.draw(player1) << endl;
	cout << "The first card drawn is of type: " << deck1.draw(player1) << endl << endl;
	cout << "Player1 has now drawn 5 cards, let's check his hand: " << endl << endl;
	cout << *(player1.playerHand) << endl;
	cout << endl << "Are you enjoying the demo so far?" << endl << endl << endl;
	cout << "Let's play all the cards in player1's hand:" << endl << endl;

	// Loop to play the first card in the player's hand until the hand is empty
	while (player1.playerHand->getHandOfCards().size() > 0) {
		player1.playerHand->getHandOfCards().at(0)->play(player1, deck1);
	}

	cout << "and now let's see what's in player1's hand and order list:" << endl << endl << player1 << endl << endl;
	cout << "Part 1 done, now on to the boring stuff.." << endl;

	cout << "\ndeck1 contents: " << deck1 << endl;
	cout << "\nCreating deck2 and using the assignment operator:";
	Deck deck2;
	deck2 = deck1;
	cout << "\ndeck2 contents: " << deck1 << endl;
	cout << "\nCreating deck3 and using the copy constructor:";
	Deck deck3(deck2);
	cout << "\ndeck3 contents " << deck1 << endl;

	Card* p5 = new Card(1, 49);
	Card* p4 = new Card(2, 50);

	player1.addCard(p4);
	player1.addCard(p5);

	cout << "For hand: \n";
	cout << "\nhand1 contents: " << *(player1.playerHand) << endl;
	cout << "\nCreating hand2 and using the assignment operator:";
	Hand hand2;
	hand2 = *(player1.playerHand);
	cout << "\nhand2 contents: " << hand2 << endl;
	cout << "\nCreating hand3 and using the copy constructor:";
	Hand hand3(hand2);
	cout << "\nhand3 contents " << hand3 << endl;

	cout << "For Card: \n";
	Card card1(0, 99);
	cout << "\ncard1: " << card1 << endl;
	cout << "\nCreating card2 and using the assignment operator:";
	Card card2(3, 100);
	card2 = card1;
	cout << "\ncard2: " << card2 << endl;
	cout << "\nCreating card3 and using the copy constructor:";
	Card card3(card2);
	cout << "\ncard3: " << card3 << endl;

	cout << "\nThank you..." << endl << "---The End---" << endl << endl;

	system("pause");
}

int main (){
	cardDriver();
}