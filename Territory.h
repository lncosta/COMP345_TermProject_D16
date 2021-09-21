#pragma once
#include "Player.h"
#include <list>
#include <string>

class Territory {
public:
	Territory(void);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Territory& p);
	friend istream& operator >> (istream& in, Territory& p);
private:
	Player owner;
	string name;
	int continentID;
	int territoryID;
	list<int> adjacentTerritories;
	int armiesPlaced;

};