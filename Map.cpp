// Graph Implementation basis: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
#include "Map.h"
#include "Territory.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

// Constructor for the Map Class. Takes as input the number of nodes/Territories that will be on the map.
Map::Map(int numNodes) {
	this->numNodes = numNodes;
	// an array of type list<int> will be created, if num = 5, then there will be 5 neighbor lists
	adj = new list<int>[numNodes];
	// A list to store the territories and their info
	countryList = new vector<Territory>;
	// an array on the heap to store num(i.e. 5) boolean values 
	wasVisited = new bool[numNodes];
}
// Destructor for the Map Class
Map:: ~Map() {
	delete[] adj;
}

void Map::addEdge(int start, int end) {
	adj[start].push_back(end);
}
void Map::addTerritory(Territory theTerritory) {
	countryList.push_back(theTerritory);
}


void Map::DFS_helper(int s, bool* visited) {
	// mark the current node as visited
	visited[s] = true;
	//cout << "Visiting node " << s << endl;	

	// Go through the neighbors list
	list<int>::iterator i;
	for (i = adj[s].begin(); i != adj[s].end(); i++) {
		// if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
		if (!visited[*i]) {
			//cout << "Going to visit " << *i << " from " << s << endl;
			DFS_helper(*i, visited);
		}
	}
}

void Map::DFS(int s) {

	//starting with all nodes as not visited
	for (int i = 0; i < numNodes; i++) {
		wasVisited[i] = false;
	}
	// Let the helper do the DFS recursively 
	DFS_helper(s, wasVisited);
}

// Checks that the given Map object is a connected graph
bool Map::isConnected() {
	// check whether from any node the rest of the nodes can be reached
	for (int i = 0; i < numNodes; i++) {
		DFS(i);
		for (int j = 0; j < numNodes; j++) {
			if (!wasVisited[j])
				return false;
		}
	}
	return true;
}

// Method 1:
// Can create new Map objects, only adding territories of a single continent
// Can then use the same isConnected() to check each subgraph
bool Map::continentSubgraphs() {

}

// Will traverse through countryList, checking that each entry has a valid value for continentID
bool Map::countryToContinentRelation() {
	for (Territory currentTerritory : countryList) {
		if (currentTerritory.continentID == NULL)			// **** May need a get method for continentID ******
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


