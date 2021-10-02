Welcome to Arie's branch... 

I'm new to C++ and still trying to figure it out, please bear with me.
I will be using this note as a personal to do list and way to organize my thoughts.


Each class needs: copy constructor, assignment operator and stream insertion operator
Every data member that is a user-defined class should be a pointer

I will try to use an enum for the card type but I'm not sure how it works with pointers. -> enum should be a global variable

Assignment 1: 

Deck: 
- Data member: collection of Card*, sizeOfDeck -> not sure if I really need a sizeOfDeck variable
- draw() method : 
Player draws a card from the deck and adds it to his hand.

Hand:
- Data member: collection of Card*
- Contains cards drawn from the deck

Card: 
- Data member: Type (enum?) , numberOfTypes 
- Can be 1 of 5 types
- play() mehtod: 
creates an order and adds it to the player's list of orders 
then returns the card to the deck

29/09/2021: I decided to make a basic running version of my program first and then to divide it into .h/.cpp files and then to fullfill the pointer requirement. Trying to do everything right from the beginning was just giving me errors. I'm using struct so I can minimize my possible errors but will be switching everything to classes once I'm done. All the structs are there, I think that all the data members I'll need are there as well. Draw() seems to work and do what I need. Play() can create orders and remove the calling card from the deck (I think) but I can't figure out how to do that. I think the next step is to figure out pointers.
01/10/2021: Everything is now split in header and cpp files. Pointer requirement is fullfilled, play() and draw() method work. The next step is to add the missing copy constructors, assignment operators, stream insertion operators and driver file for the demo. 
