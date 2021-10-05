// Graph Implementation basis: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
#include "Map.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
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
	name = "Default"; 
	continentID = cID;
	territoryID = tID;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(int tID, int cID, string o)
{
	Player* nullPlayer = new Player();
	owner = nullPlayer;
	continentID = cID;
	territoryID = tID;
	name = o; 
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(const Territory& other) : adjTerritories(other.adjTerritories.size()){
	continentID = other.continentID;
	territoryID = other.territoryID;
	name = other.name; 
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

void Territory::addAdj(Territory* o)
{
	adjTerritories.push_back(o); 
}

void Territory::setOwner(Player* o)
{
	owner = o; 
}

void Territory::setContinent(Continent* o)
{
	cont = o; 
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
void Map::addNode(Territory* theTerritory) {
	countryList.push_back(theTerritory);
}
void Map::addContinent(Continent* theContinent)
{
	continentList.push_back(theContinent); 
}
list<Territory*> Map::getCountryList(void) {
	return countryList;
}
// Given a territory ID, will return the associate Territory Object
Territory* Map::getNode(int territoryToFind) {
	list<Territory*> currentCountryList = this->getCountryList();
	Territory* theTerritory = 0;
	for (auto t : currentCountryList) {
		if (t->getTerritoryID() == territoryToFind) {
			theTerritory = t;
		}
	}
	return theTerritory;
}




// Functions for Map Validation


void Map::DFS_helper(int s, bool* visited) {
	// mark the current node as visited
	visited[s] = true;
	//cout << "Visiting node " << s << endl;	

	// Go through the neighbors list
	list<int>::iterator i;
	/*for (i = adj[s].begin(); i != adj[s].end(); i++) {
		// if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
		if (!visited[*i]) {
			//cout << "Going to visit " << *i << " from " << s << endl;
			DFS_helper(*i, visited);
		}*/
	//}
}

void Map::DFS(int s) {
	bool wasVisited[5000]; 
	//starting with all nodes as not visited
	for (int i = 0; i < numNodes; i++) {
		wasVisited[i] = false;	}
	// Let the helper do the DFS recursively 
	DFS_helper(s, wasVisited);

}
//
//// Checks that the given Map object is a connected graph
bool Map::isConnected() {
	bool wasVisited[5000];
	// check whether from any node the rest of the nodes can be reached
	for (int i = 0; i < numNodes; i++) {
		DFS(i);
	}
	return true;
}

// Method 1:
// Can create new Map objects, only adding territories of a single continent
// Can then use the same isConnected() to check each subgraph
bool Map::continentSubgraphs() {
	return true; 
}

// Will traverse through countryList, checking that each entry has a valid value for continentID
bool Map::countryToContinentRelation() {
	for (Territory* currentTerritory : countryList) {
		if (currentTerritory->getContinentID() == NULL)		
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

MapLoader::MapLoader()
{
	cout << "MapLoader created" << endl; 
}

MapLoader::MapLoader(string MapFile)
{

}

MapLoader::~MapLoader()
{
}

Map* MapLoader::getMap(void)
{
	return &loadedMap;
}

//Solution from: https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}


std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

Map* MapLoader::loadMap(string MapFile)
{
	vector<Continent*> continents;
	vector<Territory*> territories; 
	ifstream input;
	bool readingContinents = false; 
	bool readingTerritories = false;
	bool readingBorders = false; 
	Map* created = new Map(); 
	vector<string> contents; 
	bool validFile1 = false, validFile2 = false, validFile3 = false;
	//Continents and territories:
	int id;
	int contCreated = 0; 
	string name;
	int armyValue;
	string garbage; 
	input.open(MapFile);
	if (input) {
		string current;
		cout << "----------------------------------------" << endl; 
		//Check if file exists but is empty:
		if (input.peek() == std::ifstream::traits_type::eof()) {
			cout << "ERROR - File is empty!" << endl;
			throw invalid_argument("Received Empty File.");
			return created;
		}
		else {
			
				while (input.peek() != EOF && getline(input, current))
				{
					if (current == "[continents]") {
						cout << current << endl;
						getline(input, current);
						readingContinents = true;
						readingTerritories = false;
						readingBorders = false;
						validFile1 = true;
					}
					else if (current == "[countries]") {
						cout << current << endl;
						getline(input, current);
						readingContinents = false;
						readingTerritories = true;
						readingBorders = false;
						validFile2 = true;
					}
					else if (current == "[borders]") {
						cout << current << endl;
						getline(input, current);
						readingContinents = false;
						readingTerritories =false;
						readingBorders = true;
						validFile3 = true;
					}

					if (readingContinents) { //Reads and adds continent objects. 
						cout << current << endl;
						contCreated++;
						contents = split(current, ' ');
						if (contents.size() > 0) {
							name = contents[0];
							id = contCreated;
							armyValue = stoi(contents[1]);
							Continent* ret = new Continent();
							ret->name = name;
							ret->id = id;
							ret->armyValue = armyValue;
							created->addContinent(ret);
							continents.push_back(ret); 
							
						}
						
					}
					else if (readingTerritories) {
						contents = split(current, ' ');
						if (contents.size() > 0) {
							id = stoi(contents[0]);
							name = contents[1];
							int contID = stoi(contents[2]);
							Territory* ret = new Territory(id, contID, name);
							territories.push_back(ret);
							cout << *ret;
							created->addNode(ret); //Not working yet. 

							for (Continent* cont : continents) {
								if (cont->id == contID) {
									cont->subGraph.push_back(ret); 
								}
							}
						}
					}
					else if (readingBorders) {
						cout << current << endl;
						contents = split(current, ' ');
						if (contents.size() > 0) {
							vector<int> edges; 
							for (string p : contents) {
								edges.push_back(stoi(p));   // 1 2 3
							}
							
							Territory* t = territories[edges[0] - 1]; // 1
							for (int i = 1; i < edges.size(); i++) {
								Territory* o = territories[edges[i] - 1];
								t->addAdj(o); 
							}
							
							
							
						}
					}
					else {
						cout << current << endl;
						readingContinents = false;
						readingTerritories = false;
						readingBorders = false;
					}
				}
				if (validFile1 && validFile2 && validFile3) {
					cout << "EOF" << endl;
					/*Printing territories that belong to the first continent:
					* vector<Territory*> temp = continents[0]->subGraph;
					for (Territory* p : temp) {
						cout << *p;
					}
					*/
					loadedMap = *created;
					return created;
				}
				else {
					cout << "ERROR - File is of incorrect format! Keywords were not found. Please check that the file meets the Map parameters." << endl;
					throw invalid_argument("ERROR - File is of incorrect format! Keywords were not found.");
					return &Map();
				}
				
		}

		//Map Creation:
		// ADD HERE
		loadedMap = *created; 
		return created;
		
	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return &Map();
	}
	return created;
}

ostream& operator<<(ostream& out, const Territory& p)
{
	out << p.name << " " << p.territoryID  << " " << p.continentID << endl;
	return out;
}

ostream& operator<<(ostream& out, const Map& p)
{
	out << "Territories that belong to the Map: " << endl; 
	for (Territory* a :p.countryList) {
		out << *a;
	}
	out << "Continents that belong to the Map: " << endl;
	for (Continent* a : p.continentList) {
		out << a->name << " " << a->id << " " << a->armyValue << endl;
	}
	return out;
}
