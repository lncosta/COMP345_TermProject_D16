#include "Cards.h"

// Wil likely delete this line
#include <iostream>
using namespace std;

// Card::numberOfTypes = 5;

Card::Card(int valueOfType) {


}
void Card::play()
{
    cout << "play() method called";

    if (cardType == BOMB) {
        cout << "I just bombed you";
    }
    // Create a new order
    // Remove the card from the hand and return it to the deck
}

// Deck
Deck::Deck()
{
    int numberOfPlayers = 4; // For testing purposes, will be removed
        deckSize = numberOfPlayers * 5 * 3;
}

void Deck::printDeck(Deck myDeck) {
    cout << "Test";
}