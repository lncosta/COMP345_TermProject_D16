#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

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




// Territory Class, acts as the nodes for the Map class
class Territory {
public:
	Territory(int tID, int cID);
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
public:
	Map(void);
	~Map(void);
	Map(const Map& toCopy);
	void addEdge(Territory* start, Territory* end);
	void addNode(Territory theTerritory);
	int getNumNodes(void);

	Territory* getNode(int territoryID);
	list<Territory> getCountryList(void);

	void DFS(int s);
	void DFS_helper(int s, bool* wasVisited);

	// Must check the following 3 functions
	bool validate();
	// Test to the see if the map is a connected graph
	bool isConnected();
	// Test to see that continents are connected subgraphs
	bool continentSubgraphs();
	// Test to see that each country belongs to only one continent
	bool countryToContinentRelation();
};

// Map Loader Class, used to create a map object from a given file
class MapLoader {
private:
	ifstream inputfilestream;
public:
	MapLoader(string MapFile);
	~MapLoader();

	Map loadMap();
};