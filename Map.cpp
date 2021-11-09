// Graph Implementation basis: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;


// Constructors for the Territory Class
Territory::Territory(int tID, int cID) {
	owner = NULL;
	name = "Default";
	continentID = cID;
	territoryID = tID;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(int tID, int cID, string o)
{
	owner = NULL;
	continentID = cID;
	territoryID = tID;
	name = o;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(const Territory& other) : adjTerritories(other.adjTerritories.size()) {
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
// Destructor for the territory class
Territory::~Territory(void) {
	cout << "The territory " << name << " was deleted." << endl;
	for (auto p : adjTerritories) {
		if (p != NULL) {
			delete p;
		}

	}
	adjTerritories.clear();
}
vector<Territory*> Continent::getSubGraph(void)
{
	return subGraph;
}
// Destructor for Continent Struct
Continent::~Continent(void) {
	for (auto p : subGraph) {
		delete p;
	}
	subGraph.clear();
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

void Territory::printAdjTerritories(void) {
	cout << "{";
	for (auto t : adjTerritories) {
		cout << t->getTerritoryName() << ", "; 
	}
	cout << "\b\b}" << endl; 
}

void Territory::addAdj(Territory* o)
{
	adjTerritories.push_back(o);
}

void Territory::setOwner(Player* o)
{
	owner = o;
}

Player* Territory::getOwner(void)
{
	return owner;
}

int Territory::getArmiesPlaced(void)
{
	return armiesPlaced;
}
void Territory::setArmiesPlaced(int newNum) {
	armiesPlaced = newNum;
}

string Territory::getTerritoryName() {
	return name;
}


// Constructor for the Map Class.
// Implements a directed graph structure
Map::Map(void) {
	numTerritories = 0;
}
// Destructor for the Map Class
Map:: ~Map() {
	continentVector.clear();
	territoryVector.clear();
}
// Copy constructor for the Map Class
Map::Map(const Map& toCopy) {
	numTerritories = toCopy.numTerritories;
	continentVector = toCopy.continentVector;
	territoryVector = toCopy.territoryVector;
}


void Map::addContinent(Continent* theContinent)
{
	continentVector.push_back(theContinent);
}

vector<Territory*> Map::getTerritoyVector(void) {
	return territoryVector;
}
vector<Continent*> Map::getContinentVector(void)
{
	return continentVector;
}
// Given a territory ID, will return the associate Territory Object
Territory* Map::getTerritory(int territoryToFind) {
	vector<Territory*> currentTerritoryVector = this->getTerritoyVector();
	Territory* theTerritory = 0;
	for (auto t : currentTerritoryVector) {
		if (t->getTerritoryID() == territoryToFind)
			theTerritory = t;
	}
	return theTerritory;
}


// Constructor for the Maploader class
MapLoader::MapLoader()
{
	cout << "MapLoader created" << endl;
}

MapLoader::~MapLoader()
{
	cout << "MapLoader was destroyed" << endl;
}

Map* MapLoader::getMap(void)
{
	return &loadedMap;
}

// Functions for assiting in processing the map info
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
	ifstream input;
	bool readingContinents = false;
	bool readingTerritories = false;
	bool readingBorders = false;
	Map* created = new Map();
	vector<string> contents;
	bool validFile1 = false, validFile2 = false, validFile3 = false;
	Continent* conti = new Continent();
	int contCreated = 0;
	int territoryCreated = 0;



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
					readingTerritories = false;
					readingBorders = true;
					validFile3 = true;
				}

				if (readingContinents) { //Reads and adds continent objects. 
					cout << current << endl;
					contCreated++;
					contents = split(current, ' ');
					if (contents.size() > 0) {
						conti->name = contents[0];
						conti->id = contCreated;
						conti->armyValue = stoi(contents[1]);
						Continent* ret = new Continent();
						ret->name = conti->name;
						ret->id = conti->id;
						ret->armyValue = conti->armyValue;
						created->addContinent(ret);
					}


				}
				else if (readingTerritories) {
					cout << current << endl;
					contents = split(current, ' ');
					territoryCreated++;
					if (contents.size() > 0) {
						conti->id = stoi(contents[0]);
						conti->name = contents[1];
						int contID = stoi(contents[2]);
						Territory* ret = new Territory(conti->id, contID, conti->name);
						created->territoryVector.push_back(ret);
						cout << *ret;

						for (Continent* cont : created->continentVector) {
							if (cont->id == contID) {
								cont->subGraphIndex.push_back(ret->getTerritoryID());
								cont->subGraph.push_back(ret);


							}
						}


					}

					created->wasVisited = new bool[territoryCreated - 1];
					created->numTerritories = territoryCreated - 1; // initialize numTerritories here
					created->neighbors = new vector<int>[territoryCreated - 1]; // initialize neighbors here
				}
				else if (readingBorders) {
					cout << current << endl;
					contents = split(current, ' ');
					if (contents.size() > 0) {
						vector<int> edges;

						for (string p : contents) {
							edges.push_back(stoi(p));   // 1 2 3

						}

						Territory* t = created->territoryVector[edges[0] - 1]; // 1
						int k = edges[0] - 1;

						for (int i = 1; i < edges.size(); i++) { // add 2 and 3 to 1's territories
							Territory* o = created->territoryVector[edges[i] - 1];
							t->addAdj(o);
							created->neighbors[(k)].push_back(edges[i] - 1);
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
				//Printing territories that belong to the first continent:
				cout << "here is" << endl;
				vector<Territory*> temp = created->continentVector[0]->subGraph;
				for (Territory* p : temp) {
					cout << *p;
				}


				loadedMap = *created;
				created->valid = true;
				return created;


			}
			else {
				cout << "ERROR - File is of incorrect format! Keywords were not found. Please check that the file meets the Map parameters." << endl;
				throw invalid_argument("ERROR - File is of incorrect format! Keywords were not found.");
				return created;
			}

		}


	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return created;
	}


	//Map Creation:
	loadedMap = *created;
	return created;
}

ostream& operator<<(ostream& out, const Territory& p)
{
	out << p.name << " " << p.territoryID << " " << p.continentID << endl;
	return out;
}

ostream& operator<<(ostream& out, const Map& p)
{
	out << "Territories that belong to the Map: " << endl;
	for (Territory* a : p.territoryVector) {
		out << *a;
	}
	out << "Continents that belong to the Map: " << endl;
	for (Continent* a : p.continentVector) {
		out << a->name << " " << a->id << " " << a->armyValue << endl;
	}
	return out;
}
ostream& operator << (ostream& out, const MapLoader& p) {
	out << "Loaded File: " << p.fileName << endl;
	return out;
}


// Functions for Map Validation

// Checks that the given Map object is a connected graph
bool Map::isConnected() {
	for (int i = 0; i < numTerritories; i++) {
		DFS(i); // fill in the boolean values in wasVisited vector
		for (int j = 0; j < numTerritories; j++) {
			if (!wasVisited[j])    // check if there is any false value in the above array, which means the graph is not connected
			{
				int index = i;
				cout << "TerritoryId " << (index + 1) << " cannot reach to all the other territories: ";  // print which continentID is not inner connected
				cout << "The map is not connected" << endl;
				return false;
			}
		}
	}
	delete wasVisited;
	cout << "The map is a connected graph." << endl;
	return true;
}
// Assists the isConnected function
void Map::DFS(int s) {

	//starting with all nodes as not visited
	for (int i = 0; i < numTerritories; i++) {
		wasVisited[i] = false;
	}
	// Let the helper do the DFS recursively
	DFS_helper(s, wasVisited);

}
// Assists the isConnected function
void Map::DFS_helper(int s, bool* visitedOrNot) {
	// mark the current node as visited
	visitedOrNot[s] = true;

	// Go through the neighbors vector	

	for (int i : neighbors[s]) {
		// if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
		if (!visitedOrNot[i]) {
			int index = i;
			int index2 = s;
			DFS_helper(i, visitedOrNot);
		}
	}

}


bool Map::continentSubgraphs(Map* map) {
	vector<Territory*> trr = map->territoryVector;

	for (Continent* con : map->continentVector) {
		int bond = con->subGraph.size();
		wasVisited = new bool[bond];
		for (int i = 0; i < bond; i++) {

			DFS1(i, bond, trr); // fill in the boolean values in wasVisited vector
			for (int j = 0; j < bond; j++) {
				if (!wasVisited[j])    // check if there is any false value in the above array, which means the graph is not connected
				{
					cout << "The continent " << con->name << " is not a connected graph." << endl;  // print which continentID is not inner connected
					return false;

				}
			}
		}
	}

	delete wasVisited;
	cout << "All the continents are connected subgraphs" << endl;
	return true;

}
// Assists the continentSubgraph function
void Map::DFS1(int s, int bond, vector<Territory*> trr) {

	//starting with all nodes as not visited
	for (int i = 0; i < bond; i++) {
		wasVisited[i] = false;
	}
	// Let the helper do the DFS recursively
	DFS_helper1(s, wasVisited, trr);

}
// Assists the continentSubgraph function
void Map::DFS_helper1(int s, bool* visitedOrNot, vector<Territory*> trr) {

	int tID = trr[s]->getTerritoryID();
	int cID = trr[s]->getContinentID();
	vector<int> localNeighbors = neighbors[s]; // [1] connects to [21] [3] => localNeighbors[0] is (21-1) 

	// mark the current node as visited
	visitedOrNot[s] = true;

	// Go through the neighbors vector	
	for (int i = 0; i < neighbors[s].size(); i++)
	{
		int tID2 = localNeighbors[i];
		int cID2 = trr[tID2]->getContinentID();

		if ((cID2 == cID) && (!visitedOrNot[tID2]))
		{
			int index = s;
			//cout << "Going to visit " << tID2+1 << " from " << (index + 1) << endl;
			DFS_helper1(tID2, visitedOrNot, trr);

		}

	}

}

// Will traverse through countryList, checking that each entry has a valid unique value for continentID
bool Map::countryToContinentRelation() {
	//This method checks only for copies of Territory objects. Two Territories of the same name, but stored at different addresses, will not count as copies. 
	int sum = 0;
	cout << "Checking Relation between Territories and Continents" << endl;
	for (Territory* currentTerritory : territoryVector) {
		sum = 0;
		for (Continent* p : continentVector) {
			vector<Territory*> contains = p->getSubGraph();
			string terrName = currentTerritory->getTerritoryName();
			auto it = find_if(contains.begin(), contains.end(), [&terrName](Territory* obj) {
				return obj->getTerritoryName() == terrName; });
			if (it != contains.end()) {
				sum++;
				cout << "\tFound " << currentTerritory->getTerritoryName() << " in " << p->name << ". It has been found in " << sum << " continents." << endl;

			}
			if (sum > 1) {
				cout << "\tTerritory " << currentTerritory->getTerritoryName() << " belongs to more than one continent." << endl;
				return false;
			}
		}
		if (sum > 1) {
			cout << "\tTerritory " << currentTerritory->getTerritoryName() << " belongs to more than one continent." << endl;
			return false;
		}

	}
	cout << "Each Territory on the Map Belongs on One and Only One Continent" << endl;
	return true;
}

bool Map::getValidity()
{
	return valid;
}

// Checks isConnected, continentSubgraphs and countryToContinentRelation. Returns True when all are True.
// Is called during MapLoader::loadMap()
bool Map::validate(bool a, bool b, bool c) {
	if (a && b && c) {
		cout << "MAP VALIDITY: The Map is valid." << endl;
		return true;
	}
	else {
		cout << "MAP VALIDITY: The Map is NOT valid." << endl;
		return false;
	}
}

bool Map::validateWrapper(void) {
	cout << "Validating Map " << endl;
	cout << "\n---------------------------------------------------" << endl;
	bool a = isConnected();
	bool b = continentSubgraphs(this);
	bool c = countryToContinentRelation();
	bool result = validate(a, b, c);
	if (result) {

		valid = true;
		return true;
	}
	else {

		valid = false;
		return false;
	}

}
