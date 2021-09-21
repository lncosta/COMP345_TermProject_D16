#include <iostream>
#include "Player.h"

Player::Player(void){
	playerID = 0;
	name = "Default";
	list<Territory> empty;
	list<Cards> empty2;
	orders = NULL;
	playersCreated++;
}

Player::Player(Player* other) {
	playerID = 0;
	name = "Default";
	list<Territory> empty;
	list<Cards> empty2;
	orders = NULL;
	playersCreated++;
}

Player::Player(int playerID, string name) {
	this->playerID = playerID;
	this->name = name;
	list<Territory> empty;
	list<Cards> empty2;
	orders = NULL;
	playersCreated++;
}

//Assignment Operators:

void Player::setPlayerID(int playerID) {
	this->playerID = playerID;
}
void Player::setName(string name) {
	this->name = name;
}
void Player::setTOwned(list<Territory> towned) {
	this->towned = towned;
}
void Player::setCards(list<Cards> cards) {
	this->cards = cards;
}
void Player::setOrdersList(OrdersList* orders) {
	this->orders = orders; 
}

//Stream Insertions:
ostream& operator << (ostream& out, const Player& p) {

	out << "Player Name: " << p.name << endl;
	out << "Player ID: " << p.playerID<< endl;
	out << "Territories Owned: \n";
	for(auto var: p.towned){
		out << var << "\n";
	}

	out << "Cards Owned: \n";
	for (auto var : p.cards) {
		out <<" Card \n";
	}

	out << "Current Orders: \n";
	out << p.orders;

	return out;

}
istream& operator >> (istream& in, Player& p) {
	cout << "Enter Player Name: ";
	in >> p.name;

	return in;

}
//Methods:
list<Territory> toDefend();
list<Territory> toAttack();
void issueOrder();

