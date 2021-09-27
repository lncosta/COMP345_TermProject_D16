#pragma once
/*
These are personal notes for when I'll inevitably forget how the hell c++ works
*/
#include <vector>
using std::vector;

class Deck
{
public: 
    Deck();
    vector<Card> deckOfCard; 
    int  deckSize; // number of players * number of types * 3 
    void printDeck(Deck myDeck);
    void draw();
};

class Hand
{
public: 
    Hand();
    vector<Card> handOfCard; 
};

class Card
{
public:
    Card(int valueOfType);
    Card();
    int numberOfTypes;
    enum Type { BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };
    Type cardType;

    void play();
};
