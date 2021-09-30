#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include "Territory.h"
using namespace std;

// Stores Map Edges between two nodes
struct Edge {
	int start, end;
};

class Map {
private:
	int numNodes;
	list<int>* adj;
	vector<Territory> countryList;
public:
	Map(int num);
	~Map();
	void addEdge(int start, int end);
	void addTerritory(Territory theTerritory);
	bool* wasVisited;

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


class MapLoader {
private: 

public: 
	MapLoader();
	~MapLoader();

	void loadMap(string mapFile);
};
