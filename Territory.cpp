#include <iostream>
#include "Territory.h"
#include "Player.h"

using namespace std;

Territory::Territory(void){
	Player *nullPlayer = new Player();
	owner = nullPlayer;
	continentID = -1;
	territoryID = -1;
	list<int> adj;
	adjacentTerritories = adj;
	armiesPlaced = 0;
}
//Stream Insertions:
ostream& operator << (ostream& out, const Player& p) {

	out << "Territory Name: " << p.name << endl;
	return out;

}
istream& operator >> (istream& in, Player& p) {
	cout << "Enter Territory name: ";
	in >> p.name;

	return in;
}