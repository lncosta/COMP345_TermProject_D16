#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
using namespace std;
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
	Card *ace, *spade, *hearts, *club;
	string result;
	bool round = true;
	Territory* a = new Territory(1, 2, "Argeria");
	Territory* b = new Territory(2, 2, "Brazil");
	Territory* c = new Territory(3, 2, "China");
	Territory* d = new Territory(4, 2, "Denmark");
	ace = new Card(BOMB); 
	spade = new Card(BOMB);
	hearts = new Card(BOMB);
	club = new Card(BOMB);


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
	cout << "----------------------------------------------" << endl;
	cout << "Creating a Player using its copy constructor: " << endl;
	Player* copiedPlayer = new Player(*players[0]); 
	copiedPlayer->setPlayerID(102);
	cout << "Player " << copiedPlayer->getPlayerID() << " - " << copiedPlayer->getName() << endl;
	players[0]->addTerritory(a);
	players[0]->addTerritory(b);
	cout << *b;
	players[0]->addCard(ace);
	players[0]->addCard(spade);
	cout << "----------------------------------------------" << endl;
	cout << "Issuing orders for Players:" << endl;
	//Issuing orders for example Player:
	for (auto p : players) {
		cout << "Player - " << p->getName() << endl;
		round = true;
		while (round) {
			p->issueOrder();
			cout << "Would you like to issue more orders? Y/N" << endl;
			cin >> result;
			while (result != "N" && result != "n" && result != "y" && result != "Y") {
				cin >> result;
			}
			if (result == "N" || result == "n") {
				round = false;
			}
		}
		cout << *p << endl;
	}

	cout << "----------------------------------------------" << endl;
	//Demonstrating toAttack():
	cout << "Territories to Attack:" << endl;
	vector<Territory*> attc = players[0]->toAttack();
	for (Territory* p : attc) {
		cout << *p;
	}
	cout << endl;
	cout << "----------------------------------------------" << endl;
	//Demonstrating toDefend():
	cout << "Territories to Defend:" << endl;
	vector<Territory*> def = players[0]->toDefend();
	for (Territory* p : def) {
		cout << *p;
	}
	cout << endl;
	cout << "----------------------------------------------" << endl;
	//Comparing the copied Players:
	cout << "Comparing the copied Players:" << endl;
	cout << *players[0] << endl;
	cout << *copiedPlayer << endl;
	cout << "----------------------------------------------" << endl;
	//Creating a copy using the assignment operator:
	if (players.size() > 1) {
		Territory* temp = new Territory(1, 2, "Greece");
		players[1]->addTerritory(temp);
		Player temp2;
		temp2 = *players[1];
		cout << "Creating a copy using the assignment operator:" << endl;
		cout << temp2 << endl;
	}
	cout << "----------------------------------------------" << endl;
	cout << "Freeing the memory:" << endl;
	//Deallocating the memory:
	if (copiedPlayer) {
		delete copiedPlayer;
		copiedPlayer = NULL;
	}
	for (Player* p : players) {
		delete p;
	}
	for (Territory* p : attc) {
		if (p != nullptr) {
			delete p;
		}
	}
	for (Territory* p : def) {
		if (p != nullptr) {
			delete p;
		}
	}

}

int main(void) {
	example();

	return 0;
}