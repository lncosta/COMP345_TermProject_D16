#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define PINK "\033[38;5;206m"

//Global variables:
vector<Player*> players;


void example(void) {
	int n = -1;

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

	
	cout << RED << "Welcome to Warzone!" << endl;
	cout << "This is the Player creation menu." << RESET << endl;
	while (n < 1) {
		cout << "Please enter the number of desired players. " << endl;
		cout << "The number should be greater than or equal to one." << endl;
		cin >> n;
	}

	for (int i = 0; i < n; i++)
	{
		Player * temp = new Player();
		string name;
		cout << "Player " << (i + 1) << " - Enter Player's name: " << endl;
		cin >> name;
		(*temp).setName(name);
		cout << "Welcome to Warzone, " << name << "!" << endl;
		players.push_back(temp);
	}

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player * p : players) {
		cout << "Player " << (*p).getPlayerID() << " - " << (*p).getName() << endl;
	}
	
	players[0]->addTerritory(&a); 
	players[0]->addCard(&ace);
	players[0]->addCard(&spade);
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
	cout << "Territories to Attack:" << endl;
	for (Territory* p : players[0]->toAttack()) {
		cout << *p;
	}
	cout << endl;
	cout << "Territories to Defend:" << endl;
	for (Territory* p : players[0]->toDefend()) {
		cout << *p;
	}
	cout << endl;
}

void temporary(void) {
	Player test;
	Territory a, b, c, d;
	Cards ace, spade, hearts, club;
	a.name = "Belgium";
	b.name = "Netherlands";
	c.name = "Australia";
	d.name = "Brazil";
	ace.name = "Ace";
	spade.name = "Spade";
	hearts.name = "Heart";
	club.name = "Club";
	test.setName("Philippa");
	test.addTerritory(&a);
	test.addTerritory(&b);
	test.addCard(&ace);
	test.addCard(&spade);
	cout << test << endl;
	Player test2;
	test2.setName("Triss");
	test2.addTerritory(&c);
	test2.addTerritory(&d);
	test2.addCard(&hearts);
	test2.addCard(&club);
	test2.issueOrder();
	cout << test2;
}

int main(void) {
	example();

	//Deallocating the memory:
	for (int i = 0; i < players.size(); i++)
	{
		delete players[i];
	}
	return 0;
}