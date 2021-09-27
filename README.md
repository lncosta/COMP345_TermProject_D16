Welcome to Arie's branch... 

I'm new to C++ and still trying to figure it out, please bear with me.
I will be using this note as a personal to do list and way to organize my thoughts.


Each class needs: copy constructor, assignment operator and sream insertion operator
Every data member should be a pointer

I will try to use an enum for the card type but I'm not sure how it works with pointers
Deck and Hand will have a vector container to hold cards. It's a dynamic array and I can randomize the draw() method so it should work fine. 

Assignment 1: 

Deck: 
- Data member: Card, sizeOfDeck
- Contains all the cards in the game 
- draw() method : 
Player draws a card from the deck and adds it to his hand.
Should have 1/5 chance of picking each card (random) 

Hand:
- Data member: Card
- Contains cards drawn from the deck

Card: 
- Data member: Type (enum?) , numberOfTypes 
- Can be 1 of 5 types
- play() mehtod: 
creates an order and adds it to the player's list of orders 
then returns the card to the deck
