// Graph Implementation basis: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
#include "Map.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
using namespace std;

							// Temporary Classes

// Player Class for Territory Ownership
Player::Player(void) {
	name = "Default";
	playerID = 0;
}
Player::Player(const Player& other) {
	name = other.name;
	playerID = other.playerID;
}
Player::~Player(void) {
}

						// Task Specific Classes

// Constructor for the Territory Class
Territory::Territory(int tID, int cID) {
	Player* nullPlayer = new Player();
	owner = nullPlayer;
	continentID = cID;
	territoryID = tID;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(const Territory& other) : adjTerritories(other.adjTerritories.size()){
	continentID = other.continentID;
	territoryID = other.territoryID;
	armiesPlaced = other.armiesPlaced;
	owner = other.owner;

	for (auto p : other.adjTerritories) {
		Territory* temp = new Territory(*p);
		adjTerritories.push_back(temp);
	}
}
Territory::~Territory(void) {
	for (auto p : adjTerritories) {
		delete p;
	}
	adjTerritories.clear();
}
int Territory::getContinentID(void) {
	return continentID;
}
int Territory::getTerritoryID(void) {
	return territoryID;
}
vector<Territory*> Territory::getAdjTerritories(void) {
	return adjTerritories;
}


// Constructor for the Map Class.
Map::Map(void) {
	numNodes = 0;
	// A list to store the territories and their info
	list<Territory> countryList;
}
// Destructor for the Map Class
Map:: ~Map() {
	
}
// Copy constructor
Map::Map(const Map& toCopy) {
	numNodes = toCopy.numNodes;
}

int Map::getNumNodes(void) {
	return numNodes;
}
// Takes as input the pointers to the start and end territories
void Map::addEdge(Territory* start, Territory* end) {
	vector<Territory*> locationsFromStart = start->getAdjTerritories();
	locationsFromStart.push_back(end);
}
void Map::addNode(Territory theTerritory) {
	countryList.push_back(theTerritory);
}
list<Territory> Map::getCountryList(void) {
	return countryList;
}
// Given a territory ID, will return the associate Territory Object
Territory* Map::getNode(int territoryToFind) {
	list<Territory> currentCountryList = this->getCountryList();
	Territory* theTerritory = 0;
	for (auto t : currentCountryList) {
		if (t.getTerritoryID() == territoryToFind) {
			theTerritory = &t;
		}
	}
	return theTerritory;
}




					// Functions for Map Validation


//void Map::DFS_helper(int s, bool* visited) {
//	// mark the current node as visited
//	visited[s] = true;
//	//cout << "Visiting node " << s << endl;	
//
//	// Go through the neighbors list
//	list<int>::iterator i;
//	for (i = adj[s].begin(); i != adj[s].end(); i++) {
//		// if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
//		if (!visited[*i]) {
//			//cout << "Going to visit " << *i << " from " << s << endl;
//			DFS_helper(*i, visited);
//		}
//	}
//}

//void Map::DFS(int s) {
//	//starting with all nodes as not visited
//	for (int i = 0; i < numNodes; i++) {
//		wasVisited[i] = false;
//	}
//	// Let the helper do the DFS recursively 
//	DFS_helper(s, wasVisited);
//}
//
//// Checks that the given Map object is a connected graph
//bool Map::isConnected() {
//	bool wasVisited[this->getNumNodes()];
//	// check whether from any node the rest of the nodes can be reached
//	for (int i = 0; i < numNodes; i++) {
//		DFS(i);
//		for (int j = 0; j < numNodes; j++) {
//			if (!wasVisited[j])
//				return false;
//		}
//	}
//	return true;
//}

// Method 1:
// Can create new Map objects, only adding territories of a single continent
// Can then use the same isConnected() to check each subgraph
bool Map::continentSubgraphs() {

}

// Will traverse through countryList, checking that each entry has a valid value for continentID
bool Map::countryToContinentRelation() {
	for (Territory currentTerritory : countryList) {
		if (currentTerritory.getContinentID() == NULL)		
			return false;	// Returns false after finding an invalid continentID
	}
	return true;
}

// Checks isConnected, continentSubgraphs and countryToContinentRelation. Returns True when all are True. 
bool Map::validate() {
	if (this->isConnected() == true && this->continentSubgraphs() == true && this->countryToContinentRelation() == true)
		return true;
	return false;
}


// Constructor for the Maploader class

//MapLoader::MapLoader(string MapFile) {
//	this.inputfilestream(MapFile);
//	if (inputfilestream) {
//		cout << "Input File Successfully Found, Ready to Process";
//	}
//	else {
//		cout << "The Given File Could Not Be Opened, Try Another";
//	}
//
//}
//
//Map MapLoader::loadMap() {
//	string theLine;
//	getline(theLine);
//	cout << theLine << endl;
//}