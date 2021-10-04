#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
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

// Temp Classes

//Simplified Player Class
class Territory; // So that player is aware of the Territory Class
class Player {
	static int playersCreated;
private:
	//Data members:
	int playerID;
	string name;
	vector<Territory*> towned;

public:
	//Constructors:
	Player(void);
	Player(const Player& other);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);

	//Destructors:
	~Player(void);
};


class Continent {
public:
	int id;
	string name;
	int armyValue;
};

// Territory Class, acts as the nodes for the Map class
class Territory {
public:
	Territory(int tID, int cID);
	Territory(int tID, int cID, string name);
	Territory(const Territory& other);
	~Territory(void);
	int getContinentID(void);
	int getTerritoryID(void);
	vector<Territory*> getAdjTerritories(void);

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Territory& p);
	friend istream& operator >> (istream& in, Territory& p);
private:
	Player* owner;
	string name;
	int continentID;
	int territoryID;
	vector<Territory*> adjTerritories;
	int armiesPlaced;

	Continent* cont; //Must keep track of Continent it belongs to. 
};

// Stores Map Edges between two nodes
struct Edge {
	int start, end;
};

// Map Class, represents the actual game map being played
class Map {
private:
	int numNodes;
	list<Territory> countryList;
	list<Continent> continentList; 
public:
	Map(void);
	~Map(void);
	Map(const Map& toCopy);
	void addEdge(Territory* start, Territory* end);
	void addNode(Territory theTerritory);
	void addContinent(Continent * theContinent);
	int getNumNodes(void);

	Territory* getNode(int territoryID);
	list<Territory> getCountryList(void);

	void DFS(int s);
	void DFS_helper(int s, bool* wasVisited);

	// Must check the following 3 functions
	bool validate(void);
	// Test to the see if the map is a connected graph
	bool isConnected(void);
	// Test to see that continents are connected subgraphs
	bool continentSubgraphs(void);
	// Test to see that each country belongs to only one continent
	bool countryToContinentRelation(void);
};

// Map Loader Class, used to create a map object from a given file
class MapLoader {
private:
	string fileName; 
	Map loadedMap; 
public:
	MapLoader();
	MapLoader(string MapFile);
	~MapLoader();
	Map* getMap(void); 

	Map loadMap(string MapFile);
};
