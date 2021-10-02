#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

//Console colors to be used later:
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define PINK "\033[38;5;206m"



void example(void) { //This method demonstrates the basic functionalities of the Player class. 
	vector<Player*> players;
	int n = -1;

	//Creating necessary Objects for demonstration:
	Territory a, b, c, d;
	Cards ace, spade, hearts, club;
	string result;
	bool round = true;
	a.name = "Belgium";
	b.name = "Netherlands";
	c.name = "Australia";
	d.name = "Brazil";
	ace.name = "Ace";
	spade.name = "Spade";
	hearts.name = "Heart";
	club.name = "Club";


	cout << "Welcome to Warzone!" << endl;
	cout << "This is the Player creation menu." << endl;
	while (n < 1) {
		cout << "Please enter the number of desired players. " << endl;
		cout << "The number should be greater than or equal to one." << endl;
		cin >> n;
	}

	//Creating Player Objects:
	for (int i = 0; i < n; i++)
	{
		Player* temp = new Player();
		string name;
		cout << "Player " << (i + 1) << " - Enter Player's name: " << endl;
		cin >> name;
		(*temp).setName(name);
		cout << "Welcome to Warzone, " << name << "!" << endl;
		players.push_back(temp);
	}

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << (*p).getPlayerID() << " - " << (*p).getName() << endl;
	}
	//Demonstrating copy constructor functionality:
	cout << "Creating a Player using its copy constructor: " << endl;
	Player* copiedPlayer = new Player(*players[0]); 
	copiedPlayer->setPlayerID(102);
	cout << "Player " << copiedPlayer->getPlayerID() << " - " << copiedPlayer->getName() << endl;
	players[0]->addTerritory(&a);
	players[0]->addCard(&ace);
	players[0]->addCard(&spade);

	//Issuing orders for example Player:
	while (round) {
		players[0]->issueOrder();
		cout << "Would you like to issue more orders? Y/N" << endl;
		cin >> result;
		while (result != "N" && result != "n" && result != "y" && result != "Y") {
			cin >> result;
		}
		if (result == "N" || result == "n") {
			round = false;
		}
	}

	cout << *players[0] << endl;

	//Demonstrating toAttack():
	cout << "Territories to Attack:" << endl;
	for (Territory* p : players[0]->toAttack()) {
		cout << *p;
	}
	cout << endl;

	//Demonstrating toDefend():
	cout << "Territories to Defend:" << endl;
	for (Territory* p : players[0]->toDefend()) {
		cout << *p;
	}
	cout << endl;

	//Comparing the copied Players:
	cout << "Comparing the copied Players:" << endl;
	cout << *players[0] << endl;
	cout << *copiedPlayer << endl;
	
	//Creating a copy using the assignment operator:
	if (players.size() > 1) {
		Territory temp;
		temp.name = "Greece";
		players[1]->addTerritory(&temp);
		Player temp2;
		temp2 = *players[1];
		cout << "Creating a copy using the assignment operator:" << endl;
		cout << temp2 << endl;
	}

	//Deallocating the memory:
	delete copiedPlayer;
	for (Player* p : players) {
		delete p;
	}

}

int main(void) {
	example();

	return 0;
}