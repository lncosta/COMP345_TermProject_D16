#include "Cards.h"
#include <iostream>
using std::cout;
using std::endl;

int main (){
	srand(time(0)); // initialize the seed for the random number generator

cout << "Welcome to the Warzone's card tester program" << endl;
cout << "Creating a deck of cards and a player with a hand of cards..." << endl << "Beep Boop..." << endl << endl;
Deck deck1; 
Player player1;
cout << "Deck of cards, player and hand of cards succesfuly created!" << endl << endl;
cout << "Here are the contents of the deck:" << endl << deck1 << endl;

cout << "The player's hand currently contains this:" << endl << *(player1.playerHand) << endl; 

cout << "Let's draw some cards from the deck:" << endl << endl; 
cout << "The first card drawn is of type: "<< deck1.draw(player1) << endl;
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

cout << "and now let's see what's in player1's hand and order list:" << endl << player1 << endl << endl;

cout << "Thank you..." << endl << "---The End---" << endl << endl;
system("pause");
}